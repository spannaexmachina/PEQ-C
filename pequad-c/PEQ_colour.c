//
//  PEQ_colour.c
//  pequad-c
//
//  Created by Michael Holmes on 5/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include <stdio.h>
#include "PEQ_colour.h"
#include "PEQ_utility.h"

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
        case BLACK:       name = BLACK; t.r = t.g = t.b = 0; t.a = 255;       break;
        case WHITE:       name = WHITE; t.r = t.g = t.b = t.a = 255;          break;
        case RED:         name = RED; t.r = t.a = 255; t.g = t.b = 0;       break;
        case BLUE:        name = BLUE; t.r = t.g = 0; t.b = t.a = 255;       break;
        case GREEN:       name = GREEN; t.a = t.g =  255; t.b = t.r = 0;      break;
        case TRANSPARENT: name = TRANSPARENT; t.r = t.g = t.b = t.a = 0;            break;
        case RANDOM:      return PEQ_rand_colour(255);          break;
        default: break;
    }
    return t;
}
