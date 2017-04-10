

#ifndef PEQ_utility_h
#define PEQ_utility_h

#include <stdio.h>
#include <stdlib.h>
#include "PEQ_colour.h"

//general calc macros
#define pmax(a, b)      ((a)>(b)?(a):(b))
#define pmin(a, b)      ((a)<(b)?(a):(b))
#define pabsdiff(a, b)  ((a)>(b)?(a)-(b):(b)-(a))

//paste two things together
#define ppaste(front, back) front ## back

//uber random
#define uberrand(min, max) (PEQ_rand(PEQ_rand((min),(max)),PEQ_rand((min),(max))))

typedef enum pbool {FALSE,TRUE} pbool;

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
