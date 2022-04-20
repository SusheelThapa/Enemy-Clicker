#include "Game.cpp"

int main(int argc, char *arg[])
{
    bool quit = false;

    if (initialize())
    {
        if (loadWindow() && loadResourcesTexture())
        {
            while (!quit)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 255);

                SDL_RenderClear(game_renderer);

                game_homepage.render(0, 0);

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