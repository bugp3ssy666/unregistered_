#ifndef PLAYERAMMO_H
#define PLAYERAMMO_H

#include <QObject>
#include <QMediaPlayer>
#include "shipammo.h"

class playerAmmo : public shipAmmo
{
public:
    explicit playerAmmo();
    void playerAmmoInit(float ammoX, float ammoY, QPixmap ammoImg, int _type);

    enum mplayerAmmoType{defaultAmmo, advancedAmmo_Lv1, advancedAmmo_Lv2, bombAmmo_Lv1, bombAmmo_Lv2};

    void playerAmmoGenSound(int);


protected:
    int playerAmmoType;

    QMediaPlayer playerAmmoSound;

};

#endif // PLAYERAMMO_H
