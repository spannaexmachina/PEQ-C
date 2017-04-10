//
//  PEQ_engine.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_engine.h"
#include <stdlib.h>

//forward declare
static pbool PEQ_init();

// application data file
static PEQ_DATA m_data;


/******************************************************************************************
 *
 *          PEQ-C CORE
 *
 ******************************************************************************************/

pbool PEQ_exit_request()
{
    PEQ_boot_if
    return m_data.window_d.is_running;
}

void PEQ_boot()
{
    if(m_data.is_loaded == FALSE)
        m_data.window_d.is_running = PEQ_init();
}

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


static pbool PEQ_init()
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
                        printf("Renderer initialised!\ninitialisint TTF\n");
                        TTF_Init(); //init text api
                        printf("initialisation complete!\nrunning...\n*\n\n");
                        if (m_data.window_d.colour.name != TRANSPARENT && !(SDL_SetRenderDrawColor(m_data.renderer, m_data.window_d.colour.r, m_data.window_d.colour.g, m_data.window_d.colour.b, m_data.window_d.colour.a))) {
                            m_data.window_d.is_running = TRUE;
                            return TRUE;
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
    return FALSE;
}

pbool PEQ_handle_events()
{
    PEQ_boot_if
    
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
    PEQ_boot_if
    
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
    PEQ_boot_if
    
    SDL_RenderPresent(m_data.renderer);
    
    //calculate frame rate after render
    m_data.frame_rate.frame_time = SDL_GetTicks() - m_data.frame_rate.frame_start;
    if (m_data.frame_rate.frame_start < m_data.frame_rate.delay_time)
        SDL_Delay((int)m_data.frame_rate.delay_time - m_data.frame_rate.frame_time);
    if (m_data.window_d.is_running == 0) PEQ_clean(); //clean if exit
}

pbool PEQ_clean()
{
    PEQ_boot_if
    
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



/******************************************************************************************
 *
 *          TEXTURES
 *
 ******************************************************************************************/


PEQ_IMAGE PEQ_load_image(char *image_name, char *filename)
{
    SDL_Surface* t_surface;
    PEQ_IMAGE t;
    
        if ((t_surface = IMG_Load(filename))) {
            t.PEQ_TEXTURE.texture = SDL_CreateTextureFromSurface(m_data.renderer, t_surface);
            if (t.PEQ_TEXTURE.texture) {
                t.PEQ_TEXTURE.src_width = t.width = t_surface->w;   //set image height and width to default
                t.PEQ_TEXTURE.src_height = t.height = t_surface->h;
                t.position.x = t.position.y = 0;    //default coordinates
                t.flip_flag = SDL_FLIP_NONE;    //set default flip to none
                strcpy(t.img_name, image_name);             //last thing--set image name
                strcpy(t.filename , filename);
                
                printf("%s (%s) loaded!\n", t.img_name, t.filename);
                SDL_FreeSurface(t_surface);
                
                return t;
            }
        }
    printf("skipped: %s. ERROR: %s\n", t.img_name, SDL_GetError());
    return t;
}

void PEQ_draw_image(PEQ_IMAGE *image)
{
    SDL_Rect src_r, dest_r;
    
    //assign texture data
    src_r.x = src_r.y = 0;
    src_r.w = image->PEQ_TEXTURE.src_width;
    src_r.h = image->PEQ_TEXTURE.src_height;
    
    //assign passed data
    dest_r.x = image->position.x;
    dest_r.y = image->position.y;
    dest_r.w = image->width;
    dest_r.h = image->height;
    
    //blit
    SDL_RenderCopyEx(m_data.renderer, image->PEQ_TEXTURE.texture, &src_r, &dest_r, 0, 0, image->flip_flag);
}



/******************************************************************************************
 *
 *          SHAPES
 *
 ******************************************************************************************/

void PEQ_draw_line(PEQ_LINE *line)
{
    
    SDL_SetRenderDrawColor(m_data.renderer, line->colour.r, line->colour.g, line->colour.b, line->colour.a);
    SDL_RenderDrawLine(m_data.renderer, line->p1.x , line->p1.y, line->p2.x, line->p2.y);
}

void PEQ_draw_rect(PEQ_RECT *rect)
{
    SDL_Rect t;
    
    t.x = rect->p.x;
    t.y = rect->p.y;
    t.h = rect->height;
    t.w = rect->width;
    
    SDL_SetRenderDrawColor(m_data.renderer, rect->colour.r, rect->colour.g, rect->colour.b, rect->colour.a);
    SDL_RenderDrawRect(m_data.renderer, &t);
}

void PEQ_draw_point(PEQ_POINT *point)
{
    SDL_SetRenderDrawColor(m_data.renderer, point->colour.r, point->colour.g, point->colour.b, point->colour.a);
    SDL_RenderDrawPoint(m_data.renderer, point->p.x, point->p.y);
}

void PEQ_draw_circle(PEQ_CIRCLE *circ)
{
    SDL_SetRenderDrawColor(m_data.renderer, circ->colour.r, circ->colour.g, circ->colour.b, circ->colour.a);
    
    for (float w = 0; w < circ->rad * 2; w++)
    {
        for (float h = 0; h < circ->rad * 2; h++)
        {
            float dx = circ->rad - w; // horizontal offset
            float dy = circ->rad - h; // vertical offset
            if ((dx*dx + dy*dy) <= (circ->rad * circ->rad))
            {
                SDL_RenderDrawPoint(m_data.renderer, circ->center.x + dx, circ->center.y + dy);
            }
        }
    }
}


