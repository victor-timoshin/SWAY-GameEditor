#ifndef SCENEGRAPHTREEITEMDATA_H
#define SCENEGRAPHTREEITEMDATA_H

#include "StdAfx.h"

class SceneGraphTreeItemData : public wxTreeItemData
{
public:
	/// <summary>Конструктор класса.</summary>
	SceneGraphTreeItemData(Scene::ISceneNodeBase* node);

	/// <summary>Деструктор класса.</summary>
	~SceneGraphTreeItemData(void);

	Scene::ISceneNodeBase* GetNode(void);
private:
	Scene::ISceneNodeBase* itemNode;
};

#endif // SCENEGRAPHTREEITEMDATA_H