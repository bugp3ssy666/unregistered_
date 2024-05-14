#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "shipobj.h"

class playerShip : public shipObj
{
    //Q_OBJECT
public:
    explicit playerShip();

    float shipSpeed;

    int shipLife;
    int maxHealth;
    int maxLife;

    int ammoType;

protected:

};

#endif // PLAYERSHIP_H
