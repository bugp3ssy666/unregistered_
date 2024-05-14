#ifndef SHIPAMMO_H
#define SHIPAMMO_H

#include <QTimer>

#include "gameobj.h"

class shipAmmo : public gameObj
{
public:
    explicit shipAmmo();

    //enum ammoType{playerAmmo, enemyAmmo};

    //shipAmmo(float ammoX, float ammoY, QPixmap ammoImg, int ammoType);

    void moveAmmo(QPoint moveDir = QPoint (0,-1));

    int getType();

    // void ammoGenSound(QString);

    int ammoATK;

protected:
    float m_ammoSpeed;

    // QMediaPlayer ammoSound;

signals:
};

#endif // SHIPAMMO_H
