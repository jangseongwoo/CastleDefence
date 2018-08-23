#pragma once

#include "GameManager.h"
#include "GameState.h"

using namespace Ogre;


class Bullet
{
public:
	Bullet(int Number);
	~Bullet();
	void fire(Vector3 direction,Vector3 position);
	void update(Ogre::Real timeSinceLastFrame);
	void createPlayer();
	void setHP(int hp); int getHP();
	void setBulletPosition(Vector3 position); 
	void setBulletQuternion(Quaternion direction);
	Vector3 getPlayerPosition();
	void playerHeadYaw(float yawValue); void playerHeadPitch(float pitchValue);
	SceneNode* getPlayerSceneNode();
	void fireBullet();
	void playerDie();
	bool getAlive(); void setAlive(bool isAlive);

	Vector3 mBulletPosition;
protected:

private:
	int mBulletDamage;
	int mBulletVelocity;

	bool mIsFire;

	Entity* mBulletEntity;
	
	SceneNode* mBulletSceneNode;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Root* mRoot;

	char mName[15];
	int mBulletNumber;
	Vector3 mBulletDirection;
	bool mAlive;
};