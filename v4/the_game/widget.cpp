#include "widget.h"
#include "ui_widget.h"
#include "playership.h"
#include "shipammo.h"
#include "enemyship.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QResource::registerResource("D:/Qt/Projects/the_game/rsrc.rcc");

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(defIndex::screenWidth, defIndex::screenHeight);           //set fixed widget size

    mediaBackgroundMusic = new QMediaPlayer(this);
    QMediaPlaylist* musicList = new QMediaPlaylist(this);
    musicList->addMedia(QMediaContent(QUrl::fromLocalFile("D:/Qt/Projects/the_game/img/game_ost_lmao.mp3")));
    musicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaBackgroundMusic->setPlaylist(musicList);
    this->mediaBackgroundMusic->play();

    gameView.setSceneRect(QRect(0,0,defIndex::screenWidth,defIndex::screenHeight));  //
    gameScene_startup.setSceneRect(QRect(0,0,defIndex::screenWidth,defIndex::screenHeight));//
    gameScene_gaming.setSceneRect(QRect(0,0,defIndex::screenWidth,defIndex::screenHeight)); //

    playerShip_0->setPixmap(QPixmap(":/img/img/player.jpg")); playerShip_0->setZValue(1);
    gameBackground_1.setPixmap(QPixmap(":/img/img/gaming_background.jpg"));  //
    gameBackground_2.setPixmap(QPixmap(":/img/img/gaming_background.jpg")); gameBackground_2.setPos(0,-defIndex::screenHeight);
    gameBackground_3.setPixmap(QPixmap(":/img/img/gaming_background_0.jpg"));  //
    gameBackground_4.setPixmap(QPixmap(":/img/img/gaming_background_0.jpg")); gameBackground_2.setPos(0,-defIndex::screenHeight);
    startupTitle.setPixmap(QPixmap(":/img/img/startup_title.png"));
    gamePause_0.setPixmap(QPixmap(":/img/img/pause_background.png"));
    gamingSceneLayer_1.setPixmap(QPixmap(":/img/img/gaming_layer_1.png")); gamingSceneLayer_1.setZValue(5);
    gamingSceneLayer_2.setPixmap(QPixmap(":/img/img/gaming_layer_above.png")); gamingSceneLayer_2.setZValue(4);
    gamingSceneLayer_3.setPixmap(QPixmap(":/img/img/gaming_layer_below.png")); gamingSceneLayer_3.setPos(0,defIndex::screenHeight-defIndex::barHeight); gamingSceneLayer_3.setZValue(4);
    hpBar.setPixmap(QPixmap(":/img/img/hp_bar.png")); hpBar.setPos(defIndex::screenWidth/2-hpBar.pixmap().width()/2, defIndex::screenHeight-defIndex::barHeight+10); hpBar.setZValue(8);
    hpBarBackground.setPixmap(QPixmap(":/img/img/hp_bar_background.png")); hpBarBackground.setPos(defIndex::screenWidth/2-hpBar.pixmap().width()/2, defIndex::screenHeight-defIndex::barHeight+10); hpBarBackground.setZValue(7);
    hpBarShade.setPixmap(QPixmap(":/img/img/hp_bar_shade.png")); hpBarShade.setPos(0,defIndex::screenHeight-defIndex::barHeight); hpBarShade.setZValue(9);
    playerLaserBeam->setPixmap(QPixmap(":/img/img/player_laser_beam.jpg"));
    pauseGadget_1.setPixmap(QPixmap(":/img/img/gadget_1.png")), pauseGadget_1.setZValue(15);
    pauseGadget_2.setPixmap(QPixmap(":/img/img/gadget_2.png")), pauseGadget_2.setZValue(15);
    pauseGadget_3.setPixmap(QPixmap(":/img/img/gadget_3.png")), pauseGadget_3.setZValue(15);
    pauseGadget_4.setPixmap(QPixmap(":/img/img/gadget_4.png")), pauseGadget_4.setZValue(15);
    gameOverWarning.setPixmap(QPixmap(":/img/img/defeat.png")); gameOverWarning.setZValue(16);
    gameWinInfo.setPixmap(QPixmap(":/img/img/victory.png")); gameWinInfo.setZValue(16);
    gameSettings.setPixmap(QPixmap(":/img/img/settings.png")); gameSettings.setZValue(16);

    iconSpeedUp.setPixmap(QPixmap(":/img/img/speed_up_inactive.jpg")); iconSpeedUp.setPos(25,12); iconSpeedUp.setZValue(5);
    iconDoubleScore.setPixmap(QPixmap(":/img/img/double_score.jpg")); iconDoubleScore. setPos(defIndex::screenWidth/2+50, 30); iconDoubleScore.setZValue(6);
    iconSingleShield.setPixmap(QPixmap(":/img/img/single_shield_inactive.jpg")); iconSingleShield.setPos(60, 12); iconSingleShield.setZValue(5);
    iconLaserBeam.setPixmap(QPixmap(":/img/img/laser_beam_inactive.jpg")); iconLaserBeam.setPos(450, 762); iconLaserBeam.setZValue(5);
    iconMassiveBomb.setPixmap(QPixmap(":/img/img/massive_bomb_inactive.jpg")); iconMassiveBomb.setPos(415, 762); iconMassiveBomb.setZValue(5);

    gameScene_gaming.addItem(&gameBackground_1);   //add background to scene
    gameScene_gaming.addItem(&gameBackground_2);
    gameScene_startup.addItem(&gameBackground_3);   //add background to scene
    gameScene_startup.addItem(&gameBackground_4);
    gameScene_startup.addItem(&startupTitle);

    gameScene_gaming.addItem(&gamingSceneLayer_2);
    gameScene_gaming.addItem(&gamingSceneLayer_3);
    gameScene_gaming.addItem(&hpBar);
    gameScene_gaming.addItem(&hpBarBackground);
    gameScene_gaming.addItem(&hpBarShade);
    gameScene_gaming.addItem(&iconSpeedUp);
    gameScene_gaming.addItem(&iconSingleShield);
    gameScene_gaming.addItem(&iconLaserBeam);
    gameScene_gaming.addItem(&iconMassiveBomb);
    // gameScene_gaming.addItem(&
    // gameScene_gaming.addItem(&

    scoreBoard_above = new QLabel;

    board_laserCount = new QLabel;
    board_bombCount = new QLabel;


    scoreLabelItem = new QLabelGraphicsItem(scoreBoard_above);
    scoreLabelItem->updateScore(gameScore), examUpdate(1);
    scoreLabelItem->setPos((defIndex::screenWidth-scoreLabelItem->boundingRect().width())/2, 0);

    laserCountLabelItem = new QLabelGraphicsItem(board_laserCount);
    bombCountLabelItem = new QLabelGraphicsItem(board_bombCount);
    laserCountLabelItem->updateScore(laserCount);
    bombCountLabelItem->updateScore(bombCount);
    laserCountLabelItem->resetFontSize(12);
    laserCountLabelItem->resetFontBold(1);
    bombCountLabelItem->resetFontSize(12);
    bombCountLabelItem->resetFontBold(1);
    laserCountLabelItem->setPos(iconLaserBeam.x()-80, iconLaserBeam.y()-6);
    bombCountLabelItem->setPos(iconMassiveBomb.x()-80, iconMassiveBomb.y()-6);

    scoreLabelItem->setZValue(5);
    laserCountLabelItem->setZValue(6);
    bombCountLabelItem->setZValue(6);

    gameScene_gaming.addItem(scoreLabelItem);
    gameScene_gaming.addItem(laserCountLabelItem);
    gameScene_gaming.addItem(bombCountLabelItem);

    //gameScene_gaming.addItem(&playerShip_0);       //add ship to scene

    //gameView.setScene(&gameScene_gaming);          //set scene for view
    gameView.setScene(&gameScene_startup);

    gameView.setParent(this);               //pair view to widget
    gameView.show();

    //initialization
    playerShip_0->ammoType = playerAmmo::defaultAmmo;
    gameObjPool::Instance()->objInit();
    timerInit();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::moveBackground(){
    gameBackground_1.moveBy(0,1);
    gameBackground_2.moveBy(0,1);
    if (gameBackground_1.y() >= defIndex::screenHeight)
        gameBackground_1.setY(-defIndex::screenHeight);
    if (gameBackground_2.y() >= defIndex::screenHeight)
        gameBackground_2.setY(-defIndex::screenHeight);
}

void Widget::movePlayerShip(){
    for(int key: keyList){
        switch (key){
        case Qt::Key_W: if(playerShip_0->y()>0) playerShip_0->moveBy(0,-playerShip_0->shipSpeed);break;
        case Qt::Key_A: if(playerShip_0->x()>0) playerShip_0->moveBy(-playerShip_0->shipSpeed,0);break;
        case Qt::Key_S: if(playerShip_0->y()<this->height()-playerShip_0->pixmap().height()-defIndex::barHeight) playerShip_0->moveBy(0,playerShip_0->shipSpeed);break;
        case Qt::Key_D: if(playerShip_0->x()<this->width()-playerShip_0->pixmap().width()) playerShip_0->moveBy(playerShip_0->shipSpeed,0);break;
        }
    }
    if(laserBeamActive){
        for(int key: keyList){
            switch (key){
            case Qt::Key_W: if(playerShip_0->y()>0) playerLaserBeam->moveBy(0,-playerLaserBeam->shipSpeed);break;
            case Qt::Key_A: if(playerShip_0->x()>0) playerLaserBeam->moveBy(-playerLaserBeam->shipSpeed,0);break;
            case Qt::Key_S: if(playerShip_0->y()<this->height()-playerShip_0->pixmap().height()-defIndex::barHeight) playerLaserBeam->moveBy(0,playerLaserBeam->shipSpeed);break;
            case Qt::Key_D: if(playerShip_0->x()<this->width()-playerShip_0->pixmap().width()) playerLaserBeam->moveBy(playerLaserBeam->shipSpeed,0);break;
            }
        }
    }
}

void Widget::keyPressEvent(QKeyEvent* event){
    if(gameSceneLevel == Widget::LevelGaming){
        switch (event->key()){
        case Qt::Key_W:
        case Qt::Key_A:
        case Qt::Key_S:
        case Qt::Key_D:
        case Qt::Key_M:
            keyList.append(event->key());
        }
    }
    if(event->key() == Qt::Key_Return && gameSceneLevel == Widget::LevelStartup)
    {
        gameExeStart();
        gameSceneLevel = Widget::LevelGaming;
    }
    if(event->key() == Qt::Key_Escape)
    {
        if(gameSceneLevel == Widget::LevelStartup){
            this->close();
        }
        else if(gameSceneLevel == Widget::LevelGaming){
            gameExePause();
            gameSceneLevel = Widget::LevelPause;
            return;
        }
        else if(gameSceneLevel == Widget::LevelPause){
            gameExeContinue();
            gameSceneLevel = Widget::LevelGaming;
            return;
        }
        else if(gameSceneLevel == Widget::LevelSettings){
            gameScene_gaming.removeItem(&gameSettings);
            gameScene_gaming.addItem(&gamePause_0);
            timerGadgetBlinker->start(gBlinkerTime);
            gameSceneLevel = Widget::LevelPause;
        }
        // gameView.setScene(&gameScene_startup);
        // this->mediaBackgroundMusic->play();
    }
    if(event->key() == Qt::Key_R && (gameSceneLevel == Widget::LevelPause || gameSceneLevel == Widget::LevelOver || gameSceneLevel == Widget::LevelWin)){
        gameExeRestart();
        gameSceneLevel = Widget::LevelGaming;
    }
    if(event->key() == Qt::Key_Backspace && (gameSceneLevel == Widget::LevelPause || gameSceneLevel == Widget::LevelOver || gameSceneLevel == Widget::LevelWin)){
        gameExeStop();
        gameSceneLevel = Widget::LevelStartup;
    }
    if(event->key() == Qt::Key_N && gameSceneLevel == Widget::LevelGaming && laserCount && laserPermission){
        triggeredLaserBeam();
        laserCount--; laserCountLabelItem->updateScore(laserCount);
        laserPermission = 0;
        iconLaserBeam.setPixmap(QPixmap(":/img/img/laser_beam_inactive.jpg"));
        QTimer* coldDown = new QTimer;
        tempTimerList.append(coldDown);
        connect(coldDown, &QTimer::timeout, [this, coldDown]{
            laserPermission = 1;
            if(laserCount){iconLaserBeam.setPixmap(QPixmap(":/img/img/laser_beam.jpg"));}
            tempTimerList.removeOne(coldDown);
            delete coldDown;
        });
        coldDown->start(8800);
    }
    if(event->key() == Qt::Key_B && gameSceneLevel == Widget::LevelGaming && bombCount && bombPermission){
        triggeredMassiveBomb();
        bombCount--; bombCountLabelItem->updateScore(bombCount);
        bombPermission = 0;
        iconMassiveBomb.setPixmap(QPixmap(":/img/img/massive_bomb_inactive.jpg"));
        QTimer* coldDown = new QTimer;
        tempTimerList.append(coldDown);
        connect(coldDown, &QTimer::timeout, [this, coldDown]{
            bombPermission = 1;
            if(bombCount){iconMassiveBomb.setPixmap(QPixmap(":/img/img/massive_bomb.jpg"));}
            tempTimerList.removeOne(coldDown);
            delete coldDown;
        });
        coldDown->start(10800);
    }
    if(event->key() == Qt::Key_E && gameSceneLevel == Widget::LevelPause){
        gameScene_gaming.removeItem(&gamePause_0);
        gameScene_gaming.addItem(&gameSettings);
        timerGadgetBlinker->stop(), clearGadget(), gBlinkerIndex = 1;
        gameSceneLevel = Widget::LevelSettings;
    }
}

void Widget::keyReleaseEvent(QKeyEvent* event){
    if(keyList.contains(event->key()))
        keyList.removeOne(event->key());
}

void Widget::gameExeStart(){
    timerON();
    gameThread_Lv1_Ph1();
    mediaBackgroundMusic->stop();
    // playerShip_0->setPixmap(QPixmap(":/img/img/player.jpg"));
    playerShip_0->setPos(225,600);
    lifeIconInit();
    gameScene_gaming.addItem(playerShip_0);
    gameScene_gaming.addItem(&gamingSceneLayer_1);
    gameView.setScene(&gameScene_gaming);
    gameView.show();
}

void Widget::gameExePause(){
    timerOFF();
    // mediaBackgroundMusic->stop();
    timerGadgetBlinker->start(gBlinkerTime);
    gameScene_gaming.removeItem(&gamingSceneLayer_1);
    gameScene_gaming.addItem(&gamePause_0);
    gamePause_0.setZValue(11);
}

void Widget::gameExeContinue(){
    timerON();
    _timerON();
    // mediaBackgroundMusic->stop();
    timerGadgetBlinker->stop(), clearGadget(), gBlinkerIndex = 1;
    gameScene_gaming.addItem(&gamingSceneLayer_1);
    gameScene_gaming.removeItem(&gamePause_0);
}

void Widget::gameExeRestart(){
    //_timerOFF();
    resetGamingScene();
    lifeIconInit();
    // mediaBackgroundMusic->stop();
    timerON();
    timerGadgetBlinker->stop(), clearGadget(), gBlinkerIndex = 1;
    gameScene_gaming.removeItem(&gamePause_0);
    gameScene_gaming.removeItem(&gameOverWarning);
    gameScene_gaming.removeItem(&gameWinInfo);
    gameScene_gaming.addItem(&gamingSceneLayer_1);
    playerShip_0->setPos(225,600);
    gameThread_Lv1_Ph1();
}

void Widget::gameExeStop(){
    gameScene_gaming.removeItem(&gamePause_0);
    _timerOFF();
    timerGadgetBlinker->stop(), clearGadget(), gBlinkerIndex = 1;
    resetGamingScene();
    gameView.setScene(&gameScene_startup);
    this->mediaBackgroundMusic->play();
}

void Widget::gameExeOver(){
    playerShip_0->shipHP = 0;
    gameScene_gaming.addItem(&gameOverWarning);
    timerOFF();
    //_timerOFF();
    gameSceneLevel = Widget::LevelOver;
    // play defeat music
}

void Widget::gameExeWin(){
    gameScene_gaming.addItem(&gameWinInfo);
    timerOFF();
    _timerOFF();
    gameSceneLevel = Widget::LevelWin;
}

void Widget::resetGamingScene(){
    for(auto ammo: ammoList){
        gameScene_gaming.removeItem(ammo);
        gameObjPool::Instance()->objRcycl(ammo);
        ammoList.removeOne(ammo);
    }
    for(auto enemy: enemyList){
        gameScene_gaming.removeItem(enemy);
        gameObjPool::Instance()->objRcycl(enemy);
        enemyList.removeOne(enemy);
    }
    for(auto prop: propList){
        gameScene_gaming.removeItem(prop);
        gameObjPool::Instance()->objRcycl(prop);
        propList.removeOne(prop);
    }
    timerThreadRunning = false;
    timerIntervalRunning = false;
    timerSpeedUpRunning = false;
    timerDoubleScoreRunning = false;
    timerSingleShieldRunning = false;
    collisionImmuneActive = false;
    laserBeamActive = false;
    laserPermission = true;
    bombPermission = true;
    blinkerIndex = 0;
    playerShip_0->shipLife=playerShip_0->maxLife;
    playerShip_0->shipHP=playerShip_0->maxHealth;
    setHpBar();
    playerShip_0->setPixmap(QPixmap(":/img/img/player.jpg"));
    iconSpeedUp.setPixmap(QPixmap(":/img/img/speed_up_inactive.jpg"));
    iconDoubleScore.setPixmap(QPixmap(":/img/img/double_score.jpg"));
    iconSingleShield.setPixmap(QPixmap(":/img/img/single_shield_inactive.jpg"));
    iconLaserBeam.setPixmap(QPixmap(":/img/img/laser_beam_inactive.jpg"));
    iconMassiveBomb.setPixmap(QPixmap(":/img/img/massive_bomb_inactive.jpg"));
    for(int i = 0; i <5; i++) {gameScene_gaming.removeItem(&iconLife[i]);}
    gameScore = 0;
    scoreLabelItem->updateScore(gameScore), examUpdate(1);
    genCount = 0;
    examUpdate(0);
    killCount = 0;
}

void Widget::playerAmmoGen(){
    if(keyList.contains(Qt::Key_M)){
        QPixmap ammoIMG_1(":/img/img/player_ammo_lv1.jpg");
        QPixmap ammoIMG_2(":/img/img/player_ammo_lv2.jpg");
        switch(playerShip_0->ammoType){
            case playerAmmo::defaultAmmo:{
                playerAmmo* p_ammo = (playerAmmo*)gameObjPool::Instance()->objObtn(gameObj::objPlayerAmmo);
                p_ammo->playerAmmoInit(playerShip_0->x()+playerShip_0->pixmap().width()/2-ammoIMG_1.width()/2, playerShip_0->y(), ammoIMG_1, playerShip_0->ammoType);
                ammoList.append(p_ammo);
                //p_ammo->playerAmmoGenSound(playerAmmo::defaultAmmo);
                gameScene_gaming.addItem(p_ammo);
                break;
            }
            case playerAmmo::advancedAmmo_Lv1:{
                playerAmmo* p_ammo_1 = (playerAmmo*)gameObjPool::Instance()->objObtn(gameObj::objPlayerAmmo);
                playerAmmo* p_ammo_2 = (playerAmmo*)gameObjPool::Instance()->objObtn(gameObj::objPlayerAmmo);
                p_ammo_1->playerAmmoInit(playerShip_0->x(), playerShip_0->y(), ammoIMG_1, playerShip_0->ammoType);
                p_ammo_2->playerAmmoInit(playerShip_0->x()+playerShip_0->pixmap().width()-ammoIMG_1.width(), playerShip_0->y(), ammoIMG_1, playerShip_0->ammoType);
                ammoList.append(p_ammo_1), ammoList.append(p_ammo_2);
                gameScene_gaming.addItem(p_ammo_1), gameScene_gaming.addItem(p_ammo_2);
                //sound
                break;
            }
            case playerAmmo::advancedAmmo_Lv2:{
                playerAmmo* p_ammo_1 = (playerAmmo*)gameObjPool::Instance()->objObtn(gameObj::objPlayerAmmo);
                playerAmmo* p_ammo_2 = (playerAmmo*)gameObjPool::Instance()->objObtn(gameObj::objPlayerAmmo);
                playerAmmo* p_ammo_3 = (playerAmmo*)gameObjPool::Instance()->objObtn(gameObj::objPlayerAmmo);
                p_ammo_1->playerAmmoInit(playerShip_0->x()-ammoIMG_1.width(), playerShip_0->y()+ammoIMG_1.height(), ammoIMG_1, playerShip_0->ammoType);
                p_ammo_2->playerAmmoInit(playerShip_0->x()+playerShip_0->pixmap().width(), playerShip_0->y()+ammoIMG_1.height(), ammoIMG_1, playerShip_0->ammoType);
                p_ammo_3->playerAmmoInit(playerShip_0->x()+playerShip_0->pixmap().width()/2-ammoIMG_2.width()/2, playerShip_0->y()-ammoIMG_2.height()/2, ammoIMG_2, playerShip_0->ammoType);
                ammoList.append(p_ammo_1), ammoList.append(p_ammo_2), ammoList.append(p_ammo_3);
                gameScene_gaming.addItem(p_ammo_1), gameScene_gaming.addItem(p_ammo_2), gameScene_gaming.addItem(p_ammo_3);
                break;
            }
        }
    }
}

void Widget::enemyGen_Lv1(int x, float xS, float yS, int y){
    QPixmap enemyIMG(":/img/img/enemy_lv1.jpg");
    // int randX = qrand()%(defIndex::screenWidth-enemyIMG.width());
    enemyShip* e_ship = (enemyShip*)gameObjPool::Instance()->objObtn(gameObj::objEnemyShip);
    e_ship->enemyShipInit(enemyIMG,enemyShip::enemy_Lv1,x, xS, yS, y);
    enemyList.append(e_ship);
    gameScene_gaming.addItem(e_ship);
}

void Widget::enemyGen_Lv1_wAmmo(int x, float xS, float yS, int y){
    QPixmap enemyIMG(":/img/img/enemy_lv1.jpg");
    // int randX = qrand()%(defIndex::screenWidth-enemyIMG.width());
    enemyShip* e_ship = (enemyShip*)gameObjPool::Instance()->objObtn(gameObj::objEnemyShip);
    e_ship->enemyShipInit(enemyIMG,enemyShip::enemy_Lv1,x, xS, yS, y);
    enemyList.append(e_ship);
    gameScene_gaming.addItem(e_ship);
    e_ship->temp_timer = new QTimer;
    e_ship->timed = 1;
    tempTimerList.append(e_ship->temp_timer);
    connect(e_ship->temp_timer, &QTimer::timeout, this, [&, e_ship]{
        enemyAmmoGen_Lv1(e_ship);
        // else {e_ship->temp_timer->stop();}
    });
    e_ship->temp_timer->start(600);
}

void Widget::enemyAmmoGen_Lv1(enemyShip* ship){
    QPixmap ammoIMG(":/img/img/enemy_ammo_lv1.jpg");
    enemyAmmo* e_ammo_1 = (enemyAmmo*)gameObjPool::Instance()->objObtn(gameObj::objEnemyAmmo);
    enemyAmmo* e_ammo_2 = (enemyAmmo*)gameObjPool::Instance()->objObtn(gameObj::objEnemyAmmo);
    e_ammo_1->enemyAmmoInit(ship->x(), ship->y()+ship->pixmap().height(), ammoIMG, enemyAmmo::enemy_Lv1);
    e_ammo_2->enemyAmmoInit(ship->x()+ship->pixmap().width()-ammoIMG.width(), ship->y()+ship->pixmap().height(), ammoIMG, enemyAmmo::enemy_Lv1);
    //p_ammo->playerAmmoGenSound(playerAmmo::defaultAmmo);
    ammoList.append(e_ammo_1), ammoList.append(e_ammo_2);
    gameScene_gaming.addItem(e_ammo_1), gameScene_gaming.addItem(e_ammo_2);
}

void Widget::enemyGen_Lv2(int x, float xS, float yS, int y){
    QPixmap enemyIMG(":/img/img/enemy_lv2.jpg");
    // int randX = qrand()%(defIndex::screenWidth-enemyIMG.width());
    enemyShip* e_ship = (enemyShip*)gameObjPool::Instance()->objObtn(gameObj::objEnemyShip);
    e_ship->enemyShipInit(enemyIMG,enemyShip::enemy_Lv2,x, xS, yS, y);
    enemyList.append(e_ship);
    gameScene_gaming.addItem(e_ship);
}

// void Widget::enemyGen_Lv2_wAmmo(int x, float xS, float yS, int y){
//     QPixmap enemyIMG(":/img/img/enemy_lv2.jpg");
//     // int randX = qrand()%(defIndex::screenWidth-enemyIMG.width());
//     enemyShip* e_ship = (enemyShip*)gameObjPool::Instance()->objObtn(gameObj::objEnemyShip);
//     e_ship->enemyShipInit(enemyIMG,enemyShip::enemy_Lv2,x, xS, yS, y);
//     enemyList.append(e_ship);
//     gameScene_gaming.addItem(e_ship);
//     tempTimerList.append(e_ship->temp_timer);
//     connect(e_ship->temp_timer, &QTimer::timeout, this, [&, e_ship]{
//         enemyAmmoGen_Lv2(e_ship);
//         // else {e_ship->temp_timer->stop();}
//     });
//     e_ship->temp_timer->start(800);
// }

// void Widget::enemyAmmoGen_Lv2(enemyShip* ship){
//     QPixmap ammoIMG(":/img/img/enemy_ammo_lv2.jpg");
//     enemyAmmo* e_ammo_1 = (enemyAmmo*)gameObjPool::Instance()->objObtn(gameObj::objEnemyAmmo);
//     enemyAmmo* e_ammo_2 = (enemyAmmo*)gameObjPool::Instance()->objObtn(gameObj::objEnemyAmmo);
//     e_ammo_1->enemyAmmoInit(ship->x(), ship->y()+ship->pixmap().height(), ammoIMG, enemyAmmo::enemy_Lv2);
//     e_ammo_2->enemyAmmoInit(ship->x()+ship->pixmap().width()-ammoIMG.width(), ship->y()+ship->pixmap().height(), ammoIMG, enemyAmmo::enemy_Lv2);
//     //p_ammo->playerAmmoGenSound(playerAmmo::defaultAmmo);
//     ammoList.append(e_ammo_1), ammoList.append(e_ammo_2);
//     gameScene_gaming.addItem(e_ammo_1), gameScene_gaming.addItem(e_ammo_2);
// }

void Widget::enemyGen_Lv3(int x, float xS, float yS, int y){
    QPixmap enemyIMG(":/img/img/enemy_lv3.jpg");
    // int randX = qrand()%(defIndex::screenWidth-enemyIMG.width());
    enemyShip* e_ship = (enemyShip*)gameObjPool::Instance()->objObtn(gameObj::objEnemyShip);
    e_ship->enemyShipInit(enemyIMG,enemyShip::enemy_Lv3,x, xS, yS, y);
    enemyList.append(e_ship);
    gameScene_gaming.addItem(e_ship);
}

void Widget::enemyGen_Lv3_wAmmo(int x, float xS, float yS, int y){
    QPixmap enemyIMG(":/img/img/enemy_lv3.jpg");
    // int randX = qrand()%(defIndex::screenWidth-enemyIMG.width());
    enemyShip* e_ship = (enemyShip*)gameObjPool::Instance()->objObtn(gameObj::objEnemyShip);
    e_ship->enemyShipInit(enemyIMG,enemyShip::enemy_Lv3,x, xS, yS, y);
    enemyList.append(e_ship);
    gameScene_gaming.addItem(e_ship);
    enemyAmmoGen_Lv3(e_ship);
}

void Widget::enemyAmmoGen_Lv3(enemyShip* ship){
    QPixmap ammoIMG(":/img/img/enemy_ammo_lv3.jpg");
    enemyAmmo* e_ammo = (enemyAmmo*)gameObjPool::Instance()->objObtn(gameObj::objEnemyAmmo);
    e_ammo->enemyAmmoInit(ship->x()-ammoIMG.width()/2, ship->y()+ship->pixmap().height(), ammoIMG, enemyAmmo::enemy_Lv3);
    ammoList.append(e_ammo);
    gameScene_gaming.addItem(e_ammo);
}

// void Widget::enemyGen_Boss1(int, int){

// }

// void Widget::enemyGen_Boss2(int, int){

// }

// void Widget::enemyGen_Special1(int, int){

// }

// void Widget::enemyGen_Special2(int, int){

// }


void Widget::moveEnemyShip(){
    for(auto enemy: enemyList){
        enemy->moveBy(enemy->xSpeed,enemy->ySpeed);
    }
}

void Widget::moveProp(){
    for(auto prop: propList){
        prop->moveBy(0, 0.3);
    }
}

void Widget::examCollision(){
    for(int j = 0; j < enemyList.size(); j++){
        if(enemyList[j]->collidesWithItem(playerShip_0) && !collisionImmuneActive)
        {
            collisionImmune();
            enemyDeath(enemyList[j]);
            // gameScene_gaming.removeItem(enemyList[j]);
            // gameObjPool::Instance()->objRcycl(enemyList[j]);
            // enemyList.removeAt(j);
            if (timerSingleShieldRunning) {shieldBroken(); return;}
            playerShip_0->shipLife -= 1, setLifeIcon();
            if(playerShip_0->shipLife <= 0){
                // show
                gameExeOver();
                return;
            }
            else {playerShip_0->shipHP = playerShip_0->maxHealth;}
            setHpBar();
            break;
        }
    }
    for(int i = 0; i < ammoList.size(); i++){
        if(ammoList[i]->collidesWithItem(playerShip_0) && ammoList[i]->getType() == gameObj::objEnemyAmmo && !collisionImmuneActive)
        {
            collisionImmune();
            int _hp = 0; _hp = ammoList[i]->ammoATK;
            gameScene_gaming.removeItem(ammoList[i]);
            gameObjPool::Instance()->objRcycl(ammoList[i]);
            ammoList.removeAt(i);
            if (timerSingleShieldRunning) {shieldBroken(); return;}
            playerShip_0->shipHP -= _hp;
            setHpBar();
            if(playerShip_0->shipHP <= 0){
                playerShip_0->shipLife -= 1, setLifeIcon();
                if(playerShip_0->shipLife <= 0){
                    // show
                    gameExeOver();
                    return;
                }
                else{
                    playerShip_0->shipHP += playerShip_0->maxHealth;
                    setHpBar();
                    // show
                }
            }
            break;
        }
        for(int j = 0; j < enemyList.size(); j++){
            if(ammoList[i]->collidesWithItem(enemyList[j]) && ammoList[i]->getType() == gameObj::objPlayerAmmo)
            {
                enemyList[j]->shipHP -= ammoList[i]->ammoATK;
                gameScene_gaming.removeItem(ammoList[i]);
                gameObjPool::Instance()->objRcycl(ammoList[i]);
                ammoList.removeAt(i);
                if(enemyList[j]->shipHP <= 0){
                    gameScore += enemyList[j]->destroyScore*scoreTime;
                    killCount++, examPropDist();
                    scoreLabelItem->updateScore(gameScore), examUpdate(1);
                    enemyDeath(enemyList[j]);
                    break;
                    // gameScene_gaming.removeItem(enemyList[j]);
                    // gameObjPool::Instance()->objRcycl(enemyList[j]);
                    // enemyList.removeAt(j);
                    // play soundfx "destroy"
                }
                else{
                    // play soundfx "hit"
                };
            }
        }
    }
    for(auto prop: propList){
        if(playerShip_0->collidesWithItem(prop)){
            propEffect(prop->propType);
            gameScene_gaming.removeItem(prop);
            gameObjPool::Instance()->objRcycl(prop);
            propList.removeOne(prop);
        }
    }
    if(laserBeamActive){
        for(int j = 0; j < enemyList.size(); j++){
            if(playerLaserBeam->collidesWithItem(enemyList[j])){
                qDebug() <<"yes";
                enemyList[j]->shipHP -= 1;
                if(enemyList[j]->shipHP <= 0){
                    gameScore += enemyList[j]->destroyScore*scoreTime;
                    killCount++, examPropDist();
                    scoreLabelItem->updateScore(gameScore), examUpdate(1);
                    enemyDeath(enemyList[j]);
                    break;
                    // gameScene_gaming.removeItem(enemyList[j]);
                    // gameObjPool::Instance()->objRcycl(enemyList[j]);
                    // enemyList.removeAt(j);
                    // play soundfx "destroy"
                }
                else{
                    // play soundfx "hit"
                };
            }

        }
    }
}

void Widget::examOverpos(){
    for(auto ammo: ammoList){
        if(ammo->y()<-(ammo->pixmap().height())||ammo->y()>defIndex::screenHeight-defIndex::barHeight){
            gameScene_gaming.removeItem(ammo);
            gameObjPool::Instance()->objRcycl(ammo);
            ammoList.removeOne(ammo);
        }
    }
    for(auto enemy: enemyList){
        if(enemy->y()>defIndex::screenHeight-defIndex::barHeight || enemy->shipHP <= 0){
            if(enemy->timed){
                enemy->temp_timer->stop();
                tempTimerList.removeOne(enemy->temp_timer);
                delete enemy->temp_timer; enemy->timed = 0;
            }
            gameScene_gaming.removeItem(enemy);
            gameObjPool::Instance()->objRcycl(enemy);
            enemyList.removeOne(enemy);
        }
    }
    for(auto prop: propList){
        if(prop->y()>defIndex::screenHeight-defIndex::barHeight){
            gameScene_gaming.removeItem(prop);
            gameObjPool::Instance()->objRcycl(prop);
            propList.removeOne(prop);
        }
    }
}

void Widget::examUpdate(bool b){
    if(b){
        if(gameScore>=3000 && !updated[0]) {playerShip_0->ammoType = playerAmmo::advancedAmmo_Lv1; updated[0] = true;}
        if(gameScore>=10000 && !updated[1]) {playerShip_0->ammoType = playerAmmo::advancedAmmo_Lv2; updated[1] = true;}
    }
    else {playerShip_0->ammoType = playerAmmo::defaultAmmo; updated[0] = false, updated[1] = false;}
}

void Widget::examPropDist(){
    if(killCount>=10){
        int i = killCount/10;
        while(i){
            int randX = qrand()%(defIndex::screenWidth-75) + 25;
            int randI = qrand()%6;
            gameProp* m_prop = new gameProp;
            m_prop->gamePropInit(randX, randI);
            gameScene_gaming.addItem(m_prop);
            propList.append(m_prop);
            i--;
        }
        killCount%=10;
    }
}

void Widget::timerInit(){
    timerBackground = new QTimer(this);
    connect(timerBackground, &QTimer::timeout, this, &Widget::moveBackground);
    timerPlayerShip = new QTimer(this);
    connect(timerPlayerShip, &QTimer::timeout, this, &Widget::movePlayerShip);
    timerAmmoGen = new QTimer(this);
    connect(timerAmmoGen, &QTimer::timeout, this, &Widget::playerAmmoGen);

    timerAmmoMove = new QTimer(this);
    connect(timerAmmoMove, &QTimer::timeout, [this](){
        for(auto ammo: ammoList)
            ammo->moveAmmo();
        examCollision();
        examOverpos();
    });
    timerEnemyMove = new QTimer(this);
    connect(timerEnemyMove, &QTimer::timeout, this, &Widget::moveEnemyShip);
    timerPropMove = new QTimer(this);
    connect(timerPropMove, &QTimer::timeout, this, &Widget::moveProp);
    timerSpeedUp = new QTimer(this);
    connect(timerSpeedUp, &QTimer::timeout, [this]{
        playerShip_0->shipSpeed = 0.6;
        iconSpeedUp.setPixmap(QPixmap(":/img/img/speed_up_inactive.jpg"));
    });
    timerDoubleScore = new QTimer(this);
    connect(timerDoubleScore, &QTimer::timeout, [this]{
        scoreTime = 1;
        gameScene_gaming.removeItem(&iconDoubleScore);
    });
    timerImmuneBlinker = new QTimer(this);
    connect(timerImmuneBlinker, &QTimer::timeout, [this]{
        if(blinkerIndex) {playerShip_0->setPixmap(QPixmap(":/img/img/player.jpg")); blinkerIndex = false;}
        else {playerShip_0->setPixmap(QPixmap(":/img/img/player_immune.jpg")); blinkerIndex = true;}
    });
    timerCollisionImmune = new QTimer(this);
    connect(timerCollisionImmune, &QTimer::timeout, [this]{
        collisionImmuneActive = false;
        timerImmuneBlinker->stop();
        playerShip_0->setPixmap(QPixmap(":/img/img/player.jpg"));
    });
    timerGadgetBlinker = new QTimer(this);
    connect(timerGadgetBlinker, &QTimer::timeout, [this]{
        switch(gBlinkerIndex){
        case 100: {gameScene_gaming.addItem(&pauseGadget_1); gBlinkerIndex++; break;}
        case 140: {gameScene_gaming.removeItem(&pauseGadget_1); gameScene_gaming.addItem(&pauseGadget_2); gBlinkerIndex++; break;}
        case 185: {gameScene_gaming.removeItem(&pauseGadget_2); gameScene_gaming.addItem(&pauseGadget_3); gBlinkerIndex++; break;}
        case 240: {gameScene_gaming.removeItem(&pauseGadget_3); gameScene_gaming.addItem(&pauseGadget_4); gBlinkerIndex++; break;}
        case 440: {gameScene_gaming.removeItem(&pauseGadget_4); gameScene_gaming.addItem(&pauseGadget_3); gBlinkerIndex++; break;}
        case 450: {gameScene_gaming.removeItem(&pauseGadget_3); gameScene_gaming.addItem(&pauseGadget_2); gBlinkerIndex++; break;}
        case 455: {gameScene_gaming.removeItem(&pauseGadget_2); gameScene_gaming.addItem(&pauseGadget_1); gBlinkerIndex++; break;}
        case 461: {gameScene_gaming.removeItem(&pauseGadget_1); gBlinkerIndex++; break;}
        case 500: {gBlinkerIndex = 1; break;}
        default: {gBlinkerIndex++; break;}
        }
    });
}

void Widget::timerON(){
    timerBackground->start(defIndex::backgroundUpdateFreq);
    timerPlayerShip->start(defIndex::playerMoveUpdateFreq);
    timerAmmoGen->start(playerShip_0->ammoFreq);
    timerAmmoMove->start(defIndex::ammoMoveUpdateFreq);
    timerPropMove->start(defIndex::ammoMoveUpdateFreq);
    // timerEnemyGen->start(defIndex::enemyGenFreq);
    timerEnemyMove->start(defIndex::enemyMoveUpdateFreq);
    for(auto timer: tempTimerList) {timer->start();}
    for(auto timer: deathTimerList) {timer->start();}
}

void Widget::timerOFF(){
    timerBackground->stop();
    timerPlayerShip->stop();
    timerAmmoGen->stop();
    timerAmmoMove->stop();
    // timerEnemyGen->stop();
    timerEnemyMove->stop();
    timerPropMove->stop();
    timerThreadRunning = timerThread->isActive();
    if(timerThreadRunning) {pause(timerThread);}
    timerIntervalRunning = timerBlankInterval->isActive();
    if(timerIntervalRunning) {pause(timerBlankInterval);}
    timerSpeedUpRunning = timerSpeedUp->isActive();
    if(timerSpeedUpRunning) {pause(timerSpeedUp);}
    timerDoubleScoreRunning = timerDoubleScore->isActive();
    if(timerDoubleScoreRunning) {pause(timerDoubleScore);}
    for(auto timer: tempTimerList) {pause(timer);}
    for(auto timer: deathTimerList) {pause(timer);}
    if(collisionImmuneActive) {pause(timerCollisionImmune), pause(timerImmuneBlinker);}
}

void Widget::_timerOFF(){
    timerThread->stop();
    timerBlankInterval->stop();
    if(timerThread != nullptr) delete timerThread;
    if(timerBlankInterval != nullptr) delete timerBlankInterval;
    if(timerSpeedUpRunning) {timerSpeedUp->stop();}
    if(timerDoubleScoreRunning) {timerDoubleScore->stop();}
    if(collisionImmuneActive) {timerCollisionImmune->stop(), timerImmuneBlinker->stop();}
    for(auto timer: tempTimerList){
        tempTimerList.removeOne(timer);
        delete timer;
    }
    for(auto timer: deathTimerList){
        tempTimerList.removeOne(timer);
        delete timer;
    }
}

void Widget::_timerON(){
    if(timerThreadRunning) {timerThread->start(); timerThreadRunning = false;}
    if(timerIntervalRunning) {timerBlankInterval->start(); timerIntervalRunning = false;}
    if(timerSpeedUpRunning) {timerSpeedUp->start(); timerSpeedUpRunning = false;}
    if(timerDoubleScoreRunning) {timerDoubleScore->start(); timerDoubleScoreRunning = false;}
}


void Widget::gameThread_Lv1_Ph1(){
    // play media here
    timerThread = new QTimer(this);
    timerBlankInterval = new QTimer(this);

    timeIndex = 500;
    connect(timerThread, &QTimer::timeout, this, [&, x_1 = 50, x_2 = 400]{
        if(genCount < 5) {Widget::enemyGen_Lv1(x_1, 0.1); Widget::enemyGen_Lv1(x_2, -0.1); genCount++; timerThread->setInterval(timeIndex);}
        else {timerThread->stop(); genCount = 0; gameThread_Lv1_Ph2();}
    });
    timerThread->start(timeIndex);
}

void Widget::gameThread_Lv1_Ph2(){
    delete timerThread;
    timerThread = new QTimer(this);
    intervalIndex = 3000;
    timeIndex = 500;
    connect(timerBlankInterval, &QTimer::timeout, [this](){timerBlankInterval->stop(); timerThread->start(timeIndex);});
    connect(timerThread, &QTimer::timeout, this, [&, x_1 = 50, x_2 = 400, x_3 = 225]{
        if(genCount < 5) {Widget::enemyGen_Lv2(x_1); genCount++; timerThread->setInterval(timeIndex);}
        else if(genCount >= 5 && genCount <8) {Widget::enemyGen_Lv2(x_1); Widget::enemyGen_Lv2(x_2); genCount++; timerThread->setInterval(timeIndex);}
        else if(genCount >= 8 && genCount <10) {Widget::enemyGen_Lv2(x_2); genCount++; timerThread->setInterval(timeIndex);}
        else if(genCount >= 10 && genCount <13) {Widget::enemyGen_Lv2(x_2); Widget::enemyGen_Lv2(x_3); genCount++; timerThread->setInterval(timeIndex);}
        else if(genCount >= 13 && genCount < 16) {Widget::enemyGen_Lv2(x_3); genCount++; timerThread->setInterval(timeIndex);}
        else {timerThread->stop(); genCount = 0; gameThread_Lv1_Ph3();}
    });
    timerBlankInterval->start(intervalIndex);
}

void Widget::gameThread_Lv1_Ph3(){
    delete timerThread;
    delete timerBlankInterval;
    timerThread = new QTimer(this);
    timerBlankInterval = new QTimer(this);
    timeIndex = 5000;
    connect(timerThread, &QTimer::timeout, this, [&, x_0 = 0, x_n = 450]{
        if(genCount < 5){
            int randX_1 = (qrand()%10)*50;
            int randX_2 = (randX_1 + 200)%500;
            for(int x = x_0; x <= x_n; x+=50){
                if(x == randX_1 || x == randX_2){
                    Widget::enemyGen_Lv1_wAmmo(x);
                }
                else{
                    Widget::enemyGen_Lv1(x);
                }
            }
            genCount++; timerThread->setInterval(timeIndex);}
        else {timerThread->stop(); genCount = 0; gameThread_Lv1_Ph4();}
    });
    timerThread->start(timeIndex);
}

void Widget::gameThread_Lv1_Ph4(){
    delete timerThread;
    delete timerBlankInterval;
    for(auto timer: tempTimerList) {timer->stop(); tempTimerList.removeOne(timer);}
    timerThread = new QTimer(this);
    timerBlankInterval = new QTimer(this);
    timeIndex = 500;
    intervalIndex = 500;
    connect(timerBlankInterval, &QTimer::timeout, [this](){timerBlankInterval->stop(); timerThread->start(timeIndex);});
    connect(timerThread, &QTimer::timeout, this, [&, x_1 = 50, x_2 = 400]{
        int randX = qrand()%(defIndex::screenWidth-50);
        float randXS = float(qrand()%10)/100;
        int randSign = qrand()%2;
        if(randSign) {randXS *= (-1.0);}
        if(genCount < 35){
            Widget::enemyGen_Lv3_wAmmo(randX, randXS);
            if(genCount%5==2){
                Widget::enemyGen_Lv1(x_1), Widget::enemyGen_Lv1(x_2);
            }
            genCount++; timerThread->setInterval(timeIndex);
        }
        else {timerThread->stop(); genCount = 0; /*gameThread_Lv1_Ph5();*/}
    });
    timerBlankInterval->start(intervalIndex);
}

void Widget::gameThread_Lv1_Ph5(){
    delete timerThread;
    delete timerBlankInterval;
    timerThread = new QTimer(this);
    timerBlankInterval = new QTimer(this);
    intervalIndex = 80000;
    connect(timerBlankInterval, &QTimer::timeout, [this](){timerBlankInterval->stop(); gameExeWin();});
    timerBlankInterval->start(intervalIndex);
}

void Widget::gameThread_Lv2_Ph1(){
    // play media here
    // change background here
}

void Widget::pause(QTimer* timer){
    int remain = timer->remainingTime();
    timer->stop();
    timer->setInterval(remain);
}

void Widget::propEffect(int _type){
    switch(_type){
        case gameProp::speedUp:{
            playerShip_0->shipSpeed = 1.0;
            iconSpeedUp.setPixmap(QPixmap(":/img/img/speed_up.jpg"));
            if(timerSpeedUp->isActive()) {timerSpeedUp->stop();}
            timerSpeedUp->setSingleShot(true);
            timerSpeedUp->start(10000);
            break;
        }
        case gameProp::doubleScore:{
            scoreTime = 2;
            gameScene_gaming.addItem(&iconDoubleScore);
            if(timerDoubleScore->isActive()) {timerDoubleScore->stop();}
            timerDoubleScore->setSingleShot(true);
            timerDoubleScore->start(10000);
            break;
        }
        case gameProp::extraLife:{
            if(playerShip_0->shipLife == playerShip_0->maxLife) {playerShip_0->shipHP = playerShip_0->maxHealth; setHpBar();}
            else {playerShip_0->shipLife += 1, setLifeIcon();}
            break;
        }
        case gameProp::singleShield:{
            iconSingleShield.setPixmap(QPixmap(":/img/img/single_shield.jpg"));
            if(!timerSingleShieldRunning){
                playerShip_0->setPixmap(QPixmap(":/img/img/player_shielded.jpg"));
                timerSingleShieldRunning = true;
            }
            break;
        }
        case gameProp::laserBeam:{
            if(laserPermission){
                iconLaserBeam.setPixmap(QPixmap(":/img/img/laser_beam.jpg"));
            }
            laserCount++; laserCountLabelItem->updateScore(laserCount);
            break;
        }
        case gameProp::massiveBomb:{
            iconMassiveBomb.setPixmap(QPixmap(":/img/img/massive_bomb.jpg"));
            bombCount++; bombCountLabelItem->updateScore(bombCount);
            break;
        }

    }
}

void Widget::shieldBroken(){
    playerShip_0->setPixmap(QPixmap(":/img/img/player.jpg"));
    timerSingleShieldRunning = false;
    iconSingleShield.setPixmap(QPixmap(":/img/img/single_shield_inactive.jpg"));
    collisionImmune();
}

void Widget::collisionImmune(){
    collisionImmuneActive = true;
    playerShip_0->setPixmap(QPixmap(":/img/img/player_immune.jpg"));
    timerCollisionImmune->setSingleShot(true);
    timerCollisionImmune->start(immuneTime);
    timerImmuneBlinker->start(blinkerTime);
}

void Widget::clearGadget(){
    gameScene_gaming.removeItem(&pauseGadget_1);
    gameScene_gaming.removeItem(&pauseGadget_2);
    gameScene_gaming.removeItem(&pauseGadget_3);
    gameScene_gaming.removeItem(&pauseGadget_4);
}

void Widget::enemyDeath(enemyShip* ship){
    if(ship->timed){
        ship->temp_timer->stop();
        tempTimerList.removeOne(ship->temp_timer);
        delete ship->temp_timer; ship->timed = 0;
    }
    enemyList.removeOne(ship);
    if(ship->enemyType == enemyShip::enemy_Lv1)
        ship->setPixmap(QPixmap(":/img/img/enemy_lv1_dead.jpg"));
    if(ship->enemyType == enemyShip::enemy_Lv2)
        ship->setPixmap(QPixmap(":/img/img/enemy_lv2_dead.jpg"));
    if(ship->enemyType == enemyShip::enemy_Lv3)
        ship->setPixmap(QPixmap(":/img/img/enemy_lv3_dead.jpg"));
    if(ship->enemyType == enemyShip::enemy_Boss1)
        ship->setPixmap(QPixmap(":/img/img/boss_1_dead.jpg"));
    // if(ship->enemyType == enemyShip::enemy_Lv1)
    //     ship->setPixmap(QPixmap(":/img/img/enemy_lv1_dead.jpg"));
    // if(ship->enemyType == enemyShip::enemy_Lv1)
    //     ship->setPixmap(QPixmap(":/img/img/enemy_lv1_dead.jpg"));
    // if(ship->enemyType == enemyShip::enemy_Lv1)
    //     ship->setPixmap(QPixmap(":/img/img/enemy_lv1_dead.jpg"));
    QTimer* deathTimer = new QTimer;
    deathTimerList.append(deathTimer);
    deathTimer->setSingleShot(true);
    connect(deathTimer, &QTimer::timeout, [this, ship, deathTimer]{
        gameObjPool::Instance()->objRcycl(ship);
        gameScene_gaming.removeItem(ship);
        deathTimerList.removeOne(deathTimer);
        delete deathTimer;
    });
    deathTimer->start(500);
}

void Widget::setHpBar(){
    qDebug()<<playerShip_0->shipHP;
    hpBar.setPos(defIndex::screenWidth/2-hpBar.pixmap().width()/2+float(float(playerShip_0->shipHP)/float(playerShip_0->maxHealth))*200-200, defIndex::screenHeight-defIndex::barHeight+10);
}

void Widget::lifeIconInit(){
    int _indexX = 20;
    for(int i = 0; i < playerShip_0->maxLife; i++){
        iconLife[i].setPixmap(QPixmap(":/img/img/player_life.jpg")); iconLife[i].setPos(_indexX, 762); iconLife[i].setZValue(10);
        gameScene_gaming.addItem(&iconLife[i]);
        _indexX += 35;
    }
}

void Widget::setLifeIcon(){
    for(int i = playerShip_0->maxLife; i > playerShip_0->shipLife; i--){
        iconLife[i-1].setPixmap(QPixmap(":/img/img/player_life_inactive.jpg"));
    }
}

void Widget::triggeredLaserBeam(){
    QTimer* wait = new QTimer;
    tempTimerList.append(wait);
    QTimer* countdown = new QTimer;
    tempTimerList.append(countdown);
    connect(wait, &QTimer::timeout, [this, wait, countdown]{
        countdown->start(4000);
        gameScene_gaming.addItem(playerLaserBeam);
        playerLaserBeam->setPos(playerShip_0->x()+playerShip_0->pixmap().width()/2-playerLaserBeam->pixmap().width()/2, playerShip_0->y()+playerShip_0->pixmap().height()/2-playerLaserBeam->pixmap().height());
        laserBeamActive = true;
        tempTimerList.removeOne(wait);
        delete wait;
    });
    connect(countdown, &QTimer::timeout, [this, countdown]{
        gameScene_gaming.removeItem(playerLaserBeam);
        laserBeamActive = false;
        tempTimerList.removeOne(countdown);
        delete countdown;
    });
    wait->start(800);
}

void Widget::triggeredMassiveBomb(){
    QTimer* wait = new QTimer;
    tempTimerList.append(wait);
    connect(wait, &QTimer::timeout, [this, wait]{
        for(auto enemy: enemyList){
            enemyDeath(enemy);
        }
        tempTimerList.removeOne(wait);
        delete wait;
    });
    wait->start(800);
}
