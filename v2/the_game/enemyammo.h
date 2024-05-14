#ifndef ENEMYAMMO_H
#define ENEMYAMMO_H

#include <QObject>
#include <QMediaPlayer>
#include "shipammo.h"

class enemyAmmo : public shipAmmo
{
public:
    explicit enemyAmmo();
    void enemyAmmoInit(float ammoX, float ammoY, QPixmap ammoImg, int ammoType);

    enum enemyType{enemy_Lv1, enemy_Lv2, enemy_Lv3, enemy_Boss1, enemy_Boss2, enemy_Special1, enemy_Special2};

    void enemyAmmoGenSound(int);

protected:
    int enemyAmmoType;

    QMediaPlayer enemyAmmoSound;

};

#endif // ENEMYAMMO_H
