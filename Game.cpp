#include "Game.hpp"

bool initialize()
{

    srand(time(0));

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

    if (!game_background.loadFromFile("images/game-background.png"))
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

bool loadEnemy()
{
    bool status = true;

    enemies[0].initialize();
    enemies[1].initialize();
    enemies[2].initialize();
    enemies[3].initialize();
    enemies[4].initialize();

    return status;
}

bool handleEvents()
{
    while (SDL_PollEvent(&e) != 0)
    {
        /*If user press escape button or click X on window we quit the game*/
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
        {
            return true;
        }

        /*When user hover over the start and exit button*/
        if (e.type == SDL_MOUSEMOTION &&
            (current_texture == &game_homepage ||
             current_texture == &game_homepage_exit_button_hover ||
             current_texture == &game_homepage_start_button_hover))
        {
            int x, y;

            /*Get current position of the mouse*/
            SDL_GetMouseState(&x, &y);

            /*start button is hover*/
            if (x > 100 && x < 400 && y > 275 && y < 355)
            {
                current_texture = &game_homepage_start_button_hover;
            }
            /*exit button is hover*/
            else if (x > 100 && x < 400 && y > 430 && y < 510)
            {
                current_texture = &game_homepage_exit_button_hover;
            }
            else
            {
                current_texture = &game_homepage;
            }
        }

        /*When user click over the start or exit button*/
        if (e.type == SDL_MOUSEBUTTONDOWN &&
            (current_texture == &game_homepage ||
             current_texture == &game_homepage_exit_button_hover ||
             current_texture == &game_homepage_start_button_hover))
        {
            int x, y;

            /*Get current position of the mouse*/
            SDL_GetMouseState(&x, &y);

            /*start button is click*/
            if (x > 100 && x < 400 && y > 275 && y < 355)
            {
                current_texture = &game_background;

                /*Laoding Screen for the game when start button is pressed in rendered*/
                game_loading_screen[LOADING_SCREEN_THREE].render(0, 0);
                SDL_RenderPresent(game_renderer);
                SDL_Delay(800);

                game_loading_screen[LOADING_SCREEN_TWO].render(0, 0);
                SDL_RenderPresent(game_renderer);
                SDL_Delay(800);

                game_loading_screen[LOADING_SCREEN_ONE].render(0, 0);
                SDL_RenderPresent(game_renderer);
                SDL_Delay(800);

                startGame();
            }
            /*exit button is click*/
            else if (x > 100 && x < 400 && y > 430 && y < 510)
            {
                return true;
            }
        }

        /*When user click over the enemy in the game*/
        if (e.type == SDL_MOUSEBUTTONDOWN && current_texture == &game_background)
        {
            int x, y;

            /*Get current position of the mouse*/
            SDL_GetMouseState(&x, &y);

            SDL_Rect enemy_size[5];

            for (int i = 0; i < 5; i++)
            {
                enemy_size[i] = enemies[i].getEnemySize();

                if (x > enemy_size[i].x && x < (enemy_size[i].x + enemy_size[i].w) && (y > enemy_size[i].y && x < (enemy_size[i].y + enemy_size[i].h)))
                {
                    std::cout << "Enemy is clicked" << std::endl;
                }
            }
        }
    }

    return false;
}
void startGame()
{

    int life = 3;

    while (life != 0)
    {
        if (handleEvents())
        {
            close();
            exit(0);
        }

        SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 255);

        SDL_RenderClear(game_renderer);

        current_texture->render(0, 0);

        enemies[0].render();
        enemies[1].render();
        enemies[2].render();
        enemies[3].render();
        enemies[4].render();

        SDL_RenderPresent(game_renderer);

        if (SDL_GetTicks() > 10000)
        {
            exit(0);
        }
    }
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
