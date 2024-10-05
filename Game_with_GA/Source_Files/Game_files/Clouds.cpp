#include "Clouds.h"

Clouds::Clouds() {
    this->cloudWidth = 0;
    this->cloudsSpeed = 0.f;
    this->maxClouds = 0;
    this->cloudsInSky = 0;
    this->updateTimer = 0;
}


void Clouds::initClouds() {
    int i = 0;

    while(i < this->cloudsInSky){
        int pos = rand() % 17;
        this->addCloud(pos);
        i++;
    }
}

Clouds::Clouds(sf::Texture *sprite_sheet) {
    this->spriteSheet = sprite_sheet;
    this->cloudWidth = 95;
    this->cloudsSpeed = -1.f;
    this->maxClouds = 30;
    this->cloudsInSky = 4;
    this->updateTimer = 0;

    this->sky.resize(this->maxClouds);
    this->initClouds();
}

Clouds::~Clouds() {
    for(int i = 0; i < this->sky.size(); i++){
        delete this->sky[i];
        this->sky[i] = nullptr;
    }
}

void Clouds::addCloud(unsigned int x) {
    if(x < this->sky.size()){
        if(this->sky[x] == nullptr) {
            int random = rand() % 111 + 20;  //number between 20 and 130
            this->sky[x] = new Tile(this->spriteSheet, sf::IntRect(165, 0, this->cloudWidth, 30));
            this->sky[x]->setTilepos(float(this->cloudWidth * 0.6 * x), random);
            this->sky[x]->setScale(0.6, 0.6);
        }
    }
}

void Clouds::removeCloud(unsigned int x) {
    if(x < this->sky.size()){
        if(this->sky[x] != nullptr){
            delete this->sky[x];
            this->sky[x] = nullptr;
        }
    }
}

void Clouds::resetUpdateTimer(){
    this->updateTimer = 0;
}

void Clouds::update() {
    this->updateTimer += std::abs(this->cloudsSpeed);
    if(this->updateTimer >= this->cloudWidth * 0.6){
        this->resetUpdateTimer();
        if(this->sky[0] != nullptr){
            this->cloudsInSky -= 1;
        }
        for (int k = 0; k < this->sky.size() - 1; k++) {
            if (this->sky[k + 1] == nullptr) {
                this->removeCloud(k);
                continue;
            } else {
                this->removeCloud(k);
                Tile *copy = new Tile;
                (*copy) = (*this->sky[k + 1]);
                this->sky[k] = copy;
                this->sky[k]->setTilepos(float(this->cloudWidth * 0.6 * k),
                                         this->sky[k]->getGlobalBounds().top);
                this->removeCloud(k + 1);
            }
        }
        this->removeCloud(this->sky.size() - 1);
        bool chance_to_add_cloud = (rand() % 100) < 15;
        if (chance_to_add_cloud && this->cloudsInSky <= 7) {
            int cloud_index = 19 + rand() % 11;
            while(this->sky[cloud_index] != nullptr){
                cloud_index = 19 + rand() % 11;
            }
            this->cloudsInSky += 1;
            this->addCloud(cloud_index);
        }
    }


    for(int i = 0; i < this->sky.size(); i++){
        if(this->sky[i] != nullptr)
            this->sky[i]->moveTile(this->cloudsSpeed, 0);
    }

}

void Clouds::render(sf::RenderTarget &target) {
    for(int i = 0; i < this->sky.size(); i++){
        if(this->sky[i] != nullptr)
            this->sky[i]->render(target);
    }
}