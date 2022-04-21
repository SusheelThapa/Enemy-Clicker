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

    if (!game_over.loadFromFile("images/game-over.png"))
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

    Enemy enemy;
    while (enemies.size() <= TOTAL_NUMBER_OF_ENEMY)
    {
        enemy.initialize();
        enemies.push_back(enemy);
    }
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

                current_texture = &game_homepage;
            }
            /*exit button is click*/
            else if (x > 100 && x < 400 && y > 430 && y < 510)
            {
                printf("Exit button in pressed");
                return true;
            }
        }

        /*When user click over the enemy in the game*/
        if (e.type == SDL_MOUSEBUTTONDOWN && current_texture == &game_background)
        {
            int x, y;

            /*Get current position of the mouse*/
            SDL_GetMouseState(&x, &y);

            /*Finds which enemy is clicked and remove it and load new enemy*/
            SDL_Rect current_enemy_size;

            for (int i = 0; i < 5; i++)
            {
                current_enemy_size = enemies[i].getEnemySize();

                if (x > current_enemy_size.x && x < (current_enemy_size.x + current_enemy_size.w) && (y > current_enemy_size.y && x < (current_enemy_size.y + current_enemy_size.h)))
                {
                    // std::cout << "Enemy is clicked" << std::endl;
                    enemies.erase(enemies.begin() + i);
                    loadEnemy();
                }
            }
        }
    }

    return false;
}
void startGame()
{

    while (total_life != 0)
    {
        if (handleEvents())
        {
            close();
            exit(0);
        }

        SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 255);

        SDL_RenderClear(game_renderer);

        current_texture->render(0, 0);

        for (int i = 0; i < TOTAL_NUMBER_OF_ENEMY; i++)
        {
            /*when enemies touch the ground we reduce the life and remove enemies*/
            if (enemies[i].getEnemySize().y + enemies[i].getEnemySize().h > SCREEN_HEIGHT)
            {
                total_life -= 1;
                if (total_life == 0)
                {
                    game_over.render(0, 0);

                    SDL_RenderPresent(game_renderer);

                    SDL_Delay(1000);
                    break;
                }

                // printf("Remaining life %d", total_life);

                enemies.erase(enemies.begin() + i);
                loadEnemy();
            }
            enemies[i].render();
        }

        SDL_RenderPresent(game_renderer);
    }

    /*Resetting total life for next game*/
    total_life = 3;
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
