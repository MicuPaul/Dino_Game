#ifndef DINO_GAME_GAMEGLOBALS_H
#define DINO_GAME_GAMEGLOBALS_H

#include "stdafx.h"


const float IDLE_GAME_SPEED = -7.5f;
const float MAX_GAME_SPEED = -50.f;
const float FLOOR_Y_POS = 180.f;
const int TILE_SIZE = 200;
const unsigned NR_TILES = 10;
const int NR_OF_INPUTS = 10;
const int NR_OF_OUTPUTS = 3;
const float MUTATION_RATE = 0.015f;
const float MAX_PERBETUATION = 0.3f;
const int MAX_POPULATION = 300;
const unsigned int BIG_JUMP = 0;
//const unsigned int SMALL_JUMP = 1;
const unsigned int DUCK = 1;
const unsigned int NOTHING = 2;

inline float RandomFloat()
{
    return (float)rand()/*0 to 32767*/ / (float)RAND_MAX/*32767*/;
}

inline float RandomClamped()
{
    return RandomFloat() - RandomFloat();
}

inline float Sigmoid(float a, float p)
{
    float ap = (-a)/p;
    return (1 / (1 + exp(ap)));
}

inline float RelU(float z) {
    if (z > 0) return z;
    else return 0;
}

template<typename T>
inline float getLength(const sf::Vector2<T>& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

template<typename T, typename U>
inline T as(const U& u)
{
    return static_cast<T>(u);
}

template<typename T>
inline sf::Color toColor(const sf::Vector3<T>& v)
{
    const uint8_t r = as<uint8_t>(v.x);
    const uint8_t g = as<uint8_t>(v.y);
    const uint8_t b = as<uint8_t>(v.z);
    return sf::Color(std::min(uint8_t(255), r), std::min(uint8_t(255), g), std::min(uint8_t(255), b));
}

inline float getAngle(const sf::Vector2f & v)
{
    const float a = acos(v.x / getLength(v));
    return v.y > 0.0f ? a : -a;
}

inline sf::RectangleShape getLine(const sf::Vector2f& point_1, const sf::Vector2f& point_2, const float width, const sf::Color& color)
{
    const sf::Vector2f vec = point_2 - point_1;
    const float angle = getAngle(vec);
    const sf::Vector2f mid_point = point_1 + 0.5f * vec;
    const float dist = getLength(vec);
    const float rad_to_deg = 57.2958f;

    sf::RectangleShape line(sf::Vector2f(width, dist));
    line.setOrigin(width * 0.5f, dist * 0.5f);
    line.setRotation(angle * rad_to_deg - 90);
    line.setFillColor(color);
    line.setPosition(mid_point);

    return line;
}

#endif //DINO_GAME_GAMEGLOBALS_H
