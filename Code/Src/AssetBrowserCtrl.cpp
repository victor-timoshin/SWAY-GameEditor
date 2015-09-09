#include "../Inc/AssetBrowserCtrl.h"
#include "../Inc/AssetBrowserThumbnail.h"

BEGIN_EVENT_TABLE(AssetBrowserCtrl, wxScrolledWindow)
	EVT_PAINT(AssetBrowserCtrl::OnPaint)
	EVT_SIZE(AssetBrowserCtrl::OnSize)
END_EVENT_TABLE()

static int DetermineImageType(const wxString& filename)
{
	wxString path, name, ext;

	wxFileName::SplitPath(filename, &path, &name, &ext);

	ext.MakeLower();
	if (ext == wxT("jpg") || ext == wxT("jpeg"))
		return wxBITMAP_TYPE_JPEG;
	else if (ext == wxT("gif"))
		return wxBITMAP_TYPE_GIF;
	else if (ext == wxT("bmp"))
		return wxBITMAP_TYPE_BMP;
	else if (ext == wxT("png"))
		return wxBITMAP_TYPE_PNG;
	else if (ext == wxT("pcx"))
		return wxBITMAP_TYPE_PCX;
	else if (ext == wxT("tif") || ext == wxT("tiff"))
		return wxBITMAP_TYPE_TIF;
	else
		return -1;
}

WX_DEFINE_OBJARRAY(AssetBrowserThumbnailArray);

AssetBrowserCtrl::AssetBrowserCtrl(wxWindow* parent, wxWindowID id, const wxPoint& position, const wxSize& size) : wxScrolledWindow(parent, id, position, size)
{
	thumbnailImageSize = THUMBNAIL_DEFAULT_IMAGE_SIZE;
	thumbnailOverallSize = THUMBNAIL_DEFAULT_OVERALL_SIZE;
	spacing = THUMBNAIL_DEFAULT_SPACING;
	thumbnailMargin = THUMBNAIL_DEFAULT_MARGIN;

	CalculateOverallThumbnailSize();

#if USE_BUFFERED_PAINT
	RecreateBuffer(size);
#endif
}

AssetBrowserCtrl::~AssetBrowserCtrl(void)
{
}

void AssetBrowserCtrl::OnPaint(wxPaintEvent& WXUNUSED(event))
{
#if USE_BUFFERED_PAINT
	wxBufferedPaintDC paintDC(this, bufferBitmap);
#else
	wxPaintDC paintDC(this);
#endif

	PrepareDC(paintDC);

	wxRegion dirtyRegion = GetUpdateRegion();
	wxRect rect, untransformedRect, imageRect, untransformedImageRect;

	for (UInt i = 0; i < thumbnails.size(); ++i)
	{
		GetItemRect(i, rect, true);

		wxRegionContain regionContain = dirtyRegion.Contains(imageRect);
		if (regionContain != wxOutRegion)
		{
			GetItemRectImage(i, imageRect, true);

			GetItemRect(i, untransformedRect, false);
			GetItemRectImage(i, untransformedImageRect, false);

			DrawItem(i, paintDC, imageRect);
		}
	}
}

void AssetBrowserCtrl::OnSize(wxSizeEvent& event)
{
	//SetupScrollbars();
	RecreateBuffer(wxDefaultSize);
	event.Skip();
}

bool AssetBrowserCtrl::RecreateBuffer(const wxSize& size)
{
	wxSize sz = size;
	if (sz == wxDefaultSize)
		sz = GetClientSize();

	if (sz.x < 1 || sz.y < 1)
		return false;

	if (!bufferBitmap.Ok() || bufferBitmap.GetWidth() < sz.x || bufferBitmap.GetHeight() < sz.y)
		bufferBitmap = wxBitmap(sz.x, sz.y);

	return bufferBitmap.Ok();
}

void AssetBrowserCtrl::RecreateList(long flags)
{
}

void AssetBrowserCtrl::OpenFolder(const wxString& path)
{
	wxDir directory;
	if (directory.Open(path))
	{
		wxString filename;
		bool cont = directory.GetFirst(&filename, wxT("*.*"), wxDIR_FILES);
		while (cont)
		{
			wxString file = path + wxFILE_SEP_PATH + filename;
			if (wxFileExists(file) && DetermineImageType(file) != -1)
			{
				AssetBrowserThumbnail* item = NULL;
				item = new AssetBrowserThumbnail(file);
				item->Load(this, false);

				thumbnails.Add(item);
			}

			cont = directory.GetNext(&filename);
		}
	}
}

void AssetBrowserCtrl::SetThumbnailImageSize(const wxSize& size)
{
	thumbnailImageSize = size;
}

const wxSize& AssetBrowserCtrl::GetThumbnailImageSize(void) const
{
	return thumbnailImageSize;
}

bool AssetBrowserCtrl::DrawItem(UInt index, wxDC& dc, const wxRect& rect)
{
	AssetBrowserThumbnail* item = GetItem(index);
	if (item)
	{
		item->Draw(dc, rect);
		return true;
	}
	else
		return false;
}

bool AssetBrowserCtrl::GetRowCol(UInt index, const wxSize& clientSize, int& row, int& col)
{
	if (index >= thumbnails.size())
		return false;

	int perRow = clientSize.x / (thumbnailOverallSize.x + spacing);
	if (perRow < 1)
		perRow = 1;

	row = index / perRow;
	col = index % perRow;

	return true;
}

bool AssetBrowserCtrl::GetItemRect(UInt index, wxRect& rect, bool transform)
{
	if (index < thumbnails.size())
	{
		int row, col;
		if (!GetRowCol(index, GetClientSize(), row, col))
			return false;

		int x = col * (thumbnailOverallSize.x + spacing) + spacing;
		int y = row * (thumbnailOverallSize.y + spacing) + spacing;

		if (transform)
		{
			int startX, startY;
			int xppu, yppu;
			GetScrollPixelsPerUnit(&xppu, &yppu);
			GetViewStart(&startX, &startY);
			x = x - startX * xppu;
			y = y - startY * yppu;
		}

		rect.x = x;
		rect.y = y;
		rect.width = thumbnailOverallSize.x;
		rect.height = thumbnailOverallSize.y;

		return true;
	}

	return false;
}

bool AssetBrowserCtrl::GetItemRectImage(UInt index, wxRect& rect, bool transform)
{
	wxRect outerRect;
	if (!GetItemRect(index, outerRect, transform))
		return false;

	rect.width = thumbnailImageSize.x;
	rect.height = thumbnailImageSize.y;
	rect.x = outerRect.x + (outerRect.width - rect.width) / 2;
	rect.y = outerRect.y + (outerRect.height - rect.height) / 2;

	return true;
}

void AssetBrowserCtrl::CalculateOverallThumbnailSize()
{
	wxCoord coord;
	wxClientDC clientDC(this);

	thumbnailOverallSize.x = thumbnailMargin * 2 + thumbnailImageSize.x;
	thumbnailOverallSize.y = thumbnailMargin * 3 + thumbnailImageSize.y;
}

AssetBrowserThumbnail* AssetBrowserCtrl::GetItem(UInt index)
{
	if (index < thumbnails.size())
		return &thumbnails[(size_t)index];
	else
		return NULL;
}