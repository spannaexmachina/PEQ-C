//
//  PEQ_colour.h
//  pequad-c
//
//  Created by Michael Holmes on 5/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#ifndef PEQ_colour_h
#define PEQ_colour_h

#include <stdio.h>

/**
 * \brief colour enums
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
 * \brief RGBA colourspace struct
 */
typedef struct {
    COLOUR_NAME name;       /**< colour enum */
    uint8_t r,              /**< red chromaticity */
            g,              /**< green chromaticity */
            b,              /**< blue chromaticity */
            a;              /**< alpha channel */
} PEQ_COLOUR;               

int load_in_colour(PEQ_COLOUR *c, COLOUR_NAME name);

PEQ_COLOUR get_colour(COLOUR_NAME name);

#endif /* PEQ_colour_h */
