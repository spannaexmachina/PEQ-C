//
//  PEQ_engine.h
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#ifndef PEQ_engine_h
#define PEQ_engine_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "PEQ_texture_manager.h"
#include "PEQ_colour.h"
#include "PEQ_SETTINGS.h"
#include "point2D.h"



typedef enum window {
    WINDOW,                     /**< Open in a fixed size window  */
    RESIZABLE,                  /**< Open in a resizable window */
    FULLSCREEN                  /**< Open in fullscreen */
} PEQ_WINDOW_MODE;

typedef enum {
    PEQ_RECT,
    PEQ_LINE,
    PEQ_POINT
} PEQ_2Dtype;

typedef union {
    struct rect {
        int         ID;
        PEQ_2Dtype  type;
        COLOUR_NAME colour;
        point2D     p;
        int         width,
                    height;
    } rect;
    struct line {
        int         ID;
        PEQ_2Dtype  type;
        COLOUR_NAME colour;
        point2D     p1,
                    p2;
    } line;
    struct point {
        int           ID;
        PEQ_2Dtype    type;
        COLOUR_NAME   colour;
        point2D       p;
    } point;
} PEQ_2D_graphic;

typedef struct data {
    SDL_Renderer *renderer;     /**< pointer to application renderer */
    SDL_Window *window;         /**< pointer to application window */
    int is_running,             /**< is the application running; 0 false */
        win_height,             /**< application window height (set in precompile) */
        win_width,              /**< application window width (set in precompile) */
        FPS,                    /**< application frames per second (set in precompile) */
        delay_time,             /**< application delay time (set in precompile) */
        x,                      /**< application window x coordinate (set in precompile) */
        y;                      /**< application window y coordinate (set in precompile) */
    Uint32 frame_start,         /**< used to track starting frame rate */
           frame_time;          /**< used to track frame rate speed after loop */
    char title[20];             /**< application title, used for window title, etc. */
    PEQ_COLOUR r_colour;        /**< background render colour (set in precompiler) */
    PEQ_WINDOW_MODE window_mode;/**< window mode (set at precompile) */
    PEQ_TEXTURE texture_manager[5]; /**< stores textures to be used */
    PEQ_2D_graphic twoD_objects[];
} PEQ_DATA;

//todo move shapes
void PEQ_draw_line(SDL_Renderer *r, COLOUR_NAME colour, point2D p1, point2D p2);

void PEQ_draw_rect(SDL_Renderer *r, COLOUR_NAME colour, point2D p, int width, int height);
void PEQ_draw_all_2D(SDL_Renderer *r, PEQ_2D_graphic *objects[]);
/**
 * \brief returns an SDL window mode based on PEQ enum
 *
 * \note avaliabe window option are WINDOW; RESIZABLE; FULLSCREEN;
 * \param w_mode PEQ enum window mode
 * \returns SDL window flag
 */
int get_window_mode(PEQ_WINDOW_MODE w_mode);

/**
 * \brief Primary initialising function
 * \par initialises SDL; window; and renderer
 * \param data PEQ_DATA type pointer
 * \returns 1 pass, 0 fail
 */
int PEQ_init(PEQ_DATA *data);

/**
 * \brief primary engine loop for handling events
 * \param data PEQ_DATA type pointer
 * \returns 0 success
 */
int PEQ_handle_events(PEQ_DATA *data);

/**
 * \brief primary engine loop for rendering
 * \param data PEQ_DATA type pointer
 * \returns 0 success
 */
int PEQ_render(PEQ_DATA *data);

/**
 * \brief destroys application
 * \param data PEQ_DATA type pointer
 * \returns 0 success; -1 fail
 */
int PEQ_clean(PEQ_DATA *data);

/**
 * \brief primary control loop
 * \par handles framerate control and application loop
 * \param data PEQ_DATA type pointer
 * \returns 0 success; -1 fail
 */
int PEQ_cycle(PEQ_DATA *data);

/**
 */
int PEQ_update(PEQ_DATA *data);

/**
 *
 *
 */
int load_texture_manager(PEQ_DATA *data);

/**
 * \brief populates a PEQ_DATA struct
 * \param data PEQ_DATA type pointer to populate
 * \param r SDL_Renderer type pointer
 * \param w SDL_Window type pointer
 * \returns 0 success;
 */
int pop_main_data(PEQ_DATA *data/*, SDL_Renderer *r, SDL_Window */);




#endif /* PEQ_engine_h */
