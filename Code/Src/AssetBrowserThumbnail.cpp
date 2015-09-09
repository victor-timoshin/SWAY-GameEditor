#include "../Inc/AssetBrowserThumbnail.h"

AssetBrowserThumbnail::AssetBrowserThumbnail(const wxString& name)
	: filename(name)
{
}

AssetBrowserThumbnail::~AssetBrowserThumbnail(void)
{
}

bool AssetBrowserThumbnail::Load(AssetBrowserCtrl* ctrl, bool forceLoad)
{
	if (cachedBitmap.Ok() && !forceLoad)
		return true;

	if (wxFileExists(filename))
	{
		wxImage image;
		if (image.LoadFile(filename, wxBITMAP_TYPE_ANY))
		{
			wxSize thumbnailSize = ctrl->GetThumbnailImageSize();
			double scaleX = ((double)thumbnailSize.x) / ((double)image.GetWidth());
			double scaleY = ((double)thumbnailSize.y) / ((double)image.GetHeight());

			if (scaleX < 1.0 || scaleY < 1.0)
			{
				double scale = wxMin(scaleX, scaleY);
				int newWidth = (int)(scale * image.GetWidth());
				int newHeight = (int)(scale * image.GetHeight());

				image.Rescale(newWidth, newHeight);
			}

			cachedBitmap = wxBitmap(image);

			return true;
		}
	}

	return false;
}

void AssetBrowserThumbnail::Draw(wxDC& deviceContext, const wxRect& rect)
{
	if (cachedBitmap.Ok())
	{
		int x = rect.x + (rect.width - cachedBitmap.GetWidth()) / 2;
		int y = rect.y + (rect.height - cachedBitmap.GetHeight()) / 2;

#ifdef __WXWINCE__
		wxBitmap tmpBitmap = cachedBitmap;
		deviceContext.DrawBitmap(tmpBitmap, x, y);
#else
		deviceContext.DrawBitmap(cachedBitmap, x, y);
#endif
	}
}

wxBitmap& AssetBrowserThumbnail::GetCachedBitmap(void)
{
	return cachedBitmap;
}

void AssetBrowserThumbnail::SetFilename(const wxString& f)
{
	filename = f;
}

const wxString& AssetBrowserThumbnail::GetFilename(void) const
{
	return filename;
}

void AssetBrowserThumbnail::SetState(int s)
{
	state = s;
}

int AssetBrowserThumbnail::GetState(void) const
{
	return state;
}