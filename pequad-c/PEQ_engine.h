

#ifndef PEQ_engine_h
#define PEQ_engine_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "PEQ_texture_manager.h"
#include "PEQ_colour.h"
#include "PEQ_SETTINGS.h"
#include "PEQ_geometry.h"
#include "PEQ_object.h"
#include "PEQ_utility.h"


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
    
    //PEQ default fields
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
    PEQ_OBJECT object_bank[10]; /**< stores objects */
    //end PEQ default fields
    
    /* add custom fields here */
    
} PEQ_DATA;



/**
 * @brief returns an SDL window mode based on PEQ enum
 *
 * avaliabe window option are WINDOW; RESIZABLE; FULLSCREEN;
 * @warning PEQ CORE FUNCTION
 * @param w_mode PEQ enum window mode
 * @return SDL window flag
 */
int get_window_mode(PEQ_WINDOW_MODE w_mode);

/**
 * @brief Primary initialising function
 *
 * initialises SDL; window; and renderer
 * @warning PEQ CORE FUNCTION
 * @param data PEQ_DATA type pointer
 * @return 1 pass, 0 fail
 */
int PEQ_init(PEQ_DATA *data);

/**
 * @brief primary engine loop for handling events
 *
 * Any input handing should be put here
 * @param data PEQ_DATA type pointer
 * @warning PEQ CORE FUNCTION
 * @return 0 success
 */
int PEQ_handle_events(PEQ_DATA *data);

/**
 * @brief primary engine loop for rendering
 * any rendering tasks should be put here.
 * @warning PEQ CORE FUNCTION
 * @param data PEQ_DATA type pointer
 * @return 0 success
 */
int PEQ_render(PEQ_DATA *data);

/**
 * @brief destroys application
 * @param data PEQ_DATA type pointer
* @warning PEQ CORE FUNCTION
 * @return 0 success; -1 fail
 */
int PEQ_clean(PEQ_DATA *data);

/**
 * @brief primary control loop
 * @par handles framerate control and application loop.
 * any tasks added here will run each frame.
 * @note primary used to call other looped functions such as
 * render, update, etc.
 * @warning PEQ CORE FUNCTION
 * @param data PEQ_DATA type pointer
 * @return 0 success; -1 fail
 */
int PEQ_cycle(PEQ_DATA *data);

/**
 * @brief main update loop
 *
 * all object updates should be here.
 * @warning PEQ CORE FUNCTION
 * @param data PEQ_DATA type pointer
 * @return 0 success
 */
int PEQ_update(PEQ_DATA *data);

/**
 * @brief populates a PEQ_DATA struct
 * @param data PEQ_DATA type pointer to populate
 * @warning PEQ CORE FUNCTION
 * @return 0 success;
 */
int pop_main_data(PEQ_DATA *data);

/**
 * @brief loads objects into PEQ_data
 
 * @param data PEQ_DATA type pointer to populate
 * @warning PEQ CORE FUNCTION
 */
void load_objects(PEQ_DATA *data);




#endif /* PEQ_engine_h */
