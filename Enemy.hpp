
/*
===============
Our Enemy Class
===============
*/

#pragma once

#if !defined(HEADER_INCLUDED)
#include "Headers.hpp"
#endif

enum EnemyLevel
{
    ENEMY_LEVEL_NONE,
    ENEMY_LEVEL_ONE,
    ENEMY_LEVEL_TWO,
    ENEMY_LEVEL_THREE,
    ENEMY_LEVEL_FOUR,
    ENEMY_LEVEL_FIVE,
};

/*Returns the random number in between the limit*/
int randomNumberGenerator(int lower_limit, int upper_limit, int number_of_digits_in_upper_limit);

class Enemy
{
private:
    EnemyLevel enemy_level;
    SDL_Point render_position;
    SDL_Color enemy_color;
    SDL_Rect enemy_size;
    int velocity_in_y_direction;

    void setEnemyLevel();
    void setEnemyColor();
    void setEnemySize();
    void setRenderPosition();
    void setVelocityInYDirection();

public:
    Enemy();

    ~Enemy();

    void initialize();
    EnemyLevel getEnemyLevel();
    SDL_Color getEnemyColor();
    SDL_Rect getEnemySize();
    SDL_Point getRenderPosition();
    int getVelocityInYDirection();

    void render();
};