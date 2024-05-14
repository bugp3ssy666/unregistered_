#ifndef GAMEPROP_H
#define GAMEPROP_H

#include <QObject>
#include "gameobj.h"

class gameProp : public gameObj
{
public:
    explicit gameProp();

    enum mpropType{speedUp, doubleScore, singleShield, extraLife, laserBeam, massiveBomb};

    void gamePropInit(int, int, int y = -25);

    int propType;

protected:

};

#endif // GAMEPROP_H
