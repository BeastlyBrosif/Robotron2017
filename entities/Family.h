#ifndef FAMILY_H
#define FAMILY_H


#include "../entities/Entity.h"
#include "../entities/Player.h"

class Family : public Entity
{
public:
  Family() : Entity()
  {
	  m_destroyed = false;
  };
   virtual void move(Player * player) {};

   virtual bool hasShot(){return false;}; //returns whether the enemy has shot, default is to return false, if the enemy has not shot

   bool isProg(){return isNowProg;}

    void setToProg(){isNowProg = true;};
    virtual ~Family(){};


protected:
    bool isNowProg;
    void updateRandomDir();


private:

};

#endif // FAMILY_H
