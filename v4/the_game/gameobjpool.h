#ifndef GAMEOBJPOOL_H
#define GAMEOBJPOOL_H

#include <QObject>
#include "defindex.h"
#include "shipammo.h"
#include "playerammo.h"
#include "enemyammo.h"
#include "enemyship.h"
#include "gameprop.h"

class gameObjPool : public QObject
{
    gameObjPool();
    static gameObjPool*instance;
public:
    static gameObjPool* Instance(){
        if(instance == nullptr) return instance = new gameObjPool;
        return instance;
    }

    void objInit();

    gameObj* objObtn(int _objType);

    void objRcycl(gameObj* _obj);

    void objClear();

    ~gameObjPool();

protected:
    QList<shipAmmo*> playerAmmoPool;
    QList<shipAmmo*> enemyAmmoPool;
    QList<enemyShip*> enemyPool;
    QList<gameProp*> propPool;

};

#endif // GAMEOBJPOOL_H
