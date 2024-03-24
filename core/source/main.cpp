#include <SDL.h>
#include <SDL_image.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#ifdef _WIN32
#define main SDL_main
#endif

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Hello, World!",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1920, 1080,
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP
    );

    if (window == nullptr) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());

        SDL_Quit();

        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr) {
        SDL_Log("Could not create renderer: %s\n", SDL_GetError());

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    SDL_Surface* imageSurface = IMG_Load("resources/image.png");

    if (imageSurface == nullptr) {
        SDL_Log("Could not load image: %s\n", IMG_GetError());

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, imageSurface);

    if (image == nullptr) {
        SDL_Log("Could not create texture from surface: %s\n", SDL_GetError());

        SDL_FreeSurface(imageSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    SDL_FreeSurface(imageSurface);

    SDL_SetRenderTarget(renderer, image);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);

    SDL_Point imageSize;
    SDL_QueryTexture(image, nullptr, nullptr, &imageSize.x, &imageSize.y);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    bool bRunning = true;

    while (bRunning) {
        SDL_Event sdlEvent;

        while (SDL_PollEvent(&sdlEvent)) {
            if (sdlEvent.type == SDL_QUIT) {
                bRunning = false;
            }

            ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.f, 0.f));

        ImGui::Begin("Image Displayer");
        ImGui::Image(
            image,
            ImVec2(
                static_cast<float>(imageSize.x),
                static_cast<float>(imageSize.y)
            )
        );
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();

        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
