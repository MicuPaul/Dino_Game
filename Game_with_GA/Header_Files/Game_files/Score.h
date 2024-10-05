#pragma once
#include "stdafx.h"
#include "GameGlobals.h"

class Score{

private:
    unsigned int score;
    unsigned int incrementTimer; //Increments score every 10 frames
    unsigned int updateSpeedTimer;

    bool updatePoint;
    float game_speed;


public:
    Score();
    ~Score();

    void restartScore();
    float getSpeed();
    unsigned int getScore();

    void update();
};