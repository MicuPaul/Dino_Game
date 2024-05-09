#pragma once
#include "stdafx.h"
#include "Tile.h"

class Score{

private:
    std::vector<Tile*> digits;
    sf::Texture* spriteSheet;
    sf::Sound pointSound;
    unsigned int score;
    unsigned int incrementTimer; //Increments score every 10 frames
    unsigned int updateSpeedTimer;
    unsigned int visualUpdatePointTimer;  //A point is 100 score
    unsigned int blinkScoreTimer;
    unsigned int blinkScore;
    bool updatePoint;
    float game_speed;


public:
    Score();
    Score(sf::Texture* sprite_sheet);
    ~Score();

    void setPointSound(sf::Sound P);

    void restartScore();
    float getSpeed();

    void addDigit(unsigned x, unsigned int digit);
    void removeDigit(unsigned x);

    void update();
    void render(sf::RenderTarget& target);
};