/**
 * Pequad-C
 * Copyright (C) all rights reserved
 *
 * authors:
 * \author Michael Holmes
 * \author Ruxandra Maritiu
 * 
 *
 * \file PEQ_geometry.h
 * \brief header file for PEQ geomemety
 *
 * \date 2017
 *
 * \version 1.0
 *
 */

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

//drawing
void PEQ_draw_line(SDL_Renderer *r, COLOUR_NAME colour, point2D p1, point2D p2);
void PEQ_draw_rect(SDL_Renderer *r, COLOUR_NAME colour, point2D p, int width, int height);

//void PEQ_draw_all_2D(SDL_Renderer *r, PEQ_2D_graphic *objects[]);


#endif /* PEQ_geometry_h */
