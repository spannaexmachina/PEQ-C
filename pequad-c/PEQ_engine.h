

#ifndef PEQ_engine_h
#define PEQ_engine_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "PEQ_texture_manager.h"
#include "PEQ_colour.h"
#include "PEQ_geometry.h"
#include "PEQ_object.h"
#include "PEQ_utility.h"
#include "PEQ_text.h"

//window settings
#define WINDOW_X           100
#define WINDOW_Y           100
#define WINDOW_WIDTH       640
#define WINDOW_HEIGHT      480
#define WINDOW_TITLE       "Pequod-C"
#define BACKGROUND_COLOUR  BLACK
#define WINDOW_MODE        WINDOW
#define FPS_DEF            60
#define DELAY_TIME_DEF     1000.0f / FPS_DEF
#define MAX_TEXTURE        100


#define CHECK_INIT if(m_data.is_loaded == FALSE){m_data.window_d.is_running = PEQ_init();}

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
    
    qbool is_loaded;
    SDL_Renderer *renderer;     /**< pointer to application renderer */
    
    
    
    struct {
        SDL_Window *window;             /**< pointer to application window */
        PEQ_COLOUR colour;            /**< background render colour (set in precompiler) */
        int window_mode;            /**< window mode (set at precompile) */
        char title[20];                 /**< application title, used for window title, etc. */
        qbool is_running;               /**< is the application running; 0 false */
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
    
    PEQ_OBJECT object_bank[10]; /*FIXME: phase out*/
    
} PEQ_DATA;

qbool PEQ_exit_request();

/**
 * @brief returns an SDL window mode based on PEQ enum
 *
 * avaliabe window option are WINDOW; RESIZABLE; FULLSCREEN;
 * @warning PEQ CORE FUNCTION
 * @param w_mode PEQ enum window mode
 * @return SDL window flag
 */
//int get_window_mode(PEQ_WINDOW_MODE w_mode);

/**
 * @brief Primary initialising function
 *
 * initialises SDL; window; and renderer
 * @warning PEQ CORE FUNCTION
 * @return 1 pass, 0 fail
 */
qbool PEQ_init();

void PEQ_clear_render();
void PEQ_draw_render();

/**
 * @brief primary engine loop for handling events
 *
 * Any input handing should be put here
 * @warning PEQ CORE FUNCTION
 * @return 0 success
 */
qbool PEQ_handle_events();

/**
 * @brief primary engine loop for rendering
 * any rendering tasks should be put here.
 * @warning PEQ CORE FUNCTION
 * @return 0 success
 */
qbool PEQ_render();

/**
 * @brief destroys application
* @warning PEQ CORE FUNCTION
 * @return 0 success; -1 fail
 */
qbool PEQ_clean();


/**
 * @brief main update loop
 *
 * all object updates should be here.
 * @warning PEQ CORE FUNCTION
 * @return 0 success
 */
qbool PEQ_update();

/**
 * @brief populates a PEQ_DATA struct
 * @warning PEQ CORE FUNCTION
 * @return 0 success;
 */
qbool pop_main_data();

/**
 * @brief loads objects into PEQ_data
 
 * @warning PEQ CORE FUNCTION
 */
qbool load_objects();




#endif /* PEQ_engine_h */
