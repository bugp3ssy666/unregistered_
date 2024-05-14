#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <QObject>
#include <QGraphicsPixmapItem>


class gameObj : public QGraphicsPixmapItem, public QObject
{

public:
    enum objType{objPlayerAmmo, objEnemyAmmo, objPlayerShip, objEnemyShip, objGameProp};
    explicit gameObj();
    int getType(){return mObjType;}

protected:
    int mObjType;

};

#endif // GAMEOBJ_H
