#include "Texture.hpp"

/*
=============================================================
Starting of the body of the function defined in Class Texture
=============================================================
*/

Texture::Texture()
{
    mWidth = 0;
    mHeight = 0;
    mTexture = NULL;
}

Texture::~Texture()
{
    free();
}

bool Texture ::loadFromFile(std::string path, bool colorKeying)
{
    this->free();

    SDL_Surface *new_surface = IMG_Load(path.c_str());

    if (new_surface == nullptr)
    {
        std::cout << "SDL_Error:" << SDL_GetError() << std::endl;
    }
    else
    {
        if (colorKeying)
        {
            SDL_SetColorKey(new_surface, SDL_TRUE, SDL_MapRGB(new_surface->format, 255, 255, 255));
        }

        mTexture = SDL_CreateTextureFromSurface(game_renderer, new_surface);

        if (mTexture == nullptr)
        {
            std::cout << "SDL_Error:" << SDL_GetError() << std::endl;
        }
        else
        {
            mWidth = new_surface->w;
            mHeight = new_surface->h;
        }

        SDL_FreeSurface(new_surface);
    }

    return mTexture != nullptr;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText(std::string text, SDL_Color color)
{
    bool status = true;

    SDL_Surface *temporary_surface = TTF_RenderText_Solid(game_primary_font, text.c_str(), color);

    if (temporary_surface == NULL)
    {
        std::cout << "SDL_Error :" << SDL_GetError() << std::endl;
        status = false;
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(game_renderer, temporary_surface);
        if (mTexture == NULL)
        {
            std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
            status = false;
        }

        else
        {
            mWidth = temporary_surface->w;
            mHeight = temporary_surface->h;
        }

        SDL_FreeSurface(temporary_surface);
    }

    return status;
}
#endif

void Texture::free()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect *renderRect, SDL_Rect *renderQuad, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    if (renderRect != NULL)
    {
        renderQuad->w = renderRect->w;
        renderQuad->h = renderRect->h;
    }

    // SDL_RenderCopy(game_renderer, mTexture, renderRect, NULL);

    SDL_RenderCopyEx(game_renderer, mTexture, renderRect, renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture ::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}
