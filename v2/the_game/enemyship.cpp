#include "enemyship.h"

enemyShip::enemyShip(){
    mObjType = gameObj::objEnemyShip;
    timed = 0;
}

void enemyShip::enemyShipInit(QPixmap shipImg, int _enemyType, float shipX, float xS, float yS, float shipY)
{
    this->setPos(shipX, shipY);
    this->setPixmap(shipImg);
    enemyType = _enemyType;
    switch(_enemyType){
        case enemyShip::enemy_Lv1:{
            this->xSpeed = 0.0;
            this->ySpeed = 0.3;
            this->ammoFreq = 100;
            this->shipHP = 30;
            this->destroyScore = 200;
            break;
        }
        case enemyShip::enemy_Lv2:{
            this->xSpeed = 0.0;
            this->ySpeed = 0.5;
            this->ammoFreq = 50;
            this->shipHP = 20;
            this->destroyScore = 100;
            break;
        }
        case enemyShip::enemy_Lv3:{
            this->xSpeed = 0.1;
            this->ySpeed = 0.2;
            this->ammoFreq = 200;
            this->shipHP = 50;
            this->destroyScore = 500;
            break;
        }
        case enemyShip::enemy_Boss1:{
            this->xSpeed = 0.1;
            this->ySpeed = 0.10;
            this->ammoFreq = 200;
            this->shipHP = 50;
            this->destroyScore = 500;
            break;
        }
        case enemyShip::enemy_Boss2:{

        }
        case enemyShip::enemy_Special1:{

        }
        case enemyShip::enemy_Special2:{

        }
    }
    if (xS != 0) this->xSpeed = xS;
    if (yS != 0) this->ySpeed = yS;
}
