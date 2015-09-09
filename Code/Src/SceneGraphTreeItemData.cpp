#include "../Inc/SceneGraphTreeItemData.h"

/// <summary>Конструктор класса.</summary>
SceneGraphTreeItemData::SceneGraphTreeItemData(Scene::ISceneNodeBase* node)
	: itemNode(node)
{
}

/// <summary>Деструктор класса.</summary>
SceneGraphTreeItemData::~SceneGraphTreeItemData(void)
{
}

Scene::ISceneNodeBase* SceneGraphTreeItemData::GetNode(void)
{
	return itemNode;
}