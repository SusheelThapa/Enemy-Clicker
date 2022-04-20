#include "Headers.hpp"
#include "Texture.cpp"

#define GAME_VERSION 1

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 800;
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

Texture current_texture;
Texture game_homepage;
Texture game_homepage_start_button_hover;
Texture game_homepage_exit_button_hover;
Texture game_loading_screen[LOADING_SCREEN_TOTAL];

bool initialize();
bool loadWindow();
bool loadResourcesTexture();
bool handleEvents();
void close();

#if defined(SDL_TTF_MAJOR_VERSION)
bool loadResourcesFont();
#endif