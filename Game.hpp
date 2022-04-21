#include "Headers.hpp"
#include "Texture.cpp"
#include "Enemy.cpp"

#define GAME_VERSION 1

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 800;
const int TOTAL_NUMBER_OF_ENEMY = 6;
std::string GAME_NAME = "Enemy Clicker";

enum StartGameLoading
{
    LOADING_SCREEN_ONE,
    LOADING_SCREEN_TWO,
    LOADING_SCREEN_THREE,
    LOADING_SCREEN_TOTAL
};

SDL_Window *game_window; // SDL_Render is kept in Texture function
SDL_Event e;

#if defined(SDL_TTF_MAJOR_VERSION)
TTF_Font *game_primary_font, *game_secondary_font;
#endif

int total_life = 3;
Texture *current_texture;
Texture game_background;
Texture game_homepage;
Texture game_homepage_start_button_hover;
Texture game_homepage_exit_button_hover;
Texture game_over;
Texture game_loading_screen[LOADING_SCREEN_TOTAL];

std ::vector<Enemy> enemies;

bool initialize();
bool loadWindow();
bool loadResourcesTexture();
bool loadEnemy();
bool handleEvents();
void startGame();
void close();

#if defined(SDL_TTF_MAJOR_VERSION)
bool loadResourcesFont();
#endif