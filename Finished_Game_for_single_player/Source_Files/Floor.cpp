#include "stdafx.h"
#include "Floor.h"


Floor::Floor(){
    this->spriteSheet = nullptr;
    this->floorY_pos = 0;
    this->floorTileSize = 0;
    this->nr_tiles = 0;
    this->game_speed = 0;
    this->floor_id = ID_1;
    this->updateTimer = 0;
}

Floor::Floor(sf::Texture *sprite_sheet, float floorY_poz) {
    this->spriteSheet = sprite_sheet;
    this->floorY_pos = floorY_poz;
    this->floorTileSize = 200;
    this->nr_tiles = 15;
    this->game_speed = -4.f;
    this->updateTimer = 0;

    this->floor.resize(this->nr_tiles);
    for(int i = 0 ; i < this->nr_tiles ; i++){
        this->addFloorTile(i);
    }
}

Floor::~Floor() {
    for(int i = 0; i < this->floor.size(); i++){
        delete this->floor[i];
        this->floor[i] = nullptr;
    }
}

int generateRandomNumber() {

    double randomFraction = (double)rand() / RAND_MAX;

    if (randomFraction < 0.8)
        return 1;
    else if (randomFraction < 0.9)
        return 2;
    else
        return 3;
}


void Floor::addFloorTile(unsigned int x) {
    if(x < this->floor.size()){
        if(this->floor[x] == nullptr) {
            int random = generateRandomNumber();
            switch (random) {
                case true:
                    this->floor_id = ID_1;
                    break;
                case 2:
                    this->floor_id = ID_2;
                    break;
                case 3:
                    this->floor_id = ID_3;
                    break;
            }
            this->floor[x] = new Tile(this->spriteSheet, sf::IntRect(this->floor_id, 103, this->floorTileSize, 27));
            this->floor[x]->setTilepos(float(this->floorTileSize * 0.6 * x), this->floorY_pos);
            this->floor[x]->setScale(0.6, 0.6);
        }
    }
}

void Floor::removeFloorTile(unsigned int x) {
    if(x < this->floor.size()){
        if(this->floor[x] != nullptr){
            delete this->floor[x];
            this->floor[x] = nullptr;
        }
    }
}

void Floor::setGameSpeed(float x) {
    this->game_speed = x;
}

void Floor::resetUpdateTimer() {
    this->updateTimer = 0;
}

void Floor::restartFloor() {
    for(int i = 0 ; i < this->nr_tiles ; i++){
        this->removeFloorTile(i);
        this->addFloorTile(i);
    }
    this->game_speed = -4.f;
}

void Floor::updateCollision(Dino& dino) const {
    if(dino.getGlobalBounds().top + dino.getGlobalBounds().height >= this->floorY_pos + 13.6f){
        dino.resetVelocityY();
        dino.setPosition(dino.getGlobalBounds().left,
                                 this->floorY_pos + 13.6f - dino.getGlobalBounds().height);
        dino.setJumpingFalse();
    }
}

void Floor::update() {

    this->updateTimer += std::abs(this->game_speed);
    if(this->updateTimer >= this->floorTileSize * 0.6) {
        this->resetUpdateTimer();

        for (int k = 0; k < this->floor.size() - 1; k++) {
            this->removeFloorTile(k);
            Tile *copy = new Tile;
            (*copy) = (*this->floor[k + 1]);
            this->floor[k] = copy;
            this->floor[k]->setTilepos(float(this->floorTileSize * 0.6 * k),
                                       this->floor[k]->getGlobalBounds().top);
            this->removeFloorTile(k + 1);
        }
        this->removeFloorTile(this->floor.size() - 1);
        this->addFloorTile(this->floor.size() - 1);
    }



    for(int i = 0; i < this->floor.size(); i++){
        if(this->floor[i] != nullptr)
            this->floor[i]->moveTile(this->game_speed, 0);
    }

}

void Floor::render(sf::RenderTarget& target) {
    for(int i = 0; i < this->floor.size(); i++){
        if(this->floor[i] != nullptr)
            this->floor[i]->render(target);
    }
}