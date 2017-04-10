//
//  PEQ_engine.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_engine.h"
#include <stdlib.h>


// application data file
static PEQ_DATA m_data;


qbool PEQ_exit_request() {return m_data.window_d.is_running;}


static void set_window_mode(PEQ_WINDOW_MODE m)
{
    int r;
    switch (m) {
        case RESIZABLE: r = SDL_WINDOW_RESIZABLE; break;
        case FULLSCREEN: r = SDL_WINDOW_FULLSCREEN; break;
        case WINDOW: r = SDL_WINDOW_SHOWN; break;
        default: r = SDL_WINDOW_SHOWN; break;
    }
    m_data.window_d.window_mode = r;
}



qbool PEQ_init()
{
    if (m_data.is_loaded == FALSE) {         //if renderer isn't yet active
        printf("* Pequod-C *\nWarming up...\n");
        set_window_mode(WINDOW_MODE);
        m_data.frame_rate.frame_time = 0;
        m_data.frame_rate.frame_start = 0;
        m_data.window_d.is_running = 0;
        m_data.window_d.colour = get_colour(BACKGROUND_COLOUR);
        m_data.frame_rate.FPS = FPS_DEF;
        m_data.frame_rate.delay_time = DELAY_TIME_DEF;
        m_data.window_d.height = WINDOW_HEIGHT;
        m_data.window_d.width = WINDOW_WIDTH;
        strcpy(m_data.window_d.title, WINDOW_TITLE);
        m_data.window_d.x = WINDOW_X;
        m_data.window_d.y = WINDOW_Y;
        
        m_data.is_loaded = TRUE;    //set to true
        
        if (!m_data.window_d.is_running) { //if window isn't already running
            srand(SDL_GetTicks()); //seed random number based on milliseconds passed since init
            printf("initialising SDL...\n");
            if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
            printf("SDL initialised!\n");
                if ((m_data.window_d.window = SDL_CreateWindow(m_data.window_d.title, m_data.window_d.x, m_data.window_d.y, m_data.window_d.width, m_data.window_d.height, m_data.window_d.window_mode))) {
                    printf("Window initialised!\n");
                    if ((m_data.renderer = SDL_CreateRenderer(m_data.window_d.window, -1, 0))) {
                        printf("Renderer initialised!\nloading objects...\n");
                        TTF_Init(); //init text api
                        load_objects(&m_data); //FIXME: phase out
                        printf("initialisation complete!\nrunning...\n*\n\n");
                        if (m_data.window_d.colour.name != TRANSPARENT && !(SDL_SetRenderDrawColor(m_data.renderer, m_data.window_d.colour.r, m_data.window_d.colour.g, m_data.window_d.colour.b, m_data.window_d.colour.a))) {
                            m_data.window_d.is_running = TRUE;
                            return 1;
                        } else
                            printf("Renderer colour error; colour %u not recognised or is illegal\n", m_data.window_d.colour.name);
                    } else
                        printf("Renderer failed to initialise; ERROR: %s\n", SDL_GetError());
                } else
                    printf("Window failed to initialise; ERROR: %s\n", SDL_GetError());
            } else
                printf("SDL failed to initialise; ERROR: %s\n", SDL_GetError());
        } else
            printf("cannot init; PEQ already running!\n");
    }
    return 0;
}

qbool PEQ_handle_events()
{
    CHECK_INIT
    
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_data.window_d.is_running = 0;
                break;
            default:
                break;
        }
    }
    
    return TRUE;
}

void PEQ_clear_render()
{
    CHECK_INIT
    
    //start frame counter
    m_data.frame_rate.frame_start = SDL_GetTicks();
    
    if (m_data.renderer != 0) {
    SDL_SetRenderDrawColor(m_data.renderer, m_data.window_d.colour.r, m_data.window_d.colour.g, m_data.window_d.colour.b, m_data.window_d.colour.a);
    SDL_RenderClear(m_data.renderer);
    } else
        printf("no renderer!; init PEQ before rendering\n");
}

void PEQ_draw_render()
{
    CHECK_INIT
    
    SDL_RenderPresent(m_data.renderer);
    
    //calculate frame rate after render
    m_data.frame_rate.frame_time = SDL_GetTicks() - m_data.frame_rate.frame_start;
    if (m_data.frame_rate.frame_start < m_data.frame_rate.delay_time)
        SDL_Delay((int)m_data.frame_rate.delay_time - m_data.frame_rate.frame_time);
    if (m_data.window_d.is_running == 0) PEQ_clean(); //clean if exit
}

qbool PEQ_render()
{
    PEQ_draw_obj(m_data.renderer, &m_data.object_bank[8]);
    
    //cosmic rain
    for (int i = 0; i < 100; i++) {
        m_data.object_bank[4].graphic.shape = PEQ_get_point(makepoint(PEQ_rand(0, WINDOW_WIDTH), PEQ_rand(0, WINDOW_HEIGHT)), PEQ_rand(0, 3));
        PEQ_draw_shape(m_data.renderer, &m_data.object_bank[4].graphic.shape);
    }
    
    //new kind of array call
    for (int i = 0; i < 8; i++)
        PEQ_draw_shape(m_data.renderer, &m_data.object_bank[i].graphic.shape);
   
    SDL_Delay(100);
    return 0;
}

qbool PEQ_clean()
{
    CHECK_INIT
    
    printf("cleaning...\n");
    SDL_DestroyRenderer(m_data.renderer);
    printf("renderer destroyed!\n");
    SDL_DestroyWindow(m_data.window_d.window);
    printf("window destroyed!\n");
    printf("cleaning SDL_TTF...\n");
    TTF_Quit();
    printf("cleaning SDL...\n");
    SDL_Quit();
    
    return 0;
}

qbool PEQ_update()
{
    PEQ_handle_events();
    
    //update random colours
    m_data.object_bank[0].graphic.shape.rect.colour = PEQ_rand_colour(255);
    m_data.object_bank[1].graphic.shape.rect.colour = PEQ_rand_colour(0);
    
    //move rectangle
    if (m_data.object_bank[0].graphic.shape.rect.p.x + m_data.object_bank[0].graphic.shape.rect.width < WINDOW_WIDTH)
        m_data.object_bank[0].graphic.acc.x++;
    else {
        m_data.object_bank[0].graphic.acc.x = 0;
    }
    m_data.object_bank[0].graphic.shape.rect.p.x += m_data.object_bank[0].graphic.acc.x;
    
    //fades!!
    obj_fade(&m_data.object_bank[3], 20);
    obj_fade(&m_data.object_bank[7], 10);
    
    //giggly darkstar!
        m_data.object_bank[8].texture.texture.position.x += PEQ_rand(-2, 3);
        m_data.object_bank[8].texture.texture.position.y += PEQ_rand(-3, 2);
    
    
    return 0;
}

/*
qbool PEQ_cycle(PEQ_DATA *data)
{
    m_data.frame_rate.frame_start = SDL_GetTicks();
    
    PEQ_update(data);
    PEQ_render(data);
    
    m_data.frame_rate.frame_time = SDL_GetTicks() - m_data.frame_rate.frame_start;
    if (m_data.frame_rate.frame_start < m_data.frame_rate.delay_time)
        SDL_Delay((int)m_data.frame_rate.delay_time - m_data.frame_rate.frame_time);
    
    return 0;
}

 */

//load objects in here:
qbool load_objects()
{
    //todo load from file
    int count = 9;
    //graphics
    m_data.object_bank[0].graphic.shape = PEQ_get_rect(makepoint(110, 100), 200, 400, PEQ_rand(0, 5));
    m_data.object_bank[1].graphic.shape = PEQ_get_rect(makepoint(100, 100), 200, 400, PEQ_rand(0, 5));
    m_data.object_bank[2].graphic.shape = PEQ_get_line(makepoint(50, 500), makepoint(600, 50), RED);
    m_data.object_bank[7].graphic.shape = PEQ_get_circ(RED, makeSDLpoint(100, 100), 50);
    m_data.object_bank[4].graphic.shape = PEQ_get_point(makepoint(PEQ_rand(0, WINDOW_WIDTH), PEQ_rand(0, WINDOW_HEIGHT)), PEQ_rand(0, 3));
    m_data.object_bank[5].graphic.shape = PEQ_get_line(makepoint(100, 100), makepoint(200, 200), WHITE);
    m_data.object_bank[6].graphic.shape = PEQ_get_rect(makepoint(200, 200), 150, 200, RED);
    m_data.object_bank[3].graphic.shape = PEQ_get_rect(makepoint(200, 200), 200, 200, RED);
    //textures
    m_data.object_bank[8].texture.texture = PEQ_get_texture(m_data.renderer, "darkstar", "assets/images/darkstar.png", makepoint(300, 300), SDL_FLIP_NONE);
    
    for (int i = 0; i < count; i++) {
        if (m_data.object_bank[i].texture.texture.texture != 0)
            m_data.object_bank[i].texture.type = TEXTURE;
        //todo shape handling
    }
    return 0;
}

/*
qbool pop_main_data()
{
    m_data.window_d.window_mode = WINDOW_MODE;
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
 */
