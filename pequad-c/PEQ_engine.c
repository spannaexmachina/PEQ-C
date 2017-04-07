//
//  PEQ_engine.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_engine.h"


int get_window_mode(PEQ_WINDOW_MODE w_mode)
{
    switch (w_mode) {
        case RESIZABLE: return SDL_WINDOW_RESIZABLE; break;
        case FULLSCREEN: return SDL_WINDOW_FULLSCREEN; break;
        case WINDOW: return SDL_WINDOW_SHOWN; break;
        default: return SDL_WINDOW_SHOWN; break;
    }
}

int PEQ_init(PEQ_DATA *data)
{
    printf("initialising SDL...\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        printf("SDL initialised!\n");
        if ((data->window = SDL_CreateWindow(data->title, data->x, data->y, data->win_width, data->win_height, get_window_mode(data->window_mode)))) {
            printf("Window initialised!\n");
            if ((data->renderer = SDL_CreateRenderer(data->window, -1, 0))) {
                printf("Renderer initialised!\ninitialising PEQ texture manager\n");
                //if (load_texture_manager(data) != 0) {
                    printf("success!\nPEQ initialised initialised!\nInitialisation complete!\ndrawing window...\n");
                    if (data->r_colour.name != TRANSPARENT && !(SDL_SetRenderDrawColor(data->renderer, data->r_colour.r, data->r_colour.g, data->r_colour.b, data->r_colour.a))) {
                            return 1;
                   // } else
                        //printf("Renderer colour error; colour %u not recognised or is illegal\n", data->r_colour.name);
                } else
                    printf("Failed to initialise PEQ texture manager\n");
            } else
                printf("Renderer failed to initialise; ERROR: %s\n", SDL_GetError());
        } else
            printf("Window failed to initialise; ERROR: %s\n", SDL_GetError());
    } else
        printf("SDL failed to initialise; ERROR: %s\n", SDL_GetError());
    return 0;
}

int PEQ_handle_events(PEQ_DATA *data)
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

void PEQ_draw_line(SDL_Renderer *r, COLOUR_NAME colour, point2D p1, point2D p2)
{
    PEQ_COLOUR c = get_colour(colour);
    
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(r, p1.x, p1.y, p2.x, p2.y);
}

void PEQ_draw_rect(SDL_Renderer *r, COLOUR_NAME colour, point2D p, int width, int height)
{
    PEQ_COLOUR c = get_colour(colour);
    SDL_Rect rect;
    
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    rect.x = p.x;
    rect.y = p.y;
    rect.w = width;
    rect.h = height;
    SDL_RenderDrawRect(r, &rect);
}
//////////working
void PEQ_draw_all_2D(SDL_Renderer *r, PEQ_2D_graphic *objects[])
{
    int i;
    for (i = 0; i != '\0'; i++) {
        if (objects[i] == PEQ_RECT) {
            PEQ_draw_rect(r, objects[i]->rect.colour, objects[i]->rect.p, objects[i]->rect.width, objects[i]->rect.height);
        }
    }
}


int PEQ_render(PEQ_DATA *data)
{
    SDL_SetRenderDrawColor(data->renderer, data->r_colour.r, data->r_colour.g,data->r_colour.b, data->r_colour.a);
    SDL_RenderClear(data->renderer);
    //PEQ_TEXTURE *text = PEQ_get_texture("assets/rider.bmp", "rider", data->renderer);
   // PEQ_draw(text, 100, 100, 0, 0, data->renderer, SDL_FLIP_NONE);
    
    PEQ_draw_line(data->renderer, WHITE, makepoint(100, 100), makepoint(200, 200));
    PEQ_draw_rect(data->renderer, RED, makepoint(200, 200), 150, 200);
    PEQ_draw_rect(data->renderer, RED, makepoint(200, 200), 200, 200);
    
    //printf("frame time: %u\n", data->frame_time); //print frame time debug
    
    SDL_RenderPresent(data->renderer);
    return 0;
}

int PEQ_clean(PEQ_DATA *data)
{
    printf("cleaning...\n");
    SDL_DestroyRenderer(data->renderer);
    printf("renderer destroyed!\n");
    SDL_DestroyWindow(data->window);
    printf("window destroyed!\n");
    
    
    return 0;
}

int PEQ_update(PEQ_DATA *data)
{
    PEQ_handle_events(data);
    
    return 0;
}

int PEQ_cycle(PEQ_DATA *data)
{
    data->frame_start = SDL_GetTicks();
    
    PEQ_update(data);
    PEQ_render(data);
    
    data->frame_time = SDL_GetTicks() - data->frame_start;
    if (data->frame_start < data->delay_time)
        SDL_Delay((int)data->delay_time - data->frame_time);
    
    return 0;
}

int pop_main_data(PEQ_DATA *data/*, SDL_Renderer *r, SDL_Window */)
{
    data->frame_start = data->frame_time = data->is_running = 0;
    data->renderer = 0;
    data->window = 0;
    data->r_colour = get_colour(BACKGROUND_COLOUR);
    data->FPS = FPS_DEF;
    data->delay_time = DELAY_TIME_DEF;
    data->win_height = WINDOW_HEIGHT;
    data->win_width = WINDOW_WIDTH;
    strcpy(data->title, WINDOW_TITLE);
    data->x = WINDOW_X;
    data->y = WINDOW_Y;
    data->window_mode = WINDOW_MODE;
    return 0;
}

int load_texture_manager(PEQ_DATA *data)
{
    //todo read from file!
    int count = 1;
    char tempfilename[100];
    char temptextureID[20];
    strcpy(tempfilename, "assets/rider.bmp");
    strcpy(temptextureID, "rider");
    
    for (int i = 0; i < count; i++) {
        printf("entered texture loop\n");
        //data->texture_manager[i].texture = NULL;
        strcpy(data->texture_manager[i].filename, tempfilename);
        strcpy(data->texture_manager[i].textureID, temptextureID);
        PEQ_load_texture(data->renderer, &data->texture_manager[i]);
    }
    
    return 0;
}
