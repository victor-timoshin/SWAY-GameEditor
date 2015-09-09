#include "../Inc/SceneGraphTreeItemData.h"

/// <summary>����������� ������.</summary>
SceneGraphTreeItemData::SceneGraphTreeItemData(Scene::ISceneNodeBase* node)
	: itemNode(node)
{
}

/// <summary>���������� ������.</summary>
SceneGraphTreeItemData::~SceneGraphTreeItemData(void)
{
}

Scene::ISceneNodeBase* SceneGraphTreeItemData::GetNode(void)
{
	return itemNode;
}