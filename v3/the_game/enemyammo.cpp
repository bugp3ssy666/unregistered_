#include "enemyammo.h"

enemyAmmo::enemyAmmo()
{
    mObjType = gameObj::objEnemyAmmo;
}

void enemyAmmo::enemyAmmoInit(float ammoX, float ammoY, QPixmap ammoImg, int ammoType)
{
    enemyAmmoType = ammoType;
    this->setPos(ammoX, ammoY);
    this->setPixmap(ammoImg);
    switch(enemyAmmoType){
        case enemyAmmo::enemy_Lv1: this->ammoATK = 20; m_ammoSpeed = -1;
        case enemyAmmo::enemy_Lv3: this->ammoATK = 30; this->m_ammoSpeed = -0.5;
        }
}

void enemyAmmo::enemyAmmoGenSound(int _type){
    switch(_type){
    case enemyAmmo::enemy_Lv1:   enemyAmmoSound.setMedia(QUrl("qrc:/img/img/Untitled808-1.wav"));
    };
    enemyAmmoSound.play();
}
