//
//  PEQ_colour.c
//  pequad-c
//
//  Created by Michael Holmes on 5/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include <stdio.h>
#include "PEQ_colour.h"

int load_in_colour(PEQ_COLOUR *dest, COLOUR_NAME name)
{
    *dest = get_colour(name);
    return 0;
}

PEQ_COLOUR get_colour(COLOUR_NAME name)
{
    PEQ_COLOUR t;
    
    t.name = name;
    switch (t.name) {
        case BLACK: t.r = t.g = t.b = 0; t.a = 255; break;
        case WHITE: t.r = t.g = t.b = t.a = 255; break;
        case RED:   t.r = t.a = 255; t.g = t.b = 0; break;
        case TRANSPARENT: t.r = t.g = t.b = t.a = 0; break;
        default: break;
    }
    return t;
}
