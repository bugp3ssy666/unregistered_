#include "playership.h"

playerShip::playerShip()
{
    mObjType = gameObj::objPlayerShip;
    this->shipSpeed = 0.6;
    this->ammoFreq = 150;
    this->setPixmap(QPixmap(":/img/img/player.jpg"));
    this->setPos(100,100);
    this->maxHealth = 100;
    this->maxLife = 3;
    this->shipLife = this->maxLife;
    this->shipHP = this->maxHealth;
}
