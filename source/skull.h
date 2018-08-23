#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>
#include "Player.h"
#define PI 3.141592

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )
using namespace Ogre;

class Skull 
{
public:
	Skull();
	~Skull();
	void update(Ogre::Real timeSinceLastFrame);
	bool collisionCheck(Vector3 bulletVector);
	void setPosition(Vector3 position){
		mSkullNode->setPosition(position);	
	}
	void trace(SceneNode* destNode);
	bool getAlive(); void setAlive(bool isAlive);
private:
	Ogre::SceneManager* mSceneMgr;
	SceneNode* mSkullNode;
	Entity* mSkullEntity;
	AnimationState* mSkullAnimationState;
	Ogre::Root *mRoot;

	char mName[15];
	int mSkullNumber;

	Quaternion prevQuat;
	Quaternion quat;

	Vector3 dest;
	Vector3 mDestination;
	Vector3 mDirection;
	Real mDistance;
	Real move;
	float SkullVelocity;
	float sinAngle;
	float moveAngle;
	bool mAlive;
	int mSkullHP;
	
	float time;
	Vector3 mAxis;
	int randomNumber;
};


	