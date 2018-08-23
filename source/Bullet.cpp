#include "Bullet.h"


using namespace Ogre;

//-------------------------------------------
Bullet::Bullet(int Number) : mBulletNumber(Number)
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");

	sprintf(mName, "Bullet%d", mBulletNumber);
	mBulletEntity = mSceneMgr->createEntity(mName, "IronBall.mesh");
	mBulletSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName, Vector3(Vector3::ZERO));
	mBulletSceneNode->attachObject(mBulletEntity);
	mBulletSceneNode->setScale(1,1,1);

	mBulletSceneNode->setPosition(0,0,-500);
	//mPlayerHeadSceneNode->setScale(0.2,0.2,0.2);
	//std::cout<<"bullet create"<<std::endl;
	mAlive=true;
}

void Bullet::fire(Vector3 direction,Vector3 position){


}

void Bullet::update(Ogre::Real timeSinceLastFrame){

	//ÃÑ¾Ë ¹ß»ç
	//std::cout<<"bullet update()"<<std::endl;
	
//	mBulletSceneNode->translate(mBulletDirection.normalisedCopy() * 500 * timeSinceLastFrame, Node::TransformSpace::TS_LOCAL);
	mBulletSceneNode->translate(Vector3(0,0,-1) * 3000 * timeSinceLastFrame, Node::TransformSpace::TS_LOCAL);
	//std::cout<<mBulletSceneNode->getPosition()<<std::endl;
	mBulletPosition = mBulletSceneNode->getPosition();
}

void Bullet::setBulletPosition(Vector3 position){
	
	mBulletSceneNode->setPosition(position+Vector3(0,45,0));
	mBulletDirection=position;
	mBulletDirection.z=-mBulletDirection.z;
}

void Bullet::setBulletQuternion(Quaternion direction){
	mBulletSceneNode->setOrientation(direction);

}

bool Bullet::getAlive()
{
	return mAlive;
}

void Bullet::setAlive(bool isAlive)
{
	mAlive = isAlive;
}