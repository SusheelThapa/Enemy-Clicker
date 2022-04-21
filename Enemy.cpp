#include "Enemy.hpp"

#if !defined(GAME_RENDERER_EXIST)
#define GAME_RENDERER_EXIST 1
SDL_Renderer *game_renderer;
#endif

/*
=======================
Body of the Enemy Class
=======================
*/

int randomNumberGenerator(int lower_limit, int upper_limit, int number_of_digits_in_upper_limit)
{
    int number = INT16_MIN;

    while (number > upper_limit || number < lower_limit)
    {
        number = rand() % ((int)pow(10, number_of_digits_in_upper_limit));
    }

    return number;
}

void Enemy::setRenderPosition()
{
    render_position.x = randomNumberGenerator(0, 400, 3);
    render_position.y = 100;
}

void Enemy::setEnemyLevel()
{
    switch (randomNumberGenerator(1, 5, 1))
    {
    case 1:
        enemy_level = ENEMY_LEVEL_ONE;
        break;
    case 2:
        enemy_level = ENEMY_LEVEL_TWO;
        break;
    case 3:
        enemy_level = ENEMY_LEVEL_THREE;
        break;
    case 4:
        enemy_level = ENEMY_LEVEL_FOUR;
        break;
    case 5:
        enemy_level = ENEMY_LEVEL_FIVE;
        break;
    }
}

void Enemy::setEnemyColor()
{
    // Logic to find random value of r, g, b and use to make color
    Uint8 red = (Uint8)randomNumberGenerator(0, 255, 3);
    Uint8 green = (Uint8)randomNumberGenerator(0, 255, 3);
    Uint8 blue = (Uint8)randomNumberGenerator(0, 255, 3);

    // Later on we will set the value of alpha based on Enemy Level
    Uint8 alpha = 255;

    enemy_color = {red, green, blue, alpha};
}

void Enemy ::setEnemySize()
{
    // Logic to create enemy size of different dimension based on enemy level

    switch (enemy_level)
    {
    case ENEMY_LEVEL_ONE:
        enemy_size = {this->render_position.x, this->render_position.y, 100, 100};
        break;

    case ENEMY_LEVEL_TWO:
        enemy_size = {this->render_position.x, this->render_position.y, 85, 85};
        break;

    case ENEMY_LEVEL_THREE:
        enemy_size = {this->render_position.x, this->render_position.y, 70, 70};
        break;

    case ENEMY_LEVEL_FOUR:
        enemy_size = {this->render_position.x, this->render_position.y, 60, 60};
        break;

    case ENEMY_LEVEL_FIVE:
        enemy_size = {this->render_position.x, this->render_position.y, 50, 50};
        break;
    case ENEMY_LEVEL_NONE:
        break;
    }
}

void Enemy::setVelocityInYDirection()
{
    velocity_in_y_direction = randomNumberGenerator(1, 2, 1);
}

Enemy::Enemy()
{
    enemy_level = ENEMY_LEVEL_NONE;
    render_position = {0, 0};
    enemy_size = {0, 0, 0, 0};
    velocity_in_y_direction = 0;
    enemy_color = {255, 255, 255, 255};
}

Enemy::~Enemy()
{
}

void Enemy::initialize()
{
    setRenderPosition();
    setEnemyLevel();
    setEnemyColor();
    setEnemySize();
    setVelocityInYDirection();
}

EnemyLevel Enemy::getEnemyLevel()
{
    return enemy_level;
}

SDL_Color Enemy::getEnemyColor()
{
    return enemy_color;
}

SDL_Rect Enemy ::getEnemySize()
{
    return enemy_size;
}

SDL_Point Enemy::getRenderPosition()
{
    return render_position;
}

int Enemy::getVelocityInYDirection()
{
    return velocity_in_y_direction;
}

void Enemy::render()
{
    SDL_SetRenderDrawColor(
        game_renderer,
        this->enemy_color.r,
        this->enemy_color.g,
        this->enemy_color.b,
        this->enemy_color.a);
    SDL_RenderFillRect(game_renderer, &enemy_size);

    enemy_size.y += velocity_in_y_direction;
    render_position.y += velocity_in_y_direction;
}
