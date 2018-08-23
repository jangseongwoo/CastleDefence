#include "Terrain.h"


using namespace Ogre;

//-----------------------------------------
Terrain::Terrain()
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");
}

//-----------------------------------------
Terrain::Terrain(SceneNode* terrainNode, Vector3 terrainPosition, char* terrainName, char* terrainMeshName)
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");

	mTerrainEntity = mSceneMgr->createEntity(terrainName, terrainMeshName);
	mTerrainSceneNode = terrainNode->createChildSceneNode(terrainName, terrainPosition);
	mTerrainSceneNode->attachObject(mTerrainEntity);
	mTerrainEntity->setCastShadows(true);
}

//-----------------------------------------
void Terrain::createTerrain(SceneNode* terrainNode, Vector3 terrainPosition, char* terrainName, char* terrainMeshName)
{
	mTerrainEntity = mSceneMgr->createEntity(terrainName, terrainMeshName);
	mTerrainSceneNode = terrainNode->createChildSceneNode(terrainName, terrainPosition);
	mTerrainSceneNode->attachObject(mTerrainEntity);
	mTerrainEntity->setCastShadows(true);
}

//-----------------------------------------
void Terrain::setTerrainPosition(float x, float y, float z)
{
	mTerrainSceneNode->setPosition(x,y,z);
}

//-----------------------------------------
void Terrain::setTerrainShadow()
{
	if(0 == mTerrainEntity->getCastShadows())
		mTerrainEntity->setCastShadows(true);
	else
		mTerrainEntity->setCastShadows(false);
}

//-----------------------------------------
Vector3 Terrain::getTerrainPosition()
{
	return mTerrainSceneNode->getPosition();
}

//-----------------------------------------
SceneNode* Terrain::getTerrainSceneNode()
{
	return mTerrainSceneNode;
}