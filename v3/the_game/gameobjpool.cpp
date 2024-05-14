#include "gameobjpool.h"
#include <QDebug>

gameObjPool* gameObjPool::instance = nullptr;
gameObjPool::gameObjPool(){}
gameObjPool::~gameObjPool(){objClear();}

void gameObjPool::objInit(){
    for (int i = 0; i < 30; i++){
        playerAmmo* playerAmmoInstance = new playerAmmo();
        enemyAmmo* enemyAmmoInstance = new enemyAmmo();
        enemyShip* enemyInstance = new enemyShip();
        playerAmmoPool.append(playerAmmoInstance);
        enemyAmmoPool.append(enemyAmmoInstance);
        enemyPool.append(enemyInstance);
    }
    for (int i = 0; i < 20; i++){
        playerAmmo* playerAmmoInstance = new playerAmmo();
        enemyAmmo* enemyAmmoInstance = new enemyAmmo();
        playerAmmoPool.append(playerAmmoInstance);
        enemyAmmoPool.append(enemyAmmoInstance);
    }
    for (int i = 0; i < 10; i++){
        enemyAmmo* enemyAmmoInstance = new enemyAmmo();
        enemyAmmoPool.append(enemyAmmoInstance);
    }
    for (int i = 0; i < 5; i++){
        gameProp* gamePropInstance = new gameProp();
        propPool.append(gamePropInstance);
    }
}

gameObj* gameObjPool::objObtn(int _objType){
    switch (_objType){
        case gameObj::objPlayerAmmo:{
            shipAmmo* ammoInstance = playerAmmoPool.first();
            playerAmmoPool.pop_front();
            return ammoInstance;
        }
        case gameObj::objEnemyAmmo:{
            shipAmmo* ammoInstance = enemyAmmoPool.first();
            enemyAmmoPool.pop_front();
            return ammoInstance;
        }
        case gameObj::objEnemyShip:{
            enemyShip* enemyInstance = enemyPool.first();
            enemyPool.pop_front();
            return enemyInstance;
        }
        case gameObj::objGameProp:{
            gameProp* gamePropInstance = propPool.first();
            propPool.pop_front();
            return gamePropInstance;
        }
    }
    return nullptr;
}

void gameObjPool::objRcycl(gameObj* _obj){
    switch (_obj->getType()){
        case gameObj::objPlayerAmmo:{
            playerAmmoPool.append((playerAmmo*)_obj);
            break;
        }
        case gameObj::objEnemyAmmo:{
            enemyAmmoPool.append((enemyAmmo*)_obj);
            break;
        }
        case gameObj::objEnemyShip:{
            enemyPool.append((enemyShip*)_obj);
            break;
        }
        case gameObj::objGameProp:{
            propPool.append((gameProp*)_obj);
            break;
        }
    }
}

void gameObjPool::objClear(){
    for(auto pAmmo: playerAmmoPool) delete pAmmo;
    for(auto pAmmo: enemyAmmoPool) delete pAmmo;
    for(auto pEnemy: enemyPool) delete pEnemy;
}
