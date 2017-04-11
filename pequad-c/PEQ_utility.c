//
//  PEQ_utility.c
//  pequad-c
//
//  Created by Michael Holmes on 8/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//
//n
#include "PEQ_utility.h"



int PEQ_rand(int min, int max)
{
    if (min < max)
        return (rand() % (max - min)) + min;
    else
        return 0;
}

PEQ_COLOUR PEQ_rand_colour(int alpha)
{
    PEQ_COLOUR c;
    
    if (alpha < 0 || alpha > 255)
        return c = get_colour(BLACK);
    else if (alpha == 0)
        c.a = PEQ_rand(0, 255);
    else
        c.a = alpha;
    c.r = PEQ_rand(0, 255);
    c.g = PEQ_rand(0, 255);
    c.b = PEQ_rand(0, 255);
    c.name = RANDOM;
    return c;
}
