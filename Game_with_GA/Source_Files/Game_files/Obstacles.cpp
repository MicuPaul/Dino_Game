#include "Obstacles.h"

Obstacles::Obstacles() {
    this->obstacleWidth = 0;
    this->game_speed = 0;
    this->updateTimer = 0;
    this->maxObstacles = 0;
    this->obstacleTimer = 0;
}


Obstacles::Obstacles(sf::Texture *sprite_sheet) {
    this->spriteSheet = sprite_sheet;
    this->obstacleWidth = TILE_SIZE;
    this->maxObstacles = NR_TILES;
    this->game_speed = IDLE_GAME_SPEED;
    this->updateTimer = 0;
    this->obstacleTimer = 0;
    this->animationTimer.restart();

    this->obstacles.resize(this->maxObstacles);

    for(int i = 0; i < this->obstacles.size(); i++){
        this->obstacles[i] = nullptr;
    }
}

Obstacles::~Obstacles() {
    for(int i = 0; i < this->obstacles.size(); i++){
        delete this->obstacles[i];
        this->obstacles[i] = nullptr;
    }
}

void Obstacles::getRandomObstacle() {
    std::srand(std::time(nullptr));

    int obstacleNumber = std::rand() % 32;

    if (obstacleNumber < 5) {
        this->obstacleId =  SMALL_CACTUS;
    } else if (obstacleNumber < 10) {
        this->obstacleId =  DOUBLE_SMALL_CACTI;
    } else if (obstacleNumber < 13) {
        this->obstacleId = TRIPLE_SMALL_CACTI;
    } else if (obstacleNumber < 18) {
        this->obstacleId = LARGE_CACTUS;
    } else if (obstacleNumber < 24) {
        this->obstacleId = DOUBLE_LARGE_CACTI;
    } else if (obstacleNumber < 27){
        this->obstacleId = QUAD_LARGE_CACTI;
    }else{
       this->obstacleId = BIRD;
    }
}

Tile *Obstacles::getClosestObstacle() {
    float closest_obstacle = 1000000;
    unsigned int index = 0;
    for(int i = 0; i< this->maxObstacles; i++){
        if(this->obstacles[i] != nullptr) {
            if (this->obstacles[i]->getGlobalBounds().left < closest_obstacle &&
                this->obstacles[i]->getGlobalBounds().left > 20.f) {
                index = i;
                closest_obstacle = this->obstacles[i]->getGlobalBounds().left;
            }
        }
    }

    return this->obstacles[index];
}

std::vector<float> Obstacles::getInputs() {
    std::vector<float> Inputs(NR_OF_INPUTS, 0);
    int index = 0;
    int index_next_obstacle = 1;

    for(int i = 0; i < this->obstacles.size(); i++){
        if(this->obstacles[i] == this->getClosestObstacle())
            index = i;
    }

    if(index != maxObstacles - 1) {
        index_next_obstacle = index + 1;
        while (this->obstacles[index_next_obstacle] == nullptr && index_next_obstacle < this->maxObstacles - 1) {
            index_next_obstacle++;
        }
    }

    if(this->obstacles[index] != nullptr) {
        float distance_to_next_obstacle = (this->obstacles[index]->getGlobalBounds().left - 20.f) / (((this->maxObstacles - 1) * this->obstacleWidth * 0.6) - 20.f);
        Inputs[0] = distance_to_next_obstacle;
        //Dino x left pos = 50 and the width is 48 so the right of the dino is 98
        float height_of_obstacle = this->obstacles[index]->getGlobalBounds().height / 55.2f;
        Inputs[1] = height_of_obstacle;
        float width_of_obstacle = this->obstacles[index]->getGlobalBounds().width / 87.6f;
        Inputs[2] = width_of_obstacle;
        float top_of_obstacle = ((250.f - this->obstacles[index]->getGlobalBounds().top) - (250.f - 193.6f))  / ((250.f - 60.f) - (250.f - 193.6f));
        Inputs[3] = top_of_obstacle;
        if(this->obstacles[index_next_obstacle] != nullptr){
            distance_to_next_obstacle = (this->obstacles[index_next_obstacle]->getGlobalBounds().left - 20.f)/
                                        (((this->maxObstacles - 1) * this->obstacleWidth * 0.6) - 20.f);
            Inputs[4] = distance_to_next_obstacle;
            height_of_obstacle = this->obstacles[index_next_obstacle]->getGlobalBounds().height / 55.2f;
            Inputs[5] = height_of_obstacle;
            width_of_obstacle = this->obstacles[index_next_obstacle]->getGlobalBounds().width / 87.6f;
            Inputs[6] = width_of_obstacle;
            top_of_obstacle = ((250.f - this->obstacles[index_next_obstacle]->getGlobalBounds().top) - (250.f - 193.6f))  / ((250.f - 60.f) - (250.f - 193.6f));
            Inputs[7] = top_of_obstacle;
        }
        else{
            Inputs[4] = 0.99f;
            Inputs[5] = 0.f;
            Inputs[6] = 0.f;
            Inputs[7] = 0.f;
        }
    }
    else{
        Inputs[0] = 0.99f;
        Inputs[1] = 0.f;
        Inputs[2] = 0.f;
        Inputs[3] = 0.f;
        Inputs[4] = 0.99f;
        Inputs[5] = 0.f;
        Inputs[6] = 0.f;
        Inputs[7] = 0.f;
    }

    float speed = this->game_speed / MAX_GAME_SPEED;
    Inputs[8] = speed;

    return Inputs;
}

void Obstacles::addObstacle(unsigned int x) {
    if(x < this->obstacles.size()){
        if(this->obstacles[x] == nullptr) {
            std::vector<int> sprite_details;
            sprite_details.resize(4);
            this->getRandomObstacle();
            switch (this->obstacleId) {
                case SMALL_CACTUS:
                    sprite_details = {448, 4, 30, 66};
                    break;
                case DOUBLE_SMALL_CACTI:
                    sprite_details = {482, 4, 64, 66};
                    break;
                case TRIPLE_SMALL_CACTI:
                    sprite_details = {550, 4, 98, 66};
                    break;
                case LARGE_CACTUS:
                    sprite_details = {654, 4, 46, 92};
                    break;
                case DOUBLE_LARGE_CACTI:
                    sprite_details = {704, 4, 96, 92};
                    break;
                case QUAD_LARGE_CACTI:
                    sprite_details = {804, 4, 146, 92};
                    break;
                case BIRD:
                    sprite_details = {264, 0, 84, 78};
            }
            this->obstacles[x] = new Tile(this->spriteSheet, sf::IntRect(sprite_details[0],
                                                                                                sprite_details[1],
                                                                                                sprite_details[2],
                                                                                                sprite_details[3]));
            if(this->obstacleId != BIRD)
                this->obstacles[x]->setTilepos(float(this->obstacleWidth * 0.6 * x), 193.6 - sprite_details[3] * 0.6);
            else {
                int random = 1 + rand() % 3;
                int bird_height;
                switch (random){
                    case 1:
                        bird_height = 193.6 - sprite_details[3] * 0.6;
                        break;
                    case 2:
                        bird_height = 150  - sprite_details[3] * 0.6;
                        break;
                    case 3:
                        bird_height = 60;
                        break;
                }
                this->obstacles[x]->setTilepos(float(this->obstacleWidth * 0.6 * x), bird_height);
            }
            this->obstacles[x]->setScale(0.6, 0.6);
        }
    }
}

void Obstacles::removeObstacle(unsigned int x) {
    if(x < this->obstacles.size()){
        if(this->obstacles[x] != nullptr){
            delete this->obstacles[x];
            this->obstacles[x] = nullptr;
        }
    }
}

void Obstacles::setGameSpeed(float x) {
    this->game_speed = x;
}

void Obstacles::restartObstacles() {
    for(int i = 0; i < this->obstacles.size(); i++){
        this->removeObstacle(i);
        this->obstacles[i] = nullptr;
    }
    this->game_speed = IDLE_GAME_SPEED;
}


void Obstacles::resetObstacleTimer() {
    this->obstacleTimer = 0;
}

void Obstacles::resetUpdateTimer() {
    this->updateTimer = 0;
}

void Obstacles::updateAnimations() {
    if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
        for (int i = 0; i < this->obstacles.size(); i++) {
            if (this->obstacles[i] != nullptr) {

                this->animationTimer.restart();

                if (this->obstacles[i]->getCurrentFrame().left == 264)
                    this->obstacles[i]->setTextureRect(sf::IntRect(356, 0, 84, 78));
                else if (this->obstacles[i]->getCurrentFrame().left == 356)
                    this->obstacles[i]->setTextureRect(sf::IntRect(264, 0, 84, 78));
            }
        }
    }
}

void Obstacles::updateCollision(Dino& dino){
    for (int i = 0; i < this->obstacles.size(); i++) {
        if (this->obstacles[i] != nullptr) {
            if(Collision::CircleTest(dino.getSprite(), this->obstacles[i]->getSprite())){
                dino.setFailure();
            }
        }
    }
}

void Obstacles::update() {

    this->updateTimer += std::abs(this->game_speed);
    this->obstacleTimer += std::abs(this->game_speed);

    if(this->updateTimer >= this->obstacleWidth * 0.6){
        this->resetUpdateTimer();
        for (int k = 0; k < this->obstacles.size() - 1; k++) {
            if (this->obstacles[k + 1] == nullptr) {
                this->removeObstacle(k);
                continue;
            } else {
                this->removeObstacle(k);
                Tile *copy = new Tile;
                (*copy) = (*this->obstacles[k + 1]);
                this->obstacles[k] = copy;
                this->obstacles[k]->setTilepos(float(this->obstacleWidth * 0.6 * k),
                                         this->obstacles[k]->getGlobalBounds().top);
                this->removeObstacle(k + 1);
            }
        }
        this->removeObstacle(this->obstacles.size() - 1);
        bool add_chance = (rand() % 3) < 1;
        if(add_chance) {
            if (this->obstacles[this->obstacles.size() - 1] == nullptr and
                this->obstacleTimer >= 50 * std::abs(this->game_speed)* 0.8) {

                this->resetObstacleTimer();
                this->addObstacle(this->obstacles.size() - 1);

            }
        }
    }

    for(int i = 0; i < this->obstacles.size(); i++){
        if(this->obstacles[i] != nullptr)
            this->obstacles[i]->moveTile(this->game_speed, 0);
    }

    this->updateAnimations();
}

void Obstacles::render(sf::RenderTarget &target) {
    for(int i = 0; i < this->obstacles.size(); i++){
        if(this->obstacles[i] != nullptr)
            this->obstacles[i]->render(target);
    }
}
