#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>
#include "Player.h"
#define PI 3.141592

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )
using namespace Ogre;

enum demonState{idle, hurt, attack, die};

class Demon 
{
public:
	Demon();
	Demon(int number);
	~Demon();
	void update(Ogre::Real timeSinceLastFrame);
	bool collisionCheck(Vector3 bulletVector);//Bullet* bullet[]);
	void setPosition(Vector3 position){
		mDemonNode->setPosition(position);	
	}
	void trace(SceneNode* destNode);
	bool getAlive(); void setAlive(bool isAlive);
	void setHP(int damage);
	void setDemonState(demonState state); demonState getDemonState();
	AnimationState* getDemonAnimationState();

protected:

private:
	Ogre::SceneManager* mSceneMgr;
	SceneNode* mDemonNode;
	Entity* mDemonEntity;
	AnimationState* mDemonAnimationState;
	Ogre::Root *mRoot;

	char mName[15];
	

	Quaternion prevQuat;
	Quaternion quat;

	Vector3 dest;
	Vector3 mDestination;
	Vector3 mDirection;
	Real mDistance;
	Real move;
	float demonVelocity;
	float sinAngle;
	float moveAngle;
	bool mAlive;
	
	float time;
	float mAnimationTimer;
	Vector3 mAxis;
	int randomNumber;
	int mDemonHP;

	demonState mDemonState;
};


	