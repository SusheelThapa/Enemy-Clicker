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

    /*Loading Game homepage Screen*/
    if (!game_homepage.loadFromFile("images/initial-game-image.png"))
    {
        std::cout
            << "Unable to load images.\nIMG_Error: "
            << IMG_GetError()
            << std::endl;

        status = false;
    }
    if (!game_homepage_start_button_hover.loadFromFile("images/game-start-btn-hover.png"))
    {
        std::cout
            << "Unable to load images.\nIMG_Error: "
            << IMG_GetError()
            << std::endl;

        status = false;
    }
    if (!game_homepage_exit_button_hover.loadFromFile("images/game-exit-btn-hover.png"))
    {
        std::cout
            << "Unable to load images.\nIMG_Error: "
            << IMG_GetError()
            << std::endl;

        status = false;
    }

    /*Loading animation images*/
    if (!game_loading_screen[LOADING_SCREEN_ONE].loadFromFile("images/game-loading-count-one.png"))
    {
        {
            std::cout
                << "Unable to load images.\nIMG_Error: "
                << IMG_GetError()
                << std::endl;

            status = false;
        }
    }

    if (!game_loading_screen[LOADING_SCREEN_TWO].loadFromFile("images/game-loading-count-two.png"))
    {
        {
            std::cout
                << "Unable to load images.\nIMG_Error: "
                << IMG_GetError()
                << std::endl;

            status = false;
        }
    }

    if (!game_loading_screen[LOADING_SCREEN_THREE].loadFromFile("images/game-loading-count-three.png"))
    {
        {
            std::cout
                << "Unable to load images.\nIMG_Error: "
                << IMG_GetError()
                << std::endl;

            status = false;
        }
    }

    return status;
}

bool handleEvents()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
        {
            return true;
        }

        if (e.type == SDL_MOUSEMOTION)
        {
            int x, y;

            SDL_GetMouseState(&x, &y);

            /*start button is hover*/
            if (x > 100 && x < 400 && y > 275 && y < 355)
            {
                current_texture = game_homepage_start_button_hover;
            }
            /*exit button is hover*/
            else if (x > 100 && x < 400 && y > 430 && y < 510)
            {
                current_texture = game_homepage_exit_button_hover;
            }
            else
            {
                current_texture = game_homepage;
            }
        }

        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;

            SDL_GetMouseState(&x, &y);

            /*start button is click*/
            if (x > 100 && x < 400 && y > 275 && y < 355)
            {
                // Need to Write Logic For this
            }
            /*exit button is click*/
            else if (x > 100 && x < 400 && y > 430 && y < 510)
            {
                return true;
            }
        }
    }

    return false;
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
