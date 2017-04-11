

/**
 * \file PEQ_geometry.h
 *
 * \author Michael Holmes
 * \author Ruxandra Maritiu
 *
 * \brief header file for PEQ geomemety
 *
 * \date 2017
 *
 * \version 1.0
 *
 */
//n
#ifndef PEQ_geometry_h
#define PEQ_geometry_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "PEQ_colour.h"
#include <math.h>


/**
 * \brief structure representing a 2D point.
 */
typedef struct {
    int x;                  /**< x coordinate for a point2D */
    int y;                  /**< y coordinate for a point2D */
} point2D;

typedef struct {
    float x;
    float y;
} radius;

typedef struct {
    point2D p;
    radius r;
} circle;



typedef struct {
    PEQ_COLOUR     colour;
    point2D         p;
    int             width,
                    height;
} PEQ_RECT;

typedef struct line {
    PEQ_COLOUR    colour;
    point2D         p1,
                    p2;
} PEQ_LINE;

typedef struct point {
    PEQ_COLOUR     colour;
    point2D         p;
} PEQ_POINT;

typedef struct circle {
    PEQ_COLOUR colour;
    point2D center;
    float rad;
} PEQ_CIRCLE;


PEQ_RECT PEQ_load_rect(point2D p, int width, int height, COLOUR_NAME c);
PEQ_LINE PEQ_load_line(point2D p1, point2D p2, COLOUR_NAME c);
PEQ_POINT PEQ_load_point(point2D p, COLOUR_NAME c);
PEQ_CIRCLE PEQ_load_circle(point2D center, float rad, COLOUR_NAME c);

//circle
circle makecircle(point2D pt, radius r);
point2D ClosestPoint(point2D FromPoint, radius r);

//radius
radius makeradius(float r1, float r2);

//point2D
/**
 * \brief Adds two points and returns a point2D
 * \param p1 point2D 1
 * \param p2 point2D 2
 * \returns a resulting Point2D
 */
point2D result_add_points(point2D p1, point2D p2);

/**
 * \brief adds source Point2D to a destination Point2D pointer
 * \par The src point will be added to the destiation point pointer
 * \param dest pointer to the destination Point2D
 * \param src source point2D
 */
void addpoints(point2D *dest, point2D src);

/**
 * \brief subtracts source Point2D from a destination Point2D pointer
 * \par The src point will be subtracted from the destiation point pointer
 * \param dest pointer to the destination Point2D
 * \param src source point2D
 */
void subtractpoints(point2D *dest, point2D src);

/**
 * \brief generates a Point2D
 * \param x x coordinate
 * \param y y coordinate
 * \returns a point2D with passed in x and y coordinates
 */
point2D makepoint(int x, int y);



/**
 *\generated SDL Point for circles
 * \param x x coordinate
 * \param y y coordinate
 * \returns an SDL point with passed in x and y coordinates
 */

SDL_Point makeSDLpoint(int x, int y);



#endif /* PEQ_geometry_h */
