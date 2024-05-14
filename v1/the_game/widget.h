#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsItem>    //
#include <QGraphicsView>    //
#include <QGraphicsScene>   //
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QResource>
#include <QLabel>
#include <QFont>
#include <QFontMetrics>

#include <qlabelgraphicsitem.h>

#include "defindex.h"
#include "gameobjpool.h"
#include "playership.h"
#include "enemyship.h"
#include "shipammo.h"
#include "enemyammo.h"
#include "playerammo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //move background
    void moveBackground();

    //key event
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    //def-based timer action
    void timerInit();
    void timerON();
    void timerOFF();
    void _timerOFF();
    void _timerON();

    //game scene switching
    void gameExeStart();
    void gameExePause();
    void gameExeContinue();
    void gameExeRestart();
    void gameExeStop();
    void gameExeOver();
    void gameExeWin();

    //scene reset
    void resetGamingScene();

    //generate ammo
    void playerAmmoGen();
    void enemyAmmoGen_Lv1(enemyShip*);
    void enemyAmmoGen_Lv2(enemyShip*);
    void enemyAmmoGen_Lv3(enemyShip*);

    //generate enemies
    void enemyGen_Lv1(int, float xS = 0, float yS = 0, int y = -50); void enemyGen_Lv1_wAmmo(int, float xS = 0, float yS = 0, int y = -50);
    void enemyGen_Lv2(int, float xS = 0, float yS = 0, int y = -50); void enemyGen_Lv2_wAmmo(int, float xS = 0, float yS = 0, int y = -50);
    void enemyGen_Lv3(int, float xS = 0, float yS = 0, int y = -50); void enemyGen_Lv3_wAmmo(int, float xS = 0, float yS = 0, int y = -50);
    void enemyGen_Boss1(int, float xS = 0, float yS = 0, int y = -50);
    void enemyGen_Boss2(int, float xS = 0, float yS = 0, int y = -50);
    void enemyGen_Special1(int, float xS = 0, float yS = 0, int y = -50);
    void enemyGen_Special2(int, float xS = 0, float yS = 0, int y = -50);

    //move ships
    void movePlayerShip();
    void moveEnemyShip();
    void moveProp();

    // void showFloatingText();

    //exam and recycle
    void examCollision();
    void examOverpos();
    void examUpdate(bool);
    void examPropDist();

    //game levels/phases
    void gameThread_Lv1_Ph1(); void gameThread_Lv1_Ph2(); void gameThread_Lv1_Ph3(); void gameThread_Lv1_Ph4(); void gameThread_Lv1_Ph5();
    void gameThread_Lv2_Ph1(); void gameThread_Lv2_Ph2(); void gameThread_Lv2_Ph3(); void gameThread_Lv2_Ph4(); void gameThread_Lv2_Ph5(); void gameThread_Lv2_Ph6(); void gameThread_Lv2_Ph7(); void gameThread_Lv2_Ph8();

    //pause timer
    void pause(QTimer*);

    void showScore();

    void propEffect(int);
    void shieldBroken();
    void collisionImmune();
    void clearGadget();

    void enemyDeath(enemyShip*);

    void setHpBar();

private:
    Ui::Widget *ui;

    QGraphicsView gameView;                       //view
    QGraphicsScene gameScene_startup;             //startup scene
    // QGraphicsView gameView_startup;
    QGraphicsScene gameScene_gaming;              //gaming scene
    QGraphicsScene gameScene_gaming_topCover;              //gaming scene
    QGraphicsScene gameScene_pause;

    QGraphicsPixmapItem gameBackground_1;         //background img
    QGraphicsPixmapItem gameBackground_2;         //background img
    QGraphicsPixmapItem gamePause_0;
    QGraphicsPixmapItem startupBackground;
    QGraphicsPixmapItem gamingSceneLayer_1;
    QGraphicsPixmapItem gamingSceneLayer_2;
    QGraphicsPixmapItem gamingSceneLayer_3;
    QGraphicsPixmapItem pauseGadget_1;
    QGraphicsPixmapItem pauseGadget_2;
    QGraphicsPixmapItem pauseGadget_3;
    QGraphicsPixmapItem pauseGadget_4;
    QGraphicsPixmapItem hpBar;
    QGraphicsPixmapItem hpBarBackground;
    QGraphicsPixmapItem hpBarShade;

    QGraphicsPixmapItem iconSpeedUp;
    QGraphicsPixmapItem iconDoubleScore;
    QGraphicsPixmapItem iconSingleShield;
    QGraphicsPixmapItem iconLaserBeam;
    QGraphicsPixmapItem iconMassiveBomb;

    enum gameSceneLevelIndex{LevelStartup = 1, LevelGaming, LevelPause, LevelOver, LevelWin, LevelSettings};
    int gameSceneLevel = LevelStartup;

    int gameScore = 0;
    int scoreTime = 1;

    QLabel* scoreBoard_above;
    QLabel* scoreBoard_below;
    QFont scoreFont;
    QString str;

    playerShip* playerShip_0 = new playerShip;

    QTimer* timerBackground;
    QTimer* timerPlayerShip;
    QTimer* timerAmmoGen;
    QTimer* timerAmmoMove;
    QTimer* timerEnemyMove;
    QTimer* timerPropMove;
    QTimer* timerThread;
    QTimer* timerBlankInterval;
    QTimer* timerCollisionImmune; const static int immuneTime = 3000; bool collisionImmuneActive = false;
    QTimer* timerImmuneBlinker; const static int blinkerTime= 500; bool blinkerIndex = 0;
    QTimer* timerGadgetBlinker; const static int gBlinkerTime = 7; int gBlinkerIndex = 1;

    QTimer* timerSpeedUp;
    QTimer* timerDoubleScore;
    // QTimer* timerSingleShield;
    // QTimer* timerPropEvaluate;

    int timeIndex;
    int intervalIndex;
    int genCount = 0;
    int ammoCount = 0;
    int killCount = 0;

    int laserCount = 0;
    int bombCount = 0;

    bool updated[2] = {0, 0};
    //bool effects[]

    bool timerThreadRunning = false;
    bool timerIntervalRunning;
    bool timerSpeedUpRunning;
    bool timerDoubleScoreRunning;
    bool timerSingleShieldRunning = false;

    bool possessProp[6];

    QList<int> keyList;
    QList<shipAmmo*> ammoList;
    QList<enemyShip*> enemyList;
    QList<gameProp*> propList;
    QList<QTimer*> tempTimerList;
    QList<QTimer*> deathTimerList;

    QMediaPlayer* mediaBackgroundMusic;
    QMediaPlayer* mediaStartupVideo;
    QVideoWidget* startupVideoWidget;

    QLabelGraphicsItem* scoreLabelItem;
};
#endif // WIDGET_H
