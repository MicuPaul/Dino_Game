#include "stdafx.h"
#include "Score.h"


Score::Score() {
    this->score = 0;
    this->incrementTimer = 0;
    this->updateSpeedTimer = 0;

    this->updatePoint = false;
    this->game_speed = IDLE_GAME_SPEED;

}

Score::~Score() {

}

void Score::restartScore() {
    this->score = 0;
    this->incrementTimer = 0;
    this->updateSpeedTimer = 0;
    this->updatePoint = false;
    this->game_speed = IDLE_GAME_SPEED;
}

float Score::getSpeed() {
    return this->game_speed;
}

unsigned int Score::getScore() {
    return this->score;
}


void Score::update() {
    this->incrementTimer += 1;
    if(this->incrementTimer == 5){
        this->incrementTimer = 0;
        this->score += 1;
        this->updateSpeedTimer += 1;

    }

    if(this->updateSpeedTimer == 50 && this->game_speed > MAX_GAME_SPEED){
        this->updateSpeedTimer = 0;
        this->updatePoint = true;
        this->game_speed -= 0.5f;
    }

}


