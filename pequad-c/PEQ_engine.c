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
                printf("Renderer initialised!\nloading objects...\n");
                load_objects(data);
                printf("initialisation complete!\nrunning...\n*\n\n");
                if (data->r_colour.name != TRANSPARENT && !(SDL_SetRenderDrawColor(data->renderer, data->r_colour.r, data->r_colour.g, data->r_colour.b, data->r_colour.a))) {
                    return 1;
                } else
                    printf("Renderer colour error; colour %u not recognised or is illegal\n", data->r_colour.name);
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

int PEQ_render(PEQ_DATA *data)
{
    SDL_SetRenderDrawColor(data->renderer, data->r_colour.r, data->r_colour.g,data->r_colour.b, data->r_colour.a);
    SDL_RenderClear(data->renderer);
    
    
    
    PEQ_draw_shape(data->renderer, &r1);
  
    PEQ_draw_shape(data->renderer, &l1);
    PEQ_draw_shape(data->renderer, &c1);
    
    //cosmic rain
    for (int i = 0; i < 100; i++) {
        data->object_bank[4].graphic.shape = PEQ_get_point(makepoint(PEQ_rand(0, WINDOW_WIDTH), PEQ_rand(0, WINDOW_HEIGHT)), PEQ_rand(0, 3));
        PEQ_draw_shape(data->renderer, &data->object_bank[4].graphic.shape);
    }
    
    //new kind of array call
    for (int i = 0; i < 8; i++)
        PEQ_draw_shape(data->renderer, &data->object_bank[i].graphic.shape);
   
    
    SDL_RenderPresent(data->renderer);
    SDL_Delay(100);
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
    
    //update random colours
    data->object_bank[0].graphic.shape.rect.colour = PEQ_rand_colour(255);
    data->object_bank[1].graphic.shape.rect.colour = PEQ_rand_colour(0);
    
    //move rectangle
    if (data->object_bank[0].graphic.shape.rect.p.x + data->object_bank[0].graphic.shape.rect.width < WINDOW_WIDTH)
        data->object_bank[0].graphic.acc.x++;
    else {
        data->object_bank[0].graphic.acc.x = 0;
    }
    data->object_bank[0].graphic.shape.rect.p.x += data->object_bank[0].graphic.acc.x;
    
    //fades!!
    obj_fade(&data->object_bank[3], 20);
    obj_fade(&data->object_bank[7], 10);
    
    //giggly darkstar!
        data->object_bank[8].texture.texture.position.x += PEQ_rand(-2, 3);
        data->object_bank[8].texture.texture.position.y += PEQ_rand(-3, 2);
    
    
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


//load objects in here:
void load_objects(PEQ_DATA *data)
{
    //todo load from file
    int count = 9;
    //graphics
    data->object_bank[0].graphic.shape = PEQ_get_rect(makepoint(110, 100), 200, 400, PEQ_rand(0, 5));
    data->object_bank[1].graphic.shape = PEQ_get_rect(makepoint(100, 100), 200, 400, PEQ_rand(0, 5));
    data->object_bank[2].graphic.shape = PEQ_get_line(makepoint(50, 500), makepoint(600, 50), RED);
    data->object_bank[7].graphic.shape = PEQ_get_circ(RED, makeSDLpoint(100, 100), 50);
    data->object_bank[4].graphic.shape = PEQ_get_point(makepoint(PEQ_rand(0, WINDOW_WIDTH), PEQ_rand(0, WINDOW_HEIGHT)), PEQ_rand(0, 3));
    data->object_bank[5].graphic.shape = PEQ_get_line(makepoint(100, 100), makepoint(200, 200), WHITE);
    data->object_bank[6].graphic.shape = PEQ_get_rect(makepoint(200, 200), 150, 200, RED);
    data->object_bank[3].graphic.shape = PEQ_get_rect(makepoint(200, 200), 200, 200, RED);
    //textures
    data->object_bank[8].texture.texture = PEQ_get_texture(data->renderer, "darkstar", "assets/images/darkstar.png", makepoint(300, 300), SDL_FLIP_NONE);
    
    for (int i = 0; i < count; i++) {
        if (data->object_bank[i].texture.texture.texture != 0)
            data->object_bank[i].texture.type = TEXTURE;
        //todo shape handling
    }
}


int pop_main_data(PEQ_DATA *data)
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
    data->x = WINDOW_WIDTH;
    data->y = WINDOW_Y;
    data->window_mode = WINDOW_MODE;
    return 0;
}
