#include "stdafx.h"
#include "Score.h"

Score::Score() {

}

Score::Score(sf::Texture *sprite_sheet) {
    this->spriteSheet = sprite_sheet;
    this->digits.resize(5);
    this->score = 0;
    this->incrementTimer = 0;
    this->updateSpeedTimer = 0;
    this->visualUpdatePointTimer = 0;
    this->blinkScoreTimer = 0;
    this->blinkScore = 0;
    this->updatePoint = false;
    this->game_speed = -4.f;

    for(int i = 0; i < this->digits.size(); i++){
        this->addDigit(i, 0);
    }
}

Score::~Score() {
    for(int i = 0; i < this->digits.size(); i++){
        delete this->digits[i];
        this->digits[i] = nullptr;
    }
}

void Score::setPointSound(sf::Sound P) {
    this->pointSound = P;
}

void Score::restartScore() {
    this->score = 0;
    this->incrementTimer = 0;
    this->updateSpeedTimer = 0;
    this->updatePoint = false;
    this->visualUpdatePointTimer = 0;
    this->blinkScore = 0;
    this->blinkScoreTimer = 0;
    this->game_speed = -4.f;
    for(int i = 0; i < this->digits.size(); i++){
        this->removeDigit(i);
        this->addDigit(i, 0);
    }
}

float Score::getSpeed() {
    return this->game_speed;
}

sf::IntRect getSpriteDetails(unsigned digit){
    std::vector<unsigned> spriteDetails;
    spriteDetails.resize(4);
    switch (digit) {
        case 0:
            spriteDetails = {953, 0, 20, 25};
            break;
        case 1:
            spriteDetails = {974, 0, 20, 25};
            break;
        case 2:
            spriteDetails = {994, 0, 20, 25};
            break;
        case 3:
            spriteDetails = {1014, 0, 20, 25};
            break;
        case 4:
            spriteDetails = {1034, 0, 20, 25};
            break;
        case 5:
            spriteDetails = {1054, 0, 20, 25};
            break;
        case 6:
            spriteDetails = {1074, 0, 20, 25};
            break;
        case 7:
            spriteDetails = {1094, 0, 20, 25};
            break;
        case 8:
            spriteDetails = {1114, 0, 20, 25};
            break;
        case 9:
            spriteDetails = {1134, 0, 20, 25};
            break;
    }

    sf::IntRect details(spriteDetails[0],
                        spriteDetails[1],
                        spriteDetails[2],
                        spriteDetails[3]);

    return details;
}

void Score::addDigit(unsigned int x, unsigned int digit) {
    if(x < this->digits.size()){
        if(this->digits[x] == nullptr){
            sf::IntRect details;
            details = getSpriteDetails(digit);
            this->digits[x] = new Tile(this->spriteSheet, details);
            this->digits[x]->setTilepos(1000 - 20 * 0.7 * (x * 1.2 + 1) - 10, 15);
            this->digits[x]->setScale(0.7, 0.7);
        }
    }
}

void Score::removeDigit(unsigned int x) {
    if(x < this->digits.size()){
        if(this->digits[x] != nullptr){
            delete this->digits[x];
            this->digits[x] = nullptr;
        }
    }
}

void Score::update() {
    this->incrementTimer += 1;
    if(this->incrementTimer == 10){
        this->incrementTimer = 0;
        this->score += 1;
        this->updateSpeedTimer += 1;

        if(!this->updatePoint) {
            unsigned int copy = this->score;
            for (int i = 0; i < this->digits.size(); i++) {
                this->removeDigit(i);
                this->addDigit(i, copy % 10);
                copy = copy / 10;
            }
        }
    }

    if(this->updateSpeedTimer == 100){
        this->pointSound.play();
        this->updateSpeedTimer = 0;
        this->blinkScore = score;
        this->updatePoint = true;
        this->game_speed -= 0.3f;
    }

    if(this->updatePoint && this->visualUpdatePointTimer < 200){
        this->visualUpdatePointTimer += 1;
        this->blinkScoreTimer += 1;
        if(this->blinkScoreTimer == 20) {
            this->blinkScoreTimer = 0;
            unsigned int copy = this->blinkScore;
            for (int i = 0; i < this->digits.size(); i++) {
                if(this->digits[i] != nullptr){
                    this->removeDigit(i);
                }
                else {
                    this->addDigit(i, copy % 10);
                    copy = copy / 10;
                }
            }
        }
    }else{
        this->updatePoint = false;
        this->visualUpdatePointTimer = 0;
        this->blinkScore = 0;
        this->blinkScoreTimer = 0;
    }
}

void Score::render(sf::RenderTarget &target) {
    for(int i = 0; i < this->digits.size(); i++){
        if(this->digits[i] != nullptr)
            this->digits[i]->render(target);
    }
}

