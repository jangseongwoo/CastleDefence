#pragma once

#include "GameManager.h"
#include "GameState.h"
#include "OgreString.h"

using namespace Ogre;


class Terrain
{
public:
	Terrain();
	Terrain(SceneNode*, Vector3, char*, char*);
	~Terrain();

	//부모 씬노드, 배치할 위치를 전달해줌.
	void createTerrain(SceneNode*, Vector3, char*, char*);
	void setTerrainPosition(float x, float y, float z); Vector3 getTerrainPosition();
	void setTerrainShadow();
	SceneNode* getTerrainSceneNode();

protected:

private:
	Vector3 mTerrainPosition;
	Entity* mTerrainEntity;
	SceneNode* mTerrainSceneNode;
	char* mTerrainMeshName;


	Ogre::SceneManager* mSceneMgr;
	//Ogre::Camera* mCamera;
	Ogre::Root* mRoot;
};