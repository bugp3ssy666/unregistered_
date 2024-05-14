#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "shipobj.h"
#include <QTimer>

class enemyShip : public shipObj
{
    //Q_OBJECT
public:
    explicit enemyShip();
    void enemyShipInit(QPixmap, int _enemyType, float, float, float, float);
    void enemySpeedReset(int x, int y);

    enum mEnemyType{enemy_Lv1, enemy_Lv2, enemy_Lv3, enemy_Boss1, enemy_Boss2, enemy_Special1, enemy_Special2};

    float xSpeed;
    float ySpeed;

    int destroyScore;
    int enemyType;

    QTimer* temp_timer;
    bool timed;

    // ~enemyShip(){
    //     delete temp_timer;
    // }

protected:
};

#endif // ENEMYSHIP_H
