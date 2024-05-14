#include "playerammo.h"

playerAmmo::playerAmmo()
{
    mObjType = gameObj::objPlayerAmmo;
}

void playerAmmo::playerAmmoInit(float ammoX, float ammoY, QPixmap ammoImg, int _type)
{
    this->setPos(ammoX, ammoY);
    this->setPixmap(ammoImg);
    switch(_type){
        case playerAmmo::defaultAmmo:{
            playerAmmoType = _type;
            m_ammoSpeed = 1.5;
            this->ammoATK = 10;
            break;
        }
        case playerAmmo::advancedAmmo_Lv1:{
            playerAmmoType = _type;
            m_ammoSpeed = 2.0;
            this->ammoATK = 8;
            break;
        }
        case playerAmmo::advancedAmmo_Lv2:{
            playerAmmoType = _type;
            m_ammoSpeed = 3.0;
            this->ammoATK = 7;
            break;
        }
    }
}

void playerAmmo::playerAmmoGenSound(int _type){
    switch(_type){
        case playerAmmo::defaultAmmo:   playerAmmoSound.setMedia(QUrl("qrc:/img/img/Untitled808-1.wav"));
    };
    playerAmmoSound.play();
}
