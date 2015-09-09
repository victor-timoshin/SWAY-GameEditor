#ifndef ASSETBROWSERTHUMBNAIL_H
#define ASSETBROWSERTHUMBNAIL_H

#include "AssetBrowserCtrl.h"
#include "StdAfx.h"

class AssetBrowserThumbnail : public wxObject
{
	//DECLARE_CLASS(AssetBrowserThumbnail)

public:
	/// <summary>Конструктор класса.</summary>
	/// <param name="filename">Имя файла.</param>
	AssetBrowserThumbnail(const wxString& f = wxEmptyString);

	/// <summary>Деструктор класса.</summary>
	~AssetBrowserThumbnail(void);

	bool Load(AssetBrowserCtrl* ctrl, bool forceLoad);

	void Draw(wxDC& deviceContext, const wxRect& rect);

	wxBitmap& GetCachedBitmap(void);

	void SetFilename(const wxString& f);

	const wxString& GetFilename(void) const;

	void SetState(int s);

	int GetState(void) const;

private:
	wxBitmap cachedBitmap;
	wxString filename;
	int state;
};

#endif // ASSETBROWSERTHUMBNAIL_H