#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>
#define PI 3.141592

using namespace Ogre;

enum bossState{bossIdle, bossSpawn, bossAttack, bossDie};

class Boss 
{
public:
	Boss();
	~Boss();
	void update(Ogre::Real timeSinceLastFrame);
	bool collisionCheck(Vector3 bulletVector);
	void setPosition(Vector3 position);
	//void trace(SceneNode* destNode);
	bool getAlive(); void setAlive(bool isAlive);
	void getHurt(int damage); int getBossHP();
private:
	Ogre::SceneManager* mSceneMgr;
	SceneNode* mBossSceneNode;
	Entity* mBossEntity;
	AnimationState* mBossAnimationState;
	Ogre::Root *mRoot;


	Quaternion prevQuat;
	Quaternion quat;

	Vector3 dest;
	Vector3 mDestination;
	Vector3 mDirection;
	Real mDistance;
	Real move;
	float BossVelocity;
	float sinAngle;
	float moveAngle;
	bool mAlive;
	bossState mBossState;

	int mBossHP;
	
	float time;
	Vector3 mAxis;
	int randomNumber;
	float mAnimationTimer;
};