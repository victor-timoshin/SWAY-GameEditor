#ifndef STDAFX_H
#define STDAFX_H

#include <wx/msw/winundef.h>

#include <wx/wx.h>
#include <wx/arrimpl.cpp>
#include <wx/dynarray.h>
#include <wx/image.h>
#include <wx/dir.h>
#include <wx/windowid.h>
#include <wx/config.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/valnum.h>
#include <wx/treectrl.h>
#include <wx/aui/aui.h>
#include <wx/aui/tabmdi.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>

#include <Core/Render/RenderSystemBase.h>
#include <Core/Utils/Singleton.h>
#include <SceneGraph/SceneGraphBase.h>
#include <SceneGraph/SceneComponentBase.h>
#include <SceneGraph/SceneNodeBase.h>
#include <Platform.h>

#include "WidgetId.h"

typedef enum BrowserTreeIcon
{
	EBTI_MESH,
	EBTI_SUBMESH,
	EBTI_LIGHT,
	EBTI_NODE,
	EBTI_CAMERA,
} BROWSERTREEICON;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CAMERA_FOV 90.0f
#define CAMERA_ZNEAR 1.0f
#define CAMERA_ZFAR 100000.0f

#endif // STDAFX_H