#include <SDL3/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Toy Box"

void HandleEvents(int* isRunning);

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE,                      // Window title
        WINDOW_WIDTH,                      // Window width
        WINDOW_HEIGHT,                     // Window height
        SDL_WINDOW_VULKAN                  // Vulkan flag for future Kajiya integration
    );

    if (!window) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // SDL event loop
    int isRunning = 1;
    while (isRunning) {
        HandleEvents(&isRunning);

        // Placeholder for future kajiya rendering logic
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void HandleEvents(int* isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                *isRunning = 0;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    *isRunning = 0;
                }
                break;
            default:
                break;
        }
    }
}

