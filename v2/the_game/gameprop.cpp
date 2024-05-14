#include "gameprop.h"

gameProp::gameProp()
{
    mObjType = gameObj::objGameProp;
}

void gameProp::gamePropInit(int propX, int _type, int propY)
{
    this->setPos(propX, propY);
    this->propType = _type;
    switch(_type){
        case gameProp::speedUp:{
            QPixmap propIMG(":/img/img/speed_up.jpg");
            this->setPixmap(propIMG);
            break;
        }
        case gameProp::singleShield:{
            QPixmap propIMG(":/img/img/single_shield.jpg");
            this->setPixmap(propIMG);
            break;
        }
        case gameProp::extraLife:{
            QPixmap propIMG(":/img/img/player_life.jpg");
            this->setPixmap(propIMG);
            break;
        }
        case gameProp::laserBeam:{
            QPixmap propIMG(":/img/img/laser_beam.jpg");
            this->setPixmap(propIMG);
            break;
        }
        case gameProp::doubleScore:{
            QPixmap propIMG(":/img/img/double_score.jpg");
            this->setPixmap(propIMG);
            break;
        }
        case gameProp::massiveBomb:{
            QPixmap propIMG(":/img/img/massive_bomb.jpg");
            this->setPixmap(propIMG);
            break;
        }
    }
}
