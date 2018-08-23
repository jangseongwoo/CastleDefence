#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   EntityManager.h
//
//  Desc:   Singleton class to handle the  management of Entities.          
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <map>
#include <cassert>
#include <string>


class BaseGameEntity;

//provide easy access
#define EntityMgr EntityManager::Instance()



class EntityManager
{
private:
  int          m_ID;

  //this is the next valid ID. Each time a BaseGameEntity is instantiated
  //this value is updated
  static int  m_iNextValidID;

  typedef std::map<int, EntityManager*> EntityMap;
  void _SetID(int val);

private:

  //to facilitate quick lookup the entities are stored in a std::map, in which
  //pointers to entities are cross referenced by their identifying number
  EntityMap m_EntityMap;

  EntityManager(){}

  //copy ctor and assignment should be private
  EntityManager(const EntityManager&);
  EntityManager& operator=(const EntityManager&);

public:

  static EntityManager* Instance();

  //this method stores a pointer to the entity in the std::vector
  //m_Entities at the index position indicated by the entity's ID
  //(makes for faster access)
  void            RegisterEntity(EntityManager* NewEntity);

  //returns a pointer to the entity with the ID given as a parameter
  EntityManager* GetEntityFromID(int id)const;

  //this method removes the entity from the list
  void            RemoveEntity(EntityManager* pEntity);

 // virtual void  Update()=0;
  int           ID()const{return m_ID;}  
};







#endif