//
//  PEQ_engine.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//
//n
#include "PEQ_engine.h"
#include <stdlib.h>

//forward declare
static pbool PEQ_init();

//////////DATA///////////////

// application data file
static PEQ_DATA m_data;


/////////////////////////////

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

//window getters
int PEQ_get_window_height() {return m_data.window_d.height;}
int PEQ_get_window_width() {return m_data.window_d.width;}
int PEQ_get_window_x() {return m_data.window_d.x;}
int PEQ_get_window_y() {return m_data.window_d.y;}
char *PEQ_get_title() {return m_data.window_d.title;}

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
    //if renderer isn't yet active
    if (m_data.is_loaded == FALSE) {
        
        //load  init main data
        printf("* Pequod-C *\nWarming up...\n");
        m_data.frame_rate.frame_time = 0;
        m_data.frame_rate.frame_start = 0;
        m_data.window_d.is_running = 0;
        m_data.window_d.colour = get_colour(BACKGROUND_COLOUR);
        m_data.frame_rate.FPS = FPS_DEF;
        m_data.frame_rate.delay_time = DELAY_TIME_DEF;
        set_window_mode(WINDOW_MODE);
        m_data.window_d.height = WINDOW_HEIGHT;
        m_data.window_d.width = WINDOW_WIDTH;
        
        
        //set init title
        strcpy(m_data.window_d.title, WINDOW_TITLE);
        
        //set init window x, y
        m_data.window_d.x = WINDOW_X;
        m_data.window_d.y = WINDOW_Y;
        
        //set data loaded flag to true
        m_data.is_loaded = TRUE;
        
        //if window isn't already running
        if (!m_data.window_d.is_running) {
            
            //seed random number based on milliseconds passed since init
            srand(SDL_GetTicks());
            
            printf("initialising SDL...\n");
            
            //init SDL
            if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
            printf("SDL initialised!\n");
                
                //init window
                if ((m_data.window_d.window = SDL_CreateWindow(m_data.window_d.title, m_data.window_d.x, m_data.window_d.y, m_data.window_d.width, m_data.window_d.height, m_data.window_d.window_mode))) {
                    printf("Window initialised!\n");
                    
                    //init renderer
                    if ((m_data.renderer = SDL_CreateRenderer(m_data.window_d.window, -1, SDL_RENDERER_ACCELERATED))) {
                        printf("Renderer initialised!\ninitialisint TTF\n");
                        TTF_Init(); //init text api
                        printf("initialisation complete!\nrunning...\n*\n\n");
                        
                        //if window is resizable or fullscreen, get h&w values
                        if (m_data.window_d.window_mode != SDL_WINDOW_SHOWN)
                            PEQ_checkset_render_size();
                        
                        //set render colour
                        if (m_data.window_d.colour.name != TRANSPARENT && !(SDL_SetRenderDrawColor(m_data.renderer, m_data.window_d.colour.r, m_data.window_d.colour.g, m_data.window_d.colour.b, m_data.window_d.colour.a))) {
                            m_data.window_d.is_running = TRUE;
                            return TRUE;
                            
                        //error handling
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
    
    //todo (if resize etc)
    
    
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_data.window_d.is_running = 0;
                PEQ_clean(); //clean if exit
                break;
            case SDL_WINDOWEVENT:
                switch (e.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        PEQ_checkset_render_size();
                        break;
                    }
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
    
    SDL_SetRenderDrawColor(m_data.renderer, m_data.window_d.colour.r, m_data.window_d.colour.g, m_data.window_d.colour.b, m_data.window_d.colour.a);
    SDL_RenderClear(m_data.renderer);
}

void PEQ_draw_render()
{
    PEQ_boot_if
    
    SDL_RenderPresent(m_data.renderer);
}

void PEQ_frame_start()
{
    PEQ_boot_if
    
    //start frame counter
    m_data.frame_rate.frame_start = SDL_GetTicks();
}

void PEQ_frame_end()
{
    PEQ_boot_if
    
    //calculate frame rate after render
    m_data.frame_rate.frame_time = SDL_GetTicks() - m_data.frame_rate.frame_start;
    if (m_data.frame_rate.frame_start < m_data.frame_rate.delay_time)
        SDL_Delay((int)m_data.frame_rate.delay_time - m_data.frame_rate.frame_time);
}



static pbool PEQ_clean()
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

static void PEQ_checkset_render_size()
{
    SDL_GetRendererOutputSize(m_data.renderer, &m_data.window_d.width, &m_data.window_d.height);
}


/******************************************************************************************
 *
 *          TEXTURES - LOADING & DRAWING
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
 *          SHAPES - DRAWING            (See PEQ_geometry for other functions)
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


/******************************************************************************************
 *
 *          TEXT - DRAWING & LOADING
 *
 ******************************************************************************************/

PEQ_LABEL PEQ_load_label(char *text, char *font_file, int point_size, COLOUR_NAME col1, COLOUR_NAME col2, PEQ_TXT_BLEND blend)
{
    PEQ_LABEL t;
    SDL_Surface *t_surface;
    
    //load font
    t.render_d.font = TTF_OpenFont(font_file, point_size);
    
    //if successfull
    if (t.render_d.font != NULL) {
        
        //set colours
        t.colour1 = get_colour(col1);
        t.colour2 = get_colour(col2);
        SDL_Color tc1 = {t.colour1.r, t.colour1.g, t.colour1.b, t.colour1.a};
        SDL_Color tc2 = {t.colour2.r, t.colour2.g, t.colour2.b, t.colour2.a};
        
        //flip default to none
        t.render_d.flip_flag = SDL_FLIP_NONE;
        
        //copy text
        strcpy(t.text, text);
        
        //set blend
        t.render_d.blend_type = blend;
        
        //pos 0 as default
        t.pos.x = t.pos.y = 0;
        
        //load as per blend option
        switch (t.render_d.blend_type) {
            case SOLID:
                t_surface = TTF_RenderText_Solid(t.render_d.font, t.text, tc1);
                break;
            case SHADED:
                t_surface = TTF_RenderText_Shaded(t.render_d.font, t.text, tc1, tc2);
                break;
            case BLENDED:
                t_surface = TTF_RenderText_Blended(t.render_d.font, t.text, tc1);
                break;
            default:
                t_surface = TTF_RenderText_Solid(t.render_d.font, t.text, tc1);
                break;
        }
        //make texture
        t.render_d.texture = SDL_CreateTextureFromSurface(m_data.renderer, t_surface);
        
        if (t.render_d.texture)
            printf("label loaded! (%s)\n", t.text);
            //get sizes before freeing
            t.height = t_surface->h;
            t.width = t_surface->w;
            //free mem
            SDL_FreeSurface(t_surface);
        
            return t;
        }
    printf("could not load text %s; %s\n", t.text, SDL_GetError());
    return t;
}

void PEQ_draw_label(PEQ_LABEL *label)
{
    SDL_Rect src_r, dest_r;
    
    //assign texture data
    src_r.x = src_r.y = 0;
    src_r.w = label->width;
    src_r.h = label->height;
    
    //assign passed data
    dest_r.x = label->pos.x;
    dest_r.y = label->pos.y;
    dest_r.w = label->width;
    dest_r.h = label->height;
    
    //blit
    SDL_RenderCopyEx(m_data.renderer, label->render_d.texture, &src_r, &dest_r, 0, 0, label->render_d.flip_flag);
    
}



