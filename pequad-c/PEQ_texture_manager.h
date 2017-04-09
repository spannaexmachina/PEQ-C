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


#ifndef PEQ_texture_manager_h
#define PEQ_texture_manager_h

#define IMAGEDIR assets/images

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string.h>
#include "PEQ_SETTINGS.h"
#include "PEQ_geometry.h"


/*!
 * @typedef PEQ_TEXTURE
 * @brief information for a texture type
 * @field textureID unique name for the texture
 *
 */
typedef struct {
    char textureID[50];                 /**< unique ID for texure */
    char filename[255];                 /**< unique filename for texure */
    int  w,
         h;
    point2D position;
    SDL_Texture *texture;
    SDL_RendererFlip flip_flag;
} PEQ_TEXTURE;


void PEQ_load_texture(SDL_Renderer *r, PEQ_TEXTURE *t);

PEQ_TEXTURE PEQ_get_texture(SDL_Renderer *r, char name[], char filename[], point2D p, SDL_RendererFlip flip_flag);


void PEQ_draw_texture(SDL_Renderer *r, PEQ_TEXTURE *t, int draw_x, int draw_y, int draw_width, int draw_height, SDL_RendererFlip flip_flag);


#endif /* PEQ_texture_manager_h */
