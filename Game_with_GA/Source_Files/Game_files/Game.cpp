#include "Game.h"

void Game::initGA(){
    this->GA = new Genetic_Algorithm();
    this->GA->GenerateNewPopulation();
}


void Game::initWindow(){
    this->window.create(sf::VideoMode(1000, 250), "Dino Game", sf::Style::Close | sf::Style::Titlebar);
    this->window.setFramerateLimit(60);
    this->gameState = true;
    this->gameOverTimer = 0;
}

void Game::initSpritesheet() {
    if(!this->spriteSheet.loadFromFile("Spritesheet/sprite.png")){
        std::cout << "ERROR::GAME::Could not load sprite sheet" << "\n";
    }
}

void Game::initFloor() {
    this->floor = new Floor(&this->spriteSheet);
}

void Game::initSky() {
    this->sky = new Clouds(&this->spriteSheet);
}

void Game::initObstacles() {
    this->obstacles = new Obstacles(&this->spriteSheet);
}

void Game::initScore() {
    this->score = new Score();
    this->scoreTimer = 0;
}


Game::Game(){
    this->initWindow();
    this->initSpritesheet();
    this->initGA();
    this->initFloor();
    this->initSky();
    this->initObstacles();
    this->initScore();
}

Game::~Game(){
    delete this->GA;
    delete this->floor;
    delete this->sky;
    delete this->obstacles;
    delete this->score;
}



void Game::updateGA_Dinos() {
    this->scoreTimer += 1;

    if(this->scoreTimer == 5){
        this->GA->setDinosScore(this->score->getScore());
        this->scoreTimer = 0;
    }

    this->GA->setDinosInputs(this->obstacles->getInputs());
    this->GA->updateDinos(this->obstacles->getClosestObstacle());

    for(int i = 0; i < this->GA->GetTotalPopulation(); i++){
        unsigned int sum = this->GA->calculateScoresum();
        float fitness = 0;
        if(sum != 0){
            fitness = float(this->GA->GetDino(i)->getScore()) / sum;
        }
        if(!this->GA->GetDino(i)->HasFailed()){
            this->GA->SetGenomeFitness(fitness, i);
        }
    }


    if(this->GA->checkIfDinosFailed()){
        this->gameState = false;
    }

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
        else if(this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Enter) {
            this->gameState = false;  //Forcing to next generation
        }
    }

    switch (this->gameState) {
        case true:
            this->updateScore();
            this->updateGA_Dinos();
            this->updateFloor();
            this->updateObstacles();
            this->updateSky();
            this->floor->setGameSpeed(this->score->getSpeed());
            this->obstacles->setGameSpeed(this->score->getSpeed());
            for(int i = 0; i < this->GA->GetTotalPopulation(); i++) {
                if(!this->GA->GetDino(i)->HasFailed()) {
                    this->floor->updateCollision(*this->GA->GetDino(i));
                    this->obstacles->updateCollision(*this->GA->GetDino(i));
                }
            }
            break;
        case false:
            this->gameOverTimer += 1;
            if(this->gameOverTimer == 60){
                this->gameState = true;
                this->gameOverTimer = 0;
                this->GA->BreedPopulation();
                this->obstacles->restartObstacles();
                this->floor->restartFloor();
                this->score->restartScore();
            }
            break;

    }

}



void Game::renderGA_Dinos_Info() {
    this->GA->render(this->window, this->score->getScore(), this->gameState);
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

void Game::render(){
    this->window.clear(sf::Color::White);

    this->renderFloor();
    this->renderSky();
    this->renderObstacles();
    this->renderGA_Dinos_Info();

    this->window.display();
}

const sf::RenderWindow& Game::getWindow() const{
    return this->window;
}