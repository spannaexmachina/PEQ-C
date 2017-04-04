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

//window settings
#define WINDOW_X 100
#define WINDOW_Y 100
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "Pequod-C"
#define WINDOW_MODE WINDOW
#define FPS_DEF 60;
const int DELAY_TIME_DEF = 1000.0f / FPS_DEF;

enum PEQ_WINDOW_MODE {
    WINDOW,
    RESIZABLE,
    FULLSCREEN
};

typedef struct PEQ_DATA {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int is_running, win_height, win_width, FPS, delay_time, x, y;
    Uint32 frame_start, frame_time;
    char title[20];
    enum PEQ_WINDOW_MODE window_mode;
} PEQ_DATA;

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

int PEQ_init(struct PEQ_DATA *data)
{
    //extern int app_running;
    
    printf("initialising SDL...\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        printf("SDL initialised!\n");
        if ((data->window = SDL_CreateWindow("test", data->x, data->y, data->win_width, data->win_height, get_window_mode(data->window_mode)))) {
            printf("Window initialised!\n");
            if ((data->renderer = SDL_CreateRenderer(data->window, -1, 0))) {
                printf("Renderer initialised!\nInitialisation complete!\ndrawing window...\n");
                SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 255);
                return 1;
            } else
                printf("Renderer failed to initialise; ERROR: %s\n", SDL_GetError());
        } else
            printf("Window failed to initialise; ERROR: %s\n", SDL_GetError());
    } else
        printf("SDL failed to initialise; ERROR: %s\n", SDL_GetError());
    return 0;
}

int PEQ_handle_events(struct PEQ_DATA *data)
{
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                data->is_running = 0;
                break;
            default:
                break;
        }
    }
    return 0;
}

int PEQ_render(struct PEQ_DATA *data)
{
    SDL_RenderClear(data->renderer);
    SDL_RenderPresent(data->renderer);
    return 0;
}

int PEQ_cycle(struct PEQ_DATA *data)
{
    data->frame_start = SDL_GetTicks();
    
    PEQ_handle_events(data);
    PEQ_render(data);
    
    data->frame_time = SDL_GetTicks() - data->frame_start;
    if (data->frame_start < data->delay_time)
        SDL_Delay((int)data->delay_time - data->frame_time);
    
    return 0;
}

void pop_main_data(struct PEQ_DATA *data, SDL_Renderer *r, SDL_Window *w)
{
    data->frame_start = data->frame_time = data->is_running = 0;
    data->renderer = r;
    data->window = w;
    data->FPS = FPS_DEF;
    data->delay_time = DELAY_TIME_DEF / data->FPS;
    data->win_height = WINDOW_HEIGHT;
    data->win_width = WINDOW_WIDTH;
    strcpy(data->title, WINDOW_TITLE);
    data->x = WINDOW_X;
    data->y = WINDOW_Y;
    data->window_mode = WINDOW_MODE;
    
}

int main(int argc, char* argv[])
{
    //extern int app_running;
    
    struct PEQ_DATA data;
    
    SDL_Renderer *renderer = 0;
    SDL_Window *window = 0;
    
    pop_main_data(&data, renderer, window);
    
    
    printf("booting up...\n");
    
    for (data.is_running = PEQ_init(&data); data.is_running != 0; PEQ_cycle(&data)) {
        }
    
    
    printf("cleaning...\n");
    SDL_Quit();
    
    return 0;
}



