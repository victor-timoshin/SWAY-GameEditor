#ifndef SCENEGRAPHTREEITEMDATA_H
#define SCENEGRAPHTREEITEMDATA_H

#include "StdAfx.h"

class SceneGraphTreeItemData : public wxTreeItemData
{
public:
	/// <summary>����������� ������.</summary>
	SceneGraphTreeItemData(Scene::ISceneNodeBase* node);

	/// <summary>���������� ������.</summary>
	~SceneGraphTreeItemData(void);

	Scene::ISceneNodeBase* GetNode(void);
private:
	Scene::ISceneNodeBase* itemNode;
};

#endif // SCENEGRAPHTREEITEMDATA_H