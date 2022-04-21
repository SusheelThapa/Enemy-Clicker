#include "Game.cpp"

int main(int argc, char *arg[])
{
    current_texture = &game_homepage;

    bool quit = false;

    if (initialize())
    {

#if defined(SDL_TTF_MAJOR_VERSION)
        if (!loadResourcesFont())
        {
            close();
            exit(0);
        }
#endif
        if (loadWindow() && loadResourcesTexture() && loadEnemy())
        {
            while (!quit)
            {

                if (handleEvents())
                {
                    quit = true;
                }

                SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 255);

                SDL_RenderClear(game_renderer);

                current_texture->render(0, 0);

                SDL_RenderPresent(game_renderer);
            }
        }
        else
        {
            std::cout << "Unable to render window";
        }
    }
    else
    {
        std::cout << "Unable to initalize\n";
    }

    close();

    return 0;
}