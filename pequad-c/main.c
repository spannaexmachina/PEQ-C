//
//  main.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE Test

#define FPS 60;
const int DELAY_TIME = 1000.0f / FPS;

enum PEQ_WINDOW_MODE {
    WINDOW,
    RESIZABLE,
    FULLSCREEN
};

int app_running = 0;

int get_window_mode(enum PEQ_WINDOW_MODE w_mode)
{
    switch (w_mode) {
        case RESIZABLE: return SDL_WINDOW_RESIZABLE; break;
        case FULLSCREEN: return SDL_WINDOW_FULLSCREEN; break;
        case WINDOW: return SDL_WINDOW_SHOWN; break;
        default: return SDL_WINDOW_SHOWN; break;
    }
}

int init(SDL_Renderer *r, SDL_Window *w, int x, int y, int width, int height, enum PEQ_WINDOW_MODE window_mode)
{
    extern int app_running;
    
    printf("initialising SDL...\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        printf("SDL initialised!\n");
        if ((w = SDL_CreateWindow("test", x, y, width, height, get_window_mode(window_mode)))) {
            printf("Window initialised!\n");
            if ((r = SDL_CreateRenderer(w, -1, 0))) {
                printf("Renderer initialised!\nInitialisation complete!\ndrawing window...\n");
                app_running = 1;
                SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
                return 1;
            } else
                printf("Renderer failed to initialise; ERROR: %s\n", SDL_GetError());
        } else
            printf("Window failed to initialise; ERROR: %s\n", SDL_GetError());
    } else
        printf("SDL failed to initialise; ERROR: %s\n", SDL_GetError());
    return 0;
}

int handle_events()
{
    extern int app_running;
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                app_running = 0;
                break;
            default:
                break;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    extern int app_running;
    Uint32 frame_start, frame_time;
    SDL_Renderer* renderer = 0;
    SDL_Window* window = 0;
    
    frame_start = frame_time = 0;
    printf("booting up...\n");
    for (init(renderer, window, 100, 100, 640, 480, WINDOW); app_running != 0; handle_events()) {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    printf("cleaning...\n");
    SDL_Quit();
    
    return 0;
}



