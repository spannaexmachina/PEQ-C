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

#ifndef PEQ_geometry_h
#define PEQ_geometry_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "PEQ_colour.h"
#include <math.h>

/**
 * flags for PEQ shapes
 */
typedef enum {
    PEQ_RECT,
    PEQ_LINE,
    PEQ_POINT,
    PEQ_CIRCLE
} PEQ_shape_type;

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

/**
 * \brief union for storing a type of 2D graphic
 *
 * \note avaliable shapes: rect; line; point; circle
 */
typedef union {
    struct rect {
        PEQ_shape_type  type;
        PEQ_COLOUR     colour;
        point2D         p;
        int             width,
                        height;
    } rect;
    struct line {
        PEQ_shape_type  type;
        PEQ_COLOUR    colour;
        point2D         p1,
                        p2;
    } line;
    struct point {
        PEQ_shape_type  type;
        PEQ_COLOUR     colour;
        point2D         p;
    } point;
    struct circle {
        PEQ_shape_type type;
        PEQ_COLOUR colour;
        SDL_Point center;
        float rad;
    }circle;
} PEQ_2D_shape;

//variable shape create
PEQ_2D_shape PEQ_get_rect(point2D p, int width, int height, COLOUR_NAME c);
PEQ_2D_shape PEQ_get_line(point2D p1, point2D p2, COLOUR_NAME c);
PEQ_2D_shape PEQ_get_point(point2D p, COLOUR_NAME c);
PEQ_2D_shape PEQ_get_circ(COLOUR_NAME c, SDL_Point center, float rad);

//var shape draw
void PEQ_draw_shape(SDL_Renderer *r, PEQ_2D_shape *shape);

//update variable shapes function
void scale_shape(PEQ_2D_shape s, float scaler);

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

//drawing
void PEQ_draw_line(SDL_Renderer *r, PEQ_COLOUR c, point2D p1, point2D p2);
void PEQ_draw_rect(SDL_Renderer *r, PEQ_COLOUR c, point2D p, int width, int height);
void PEQ_draw_circle(SDL_Renderer *r, PEQ_COLOUR c, SDL_Point center, float rad);
void PEQ_draw_point(SDL_Renderer *r, PEQ_COLOUR c, point2D p);



#endif /* PEQ_geometry_h */
