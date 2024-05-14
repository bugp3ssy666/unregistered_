#ifndef SHIPOBJ_H
#define SHIPOBJ_H

#include "gameobj.h"

class shipObj : public gameObj
{
    //Q_OBJECT
public:
    explicit shipObj();


    int ammoFreq;

    int shipHP;

protected:

signals:
};

#endif // SHIPOBJ_H
