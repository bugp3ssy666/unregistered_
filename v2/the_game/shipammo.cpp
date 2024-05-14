#include "shipammo.h"

shipAmmo::shipAmmo(){}

// shipAmmo::shipAmmo(float ammoX, float ammoY, QPixmap ammoImg, int ammoType): m_ammoType(ammoType), m_ammoSpeed(1)
// {
//     this->setPos(ammoX, ammoY);
//     this->setPixmap(ammoImg);

//     ammoGenSound(ammoType);

//     //timerAmmoMove = new QTimer(this);
//     //timerAmmoMove->start(1);
//     //connect(timerAmmoMove, &QTimer::timeout, this, &shipAmmo::moveAmmo);
// }

void shipAmmo::moveAmmo(QPoint moveDir){
    this->moveBy(moveDir.x()*m_ammoSpeed, moveDir.y()*m_ammoSpeed);
}

// void shipAmmo::ammoGenSound(QString _url){
//     ammoSound.setMedia(QUrl(_url));
//     ammoSound.play();
// }

int shipAmmo::getType(){
    return this->mObjType;
}
