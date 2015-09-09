#ifndef ASSETBROWSERCTRL_H
#define ASSETBROWSERCTRL_H

#include "StdAfx.h"

#define THUMBNAIL_DEFAULT_IMAGE_SIZE wxSize(80, 80)
#define THUMBNAIL_DEFAULT_OVERALL_SIZE wxSize(-1, -1)
#define THUMBNAIL_DEFAULT_SPACING 3
#define THUMBNAIL_DEFAULT_MARGIN 3

class AssetBrowserThumbnail;

WX_DECLARE_OBJARRAY(AssetBrowserThumbnail, AssetBrowserThumbnailArray);
class AssetBrowserCtrl : public wxScrolledWindow
{
	DECLARE_EVENT_TABLE()

public:
	/// <summary>Конструктор класса.</summary>
	/// <param name="parent">Указатель на родительское окно.</param>
	/// <param name="id">Уникальный идентификатор панели.</param>
	AssetBrowserCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& position = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	/// <summary>Деструктор класса.</summary>
	~AssetBrowserCtrl(void);

	void OnPaint(wxPaintEvent& WXUNUSED(event));

	void OnSize(wxSizeEvent& event);


	bool RecreateBuffer(const wxSize& size);

	void RecreateList(long flags);

	void OpenFolder(const wxString& path);

	AssetBrowserThumbnail* GetItem(UInt index);

	bool GetRowCol(UInt index, const wxSize& clientSize, int& row, int& col);

	bool GetItemRect(UInt index, wxRect& rect, bool transform);

	bool GetItemRectImage(UInt index, wxRect& rect, bool transform);

	void CalculateOverallThumbnailSize(void);

	bool DrawItem(UInt index, wxDC& dc, const wxRect& rect);


	void SetThumbnailImageSize(const wxSize& size);

	const wxSize& GetThumbnailImageSize(void) const;

private:
	AssetBrowserThumbnailArray thumbnails;
	wxBitmap bufferBitmap;

	wxSize thumbnailImageSize;
	wxSize thumbnailOverallSize;
	int spacing;

	int thumbnailMargin;
};

#endif // ASSETBROWSERCTRL_H