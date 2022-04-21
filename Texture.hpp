/*
===============================
Our Texture class
===============================
*/

#pragma once

#if !defined(HEADER_INCLUDED)
#include "Headers.hpp"
#endif

#if !defined(GAME_RENDERER_EXIST)
#define GAME_RENDERER_EXIST 1
SDL_Renderer *game_renderer;
#endif

#if !defined(GAME_FONT_EXIST)
#define GAME_FONT_EXIST 1
TTF_Font *game_font;
#endif

class Texture
{

public:
    // Construstor
    Texture();

    // Destructor
    ~Texture();

    // Create a Texture out of image path provide
    bool loadFromFile(std::string path, bool colorKeying = false);

    // if SDL_ttf.h is include then it create a texture out of text, color provide
#if defined(SDL_TTF_MAJOR_VERSION)
    bool loadFromRenderedText(std::string text, SDL_Color color);
#endif

    // It is used to free up the resource we have used for Texture
    void free();

    // It is used to set the value of alpha
    void setAlpha(Uint8 alpha);

    // It is used to set the blending mode
    void setBlendMode(SDL_BlendMode blending);

    // It is used to set the color mode
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // It is used to render the texture in the window
    void render(int x, int y, SDL_Rect *renderRect = NULL, SDL_Rect *renderQuad = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // It is used to get the height and width of the Texture
    int getWidth();
    int getHeight();

private:
    // Variable where loaded Texture is stored
    SDL_Texture *mTexture;

    // Variable to store height and width of Texture
    int mWidth;
    int mHeight;
};
