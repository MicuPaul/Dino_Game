#include "stdafx.h"
#include "Game.h"

void Game::initWindow(){
    this->window.create(sf::VideoMode(1000, 250), "Dino Game", sf::Style::Close | sf::Style::Titlebar);
    this->window.setFramerateLimit(100);
    this->gameState = false;
    this->initGame = true;
    this->gameOverTimer = 0;
}

void Game::initSpritesheet() {
    if(!this->spriteSheet.loadFromFile("/home/alexpail/Documents/Dino_Game/Finished_Game_for_single_player/Spirtesheet/sprite.png")){
        std::cout << "ERROR::GAME::Could not load sprite sheet" << "\n";
    }
    this->gameOverSprites.resize(2);
    this->gameOverSprites[0].setTexture(this->spriteSheet);
    this->gameOverSprites[0].setTextureRect(sf::IntRect(952, 25, 385, 30));
    this->gameOverSprites[1].setTexture(this->spriteSheet);
    this->gameOverSprites[1].setTextureRect(sf::IntRect(0, 0, 75, 70));
    this->gameOverSprites[0].setPosition(307.5, 45);
    this->gameOverSprites[1].setPosition(462.5, 90);
}

void Game::initDino(){
    this->dino = new Dino();
}

void Game::initFloor() {
    this->floor = new Floor(&this->spriteSheet, 180);
}

void Game::initSky() {
    this->sky = new Clouds(&this->spriteSheet);
}

void Game::initObstacles() {
    this->obstacles = new Obstacles(&this->spriteSheet);
}

void Game::initScore() {
    this->score = new Score(&this->spriteSheet);
}

void Game::initSounds() {
    this->buff.resize(3);
    if (!this->buff[0].loadFromFile("/home/alexpail/Documents/Dino_Game/Finished_Game_for_single_player/Sounds/jump.wav"))
        std::cout << "ERROR::GAME::Could not load jump sound" << "\n";
    this->jumpSound.setBuffer(this->buff[0]);
    if (!this->buff[1].loadFromFile("/home/alexpail/Documents/Dino_Game/Finished_Game_for_single_player/Sounds/die.wav"))
        std::cout << "ERROR::GAME::Could not load death sound" << "\n";
    this->deathSound.setBuffer(this->buff[1]);
    if (!this->buff[2].loadFromFile("/home/alexpail/Documents/Dino_Game/Finished_Game_for_single_player/Sounds/point.wav"))
        std::cout << "ERROR::GAME::Could not load point sound" << "\n";
    this->pointSound.setBuffer(this->buff[2]);
}

Game::Game(){
    this->initWindow();
    this->initSpritesheet();
    this->initDino();
    this->initFloor();
    this->initSky();
    this->initObstacles();
    this->initScore();
    this->initSounds();
}

Game::~Game(){
    delete this->dino;
    delete this->floor;
    delete this->sky;
    delete this->obstacles;
    delete this->score;
}

void Game::updateDino(){
    this->dino->update();
}


void Game::updateFloor() {
    this->floor->update();
}

void Game::updateSky() {
    this->sky->update();
}

void Game::updateObstacles() {
    this->obstacles->update();
}

void Game::updateScore() {
    this->score->update();
}

void Game::update(){
    while(this->window.pollEvent(this->ev))
    {
        if(this->ev.type == sf::Event::Closed)
            this->window.close();
        else if(this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
            this->window.close();
        else if(this->ev.type == sf::Event::KeyPressed && this->initGame && (this->ev.key.code == sf::Keyboard::Up ||
                                                                              this->ev.key.code == sf::Keyboard::Space)){
            this->gameState = true;
            this->initGame = false;
            this->dino->setGameState(true);
            this->dino->setJumpSound(this->jumpSound);
            this->score->setPointSound(this->pointSound);
            this->obstacles->setDeathSound(this->deathSound);
        }
        else if(this->ev.type == sf::Event::KeyReleased && !this->gameState && !this->initGame && (this->ev.key.code == sf::Keyboard::Up ||
                                                                                                   this->ev.key.code == sf::Keyboard::Space)){
            if(this->gameOverTimer >= 50) {
                this->jumpSound.play();
                this->gameOverTimer = 0;
                this->gameState = true;
                this->dino->restartDino();
                this->floor->restartFloor();
                this->obstacles->restartObstacles();
                this->score->restartScore();
            }
        }
        if(this->ev.type == sf::Event::KeyReleased &&
                                                    (this->ev.key.code == sf::Keyboard::Up ||
                                                     this->ev.key.code == sf::Keyboard::Space ||
                                                     this->ev.key.code == sf::Keyboard::Down)) {
            this->dino->resetAnimationTimer();
        }
    }

    if(this->gameState) {
        this->updateDino();
        this->updateFloor();
        this->updateSky();
        this->updateObstacles();
        this->updateScore();
        this->floor->setGameSpeed(this->score->getSpeed());
        this->obstacles->setGameSpeed(this->score->getSpeed());
        this->floor->updateCollision(*this->dino);
        this->obstacles->updateCollision(*this->dino, &this->gameState);
    }

    if(!this->gameState && !this->initGame){
        if(this->dino->getAnimState() == DUCKING){
            this->dino->setTextureRect(sf::IntRect(2294, 40, 110, 52));
        }
        else
            this->dino->setTextureRect(sf::IntRect(1782, 6, 80, 86));
        this->gameOverTimer += 1;
    }

}

void Game::renderDino(){
    this->dino->render(this->window);
}

void Game::renderFloor() {
    this->floor->render(this->window);
}

void Game::renderSky() {
    this->sky->render(this->window);
}

void Game::renderObstacles() {
    this->obstacles->render(this->window);
}

void Game::renderGameOver() {
    this->window.draw(this->gameOverSprites[0]);
    this->window.draw(this->gameOverSprites[1]);
}

void Game::renderScore() {
    this->score->render(this->window);
}

void Game::render(){
    this->window.clear(sf::Color::White);

    this->renderFloor();
    this->renderSky();
    this->renderScore();
    this->renderObstacles();
    this->renderDino();
    if(!this->gameState && !this->initGame)
        this->renderGameOver();

    this->window.display();
}

const sf::RenderWindow& Game::getWindow() const{
    return this->window;
}