/************************************************************************************
 * Copyright (C) 2017  Michael Holmes et al.   <peqclib@gmail.com>                  *
 *                                                                                  *
 * This file is part of PEQUOD-C.                                                   *
 *                                                                                  *
 *      Redistribution and use in source and binary forms, with or                  *
 *      without modification, are permitted provided that the                       *
 *      following conditions are met:                                               *
 *                                                                                  *
 *          * Redistributions of source code must retain the above                  *
 *            copyright notice, this list of conditions and the                     *
 *            following disclaimer.                                                 *
 *                                                                                  *
 *          * Redistributions in binary form must reproduce the                     *
 *            above copyright notice, this list of conditions and                   *
 *            the following disclaimer in the documentation and/or                  *
 *            other materials provided with the distribution.                       *
 *                                                                                  *
 *          * Neither the name of PEQUOD-C, PEQ-C, PEQ, nor the                     *
 *            names of its contributors may be used to endorse or                   *
 *            promote products derived from this software without                   *
 *            specific prior written permission.                                    *
 *                                                                                  *
 *      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS         *
 *      “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT           *
 *      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS           *
 *      FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE              *
 *      COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,         *
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,        *
 *      BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;            *
 *      LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER            *
 *      CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT          *
 *      LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY       *
 *      WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY     *
 *      OF SUCH DAMAGE.                                                             *
 *                                                                                  *
 *      * PEQUOD-C utilises the SDL framework                                       *
 *        ( https://www.libsdl.org )                                                *
 *                                                                                  *
 *      * PEQUOD-C contact:                                                         *
 *          <peqclib@gmail.com>                                                     *
 *         ( https://github.com/spannaexmachina/pequad-c )                          *
 *                                                                                  *
 ************************************************************************************/



#ifndef PEQ_engine_h
#define PEQ_engine_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string.h>
#include "PEQ_colour.h"
#include "PEQ_geometry.h"
#include "PEQ_object.h"
#include "PEQ_utility.h"
#include "PEQ_text.h"

//dirs
#define dir_images assets/images/


/* ---Frame rate settings----
 don't mess with these unless
 you know what you're doing */

#define FPS_DEF            60
#define DELAY_TIME_DEF     1000.0f / FPS_DEF

//  //  //  //  //  //  //  //  //  //  //

//init window settings
#define WINDOW_X           100
#define WINDOW_Y           100
#define WINDOW_WIDTH       640
#define WINDOW_HEIGHT      480
#define WINDOW_TITLE       "Pequod-C"
#define BACKGROUND_COLOUR  BLACK
#define WINDOW_MODE        /* FULLSCREEN */ /* WINDOW */  RESIZABLE

//macros
#define PEQ_delay(int) (SDL_Delay((int)))
#define PEQ_boot_if if(m_data.is_loaded == FALSE){m_data.window_d.is_running = PEQ_init();}


/**
 * @brief mask for window modes
 *
 * mostly used for passing into low level SDL window functions
 */

typedef enum window {
    WINDOW,                     /**< Open in a fixed size window  */
   RESIZABLE,                  /**< Open in a resizable window */
  FULLSCREEN                  /**< Open in fullscreen */
} PEQ_WINDOW_MODE;



/**
 * @brief main data struct for PEQUAD-C
 *
 * This struct contains all the information PEQUOD needs to run. It
 * prvides a convinient way to pass data around the program.
 *
 * However, custom data does not have to be added here, but can be
 * used as usual from within new functions.
 * @code
 * int PEQ_render(PEQ_DATA *data)
 * {
 * ...
 * PEQ_draw_shape(data->renderer, &data->object_bank[i].graphic.shape);
 * ...
 * }
 * @endcode
 * @warning Changing the default data struct can have unforseen consiquences!
 * new fields for cusotmisation should be added at the end and separated from
 * core data.
 *
 */
typedef struct data {
    
    pbool is_loaded;
    SDL_Renderer *renderer;     /**< pointer to application renderer */
    
    
    
    struct {
        
        SDL_Window *window;             /**< pointer to application window */
        PEQ_COLOUR colour;            /**< background render colour (set in precompiler) */
        int window_mode;            /**< window mode (set at precompile) */
        char title[20];                 /**< application title, used for window title, etc. */
        pbool is_running;               /**< is the application running; 0 false */
        int x,                          /**< application window x coordinate (set in precompile) */
            y,
            height,                     /**< application window height (set in precompile) */
            width;                     /**< application window width (set in precompile) */
    } window_d;                         /**< application window y coordinate (set in precompile) */
    
    struct {
        
        Uint32 frame_start,                 /**< used to track starting frame rate */
               frame_time;
        int     FPS,                        /**< application frames per second (set in precompile) */
                delay_time;                 /**< application delay time (set in precompile) */
    } frame_rate;                                   /**< used to track frame rate speed after loop */
    
    
} PEQ_DATA;



 typedef struct {
     
    char  img_name[50];
    char filename[255];
    SDL_RendererFlip flip_flag;
     point2D position;
     int width,
        height;
     
    struct {
        
        int src_width,
            src_height;
        SDL_Texture *texture;
    } PEQ_TEXTURE;
     
} PEQ_IMAGE;

//images
PEQ_IMAGE PEQ_load_image(char *image_name, char *filename);
void PEQ_draw_image(PEQ_IMAGE *image);

//shapes
void PEQ_draw_line(PEQ_LINE *line);
void PEQ_draw_rect(PEQ_RECT *rect);
void PEQ_draw_circle(PEQ_CIRCLE *circ);
void PEQ_draw_point(PEQ_POINT *point);



//core
void PEQ_boot();
pbool PEQ_exit_request();

static void PEQ_checkset_render_size();
void PEQ_clear_render();
void PEQ_draw_render();

void PEQ_frame_start();
void PEQ_frame_end();


//getters
int PEQ_get_window_height();
int PEQ_get_window_width();
int PEQ_get_window_x();
int PEQ_get_window_y();
char *PEQ_get_title();


/**
 * @brief primary engine loop for handling events
 *
 * Any input handing should be put here
 * @warning PEQ CORE FUNCTION
 * @return 0 success
 */
pbool PEQ_handle_events();


/**
 * @brief destroys application
* @warning PEQ CORE FUNCTION
 * @return 0 success; -1 fail
 */
static pbool PEQ_clean();


#endif /* PEQ_engine_h */
