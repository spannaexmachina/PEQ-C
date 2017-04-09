

#ifndef PEQ_utility_h
#define PEQ_utility_h

#include <stdio.h>
#include <stdlib.h>
#include "PEQ_colour.h"

typedef enum boolean
{
    FALSE,
    TRUE
} boolean;

//random int generator
int PEQ_rand(int min, int max);


/**
 * \brief returns a random PEQ colour
 * \note *****SPECIAL****** pass in zero for random transparency!!!!
 * \param alpha pass an int between 1 and 255 for transparency setting
 * \returns random PEQ colour or defaults BLACK if error
 */
PEQ_COLOUR PEQ_rand_colour(int alpha);

#endif /* PEQ_utility_h */
