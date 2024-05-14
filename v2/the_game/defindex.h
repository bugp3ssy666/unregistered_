#ifndef DEFINDEX_H
#define DEFINDEX_H



class defIndex
{
    defIndex();
public:
    static const int screenWidth = 500,
                     screenHeight = 800,
                     barWidth = 500,
                     barHeight = 50;

    static const int backgroundUpdateFreq = 15,
                     playerMoveUpdateFreq = 2,
                     enemyMoveUpdateFreq = 2,
                     ammoMoveUpdateFreq = 2,
                     enemyGenFreq = 1500;

    int musicVolume = 100,
        soundfxVolume = 100;
};

#endif // DEFINDEX_H
