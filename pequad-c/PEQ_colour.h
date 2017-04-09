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
