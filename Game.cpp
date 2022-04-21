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

bool loadGameDetails()
{
    bool status = true;

    SDL_Color text_color = {260, 166, 135, 255};

    std::stringstream score_text;
    score_text.str("");
    score_text << "Score: " << score;
    if (!game_score.loadFromRenderedText(score_text.str().c_str(), text_color))
    {
        std::cout
            << "Unable to load texture from text.\nTTF_Error: "
            << TTF_GetError()
            << std::endl;

        status = false;
    }

    std::stringstream total_life_text;
    total_life_text.str("");
    total_life_text << "Life: " << total_life;
    if (!game_total_life.loadFromRenderedText(total_life_text.str().c_str(), text_color))
    {
        std::cout
            << "Unable to load texture from text.\nTTF_Error: "
            << TTF_GetError()
            << std::endl;

        status = false;
    }

    std::stringstream time_text;
    time_text.str("");
    time_text << "Time: " << total_game_time;
    if (!game_time.loadFromRenderedText(time_text.str().c_str(), text_color))
    {
        std::cout
            << "Unable to load texture from text.\nTTF_Error: "
            << TTF_GetError()
            << std::endl;

        status = false;
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
                    enemies.erase(enemies.begin() + i);
                    score += 1;
                    loadEnemy();
                }
            }
        }
    }

    return false;
}
void startGame()
{

    SDL_Rect renderQuadScore = {10, 5, 90, 30};
    SDL_Rect renderQuadLife = {10, 35, 90, 30};
    SDL_Rect renderQuadTime = {10, 65, 120, 30};

    int start_time = SDL_GetTicks();

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

                    renderQuadScore = {50, 500, 400, 100};

                    game_score.render(0, 0, nullptr, &renderQuadScore);

                    SDL_RenderPresent(game_renderer);

                    SDL_Delay(5000);
                    break;
                }

                enemies.erase(enemies.begin() + i);
                loadEnemy();
            }

            enemies[i].render();
        }

        total_game_time = (SDL_GetTicks() - start_time) / 1000.000f;

        loadGameDetails();

        game_score.render(0, 0, nullptr, &renderQuadScore);
        game_time.render(0, 0, nullptr, &renderQuadTime);
        game_total_life.render(0, 0, nullptr, &renderQuadLife);

        SDL_RenderPresent(game_renderer);

        // break;
    }

    /*Resetting total life for next game*/
    total_life = 3;
}
void close()
{

#if defined(SDL_TTF_MAJOR_VERSION)

    TTF_CloseFont(game_font);

#endif

    SDL_DestroyRenderer(game_renderer);
    SDL_DestroyWindow(game_window);

#if defined(SDL_TTF_MAJOR_VERSION)

    TTF_Quit();

#endif

#if defined(SDL_IMAGE_MAJOR_VERSION)

    IMG_Quit();

#endif

    SDL_Quit();
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool loadResourcesFont()
{
    bool status = true;

    game_font = TTF_OpenFont("fonts/cascadia.ttf", 28);

    if (game_font == nullptr)
    {
        std::cout << "Unable to load fonts.\nTTF_Error: " << TTF_GetError() << std::endl;
        status = false;
    }

    return status;
}
#endif
