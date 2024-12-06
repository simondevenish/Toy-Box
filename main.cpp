#include <SDL3/SDL.h>
#include <stdio.h>

// Constants
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// Function prototypes
void HandleEvents(int* isRunning);

int main(int argc, char* argv[]) {
    SDL_Window* window; // Declare a pointer
    int isRunning = 1;  // Application running flag

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        const char* sdlError = SDL_GetError();
        if (sdlError && sdlError[0] != '\0') {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: %s\n", sdlError);
        } else {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: Unknown error\n");
        }
        return 1;
    }


    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Toy Box",                  // Window title
        WINDOW_WIDTH,               // Width, in pixels
        WINDOW_HEIGHT,              // Height, in pixels
        SDL_WINDOW_VULKAN           // Flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Main event loop
    while (isRunning) {
        HandleEvents(&isRunning);

        // Placeholder for rendering logic (if any)
        SDL_Delay(16); // Limit to ~60 FPS
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

void HandleEvents(int* isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT: // Renamed from SDL_QUIT
                *isRunning = 0;
                break;
            case SDL_EVENT_KEY_DOWN: // Renamed from SDL_KEYDOWN
                if (event.key.scancode == SDL_SCANCODE_ESCAPE) { // Direct access to scancode
                    *isRunning = 0;
                }
                break;
            default:
                break;
        }
    }
}
