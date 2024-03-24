#include <SDL2/SDL.h>

#ifdef _WIN32
#define main SDL_main
#endif

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Hello, World!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());

        SDL_Quit();

        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        SDL_Log("Could not create renderer: %s\n", SDL_GetError());

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    bool bRunning = true;

    while (bRunning) {
        SDL_Event sdlEvent;

        while (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_QUIT) {
                bRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
