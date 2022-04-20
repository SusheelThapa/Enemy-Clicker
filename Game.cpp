#include "Game.hpp"

bool initialize()
{
    /*initialize function flag*/
    bool status = true;

    /*Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Unable to initialize SDL.\nSDL_GetError: " << SDL_GetError() << std::endl;
        status = false;
    }

#if defined(SDL_IMAGE_MAJOR_VERSION)

    /*Initialize SDL image()*/
    int image_flag = IMG_INIT_PNG;
    if (!(IMG_Init(image_flag) & image_flag))
    {
        std::cout << "Unable to initalize SDL Images.\nIMG_Error: " << IMG_GetError() << std::endl;
        status = false;
    }

#endif

#if defined(SDL_TTF_MAJOR_VERSION)

    /* Initialize SDL_ttf*/
    if (TTF_Init() == -1)
    {
        std::cout << "Unable to initalize SDL TTF.\nTTF_Error: " << TTF_GetError() << std::endl;
        status = false;
    }

#endif
    return status;
}

bool loadWindow()
{
    /*Window loader flag*/
    bool status = true;

    /*Create game window*/
    game_window = SDL_CreateWindow(
        GAME_NAME.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (game_window == nullptr)
    {
        std::cout
            << "Unable to create game window.\nSDL_Error:"
            << SDL_GetError()
            << std::endl;

        status = false;
    }
    else
    {
        /*Create game renderer*/
        game_renderer = SDL_CreateRenderer(
            game_window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (game_renderer == nullptr)
        {
            std::cout
                << "Unable to render game window.\nSDL_Error:"
                << SDL_GetError()
                << std::endl;

            status = false;
        }
    }

    return status;
}

bool loadResourcesTexture()
{
    bool status = true;

    if (!game_homepage.loadFromFile("images/initial-game-image.png"))
    {
        std::cout
            << "Unable to load images.\nIMG_Error: "
            << IMG_GetError()
            << std::endl;

        status = false;
    }
    return status;
}

void close()
{

    SDL_DestroyRenderer(game_renderer);
    SDL_DestroyWindow(game_window);

#if defined(SDL_IMAGE_MAJOR_VERSION)

    IMG_Quit();

#endif

    SDL_Quit();
}
