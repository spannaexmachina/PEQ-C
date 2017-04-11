

/**
 * @file PEQ_colour.h
 * @author Michael Holmes
 * @date April 2017
 * @version 1
 *
 * @brief file containing colour information and functions for the 
 * PEQUOD-C engine.
 * @see peqclib@gmail.com
 */
//n
#ifndef PEQ_colour_h
#define PEQ_colour_h

#include <stdio.h>

/**
 * @brief colour masks for specific PEQ functions
 *
 * masks for RGBA colours.
 * @note to be used with get_colour(COLOUR_NAME) to return a RBGA colourspace
 * @code
 * PEQ_2D_shape shape = PEQ_get_line(point_1, point_2, WHITE);
 * @endcode
 * @code
 * t.line.colour = get_colour(WHITE);
 * @endcode
 * @warning If a new colours are added to the get_colour() function then a mask should
 * also be added to this enum for best use throughout the engine.
 */
typedef enum {
    BLACK,
    WHITE,
    RED,
    BLUE,
    GREEN,
    TRANSPARENT,
    RANDOM
} COLOUR_NAME;

/**
 * @brief RGBA colourspace struct
 *
 * stores information for an RBGA colourspace including a COLOUR_NAME enum for use with 
 * various PEQ functions.
 * @code
 * PEQ_COLOUR t = get_colour(BLACK);
 * t.r = 50;
 * printf("colour red chromacity: %u", t.r);
 * @endcode
 *
 */
typedef struct {
    COLOUR_NAME name;       /**< colour enum */
    uint8_t r,              /**< red chromaticity */
            g,              /**< green chromaticity */
            b,              /**< blue chromaticity */
            a;              /**< alpha channel */
} PEQ_COLOUR;               

/**
 * \brief loads a PEQ_COLOUR struct from a COLOUR_NAME
 *
 * Use this function to load a PEQ_COLOUR type using a pointer.
 * function will use the passed in COLOUR_NAME paramenter to
 * load colour values.
 *
 * @code
 * PEQ_COLOUR colour;
 * load_in_colour(&colour, RANDOM);
 * @endcode
 *
 * @param c pointer to PEQ_COLOUR.
 * @param name COLOUR_NAME mask
 * @return 0 when completed.
 */
int load_in_colour(PEQ_COLOUR *c, COLOUR_NAME name);

/**
 * \brief creates a loaded PEQ_COLOUR struct from a COLOUR_NAME
 *
 * This function loads a PEQ_COLOUR and returns it
 *
 * @code
 * PEQ_COLOUR t = get_colour(RANDOM);
 * @endcode
 *
 * @param name COLOUR_NAME mask
 * @return a loaded PEQ_COLOUR
 * @note add new colours to this function for use with masks. don't forget to update
 * the COLOUR_NAME enum as well!
 */
PEQ_COLOUR get_colour(COLOUR_NAME name);

#endif /* PEQ_colour_h */
