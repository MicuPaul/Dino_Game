#include "stdafx.h"
#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(sf::Texture* texture_sheet, sf::IntRect texture_rect) {
    this->sprite.setTexture(*texture_sheet);
    this->sprite.setTextureRect(texture_rect);
}


sf::FloatRect Tile::getGlobalBounds() {
    return this->sprite.getGlobalBounds();
}

sf::Sprite Tile::getSprite() {
    return this->sprite;
}

void Tile::moveTile(float offsetX, float offsetY) {
    this->sprite.move(offsetX, offsetY);
}

void Tile::setTilepos(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Tile::setTextureRect(sf::IntRect current_frame) {
    this->sprite.setTextureRect(current_frame);
}

sf::IntRect Tile::getCurrentFrame() {
    return this->sprite.getTextureRect();
}

void Tile::setScale(float x, float y) {
    this->sprite.setScale(x, y);
}

void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}