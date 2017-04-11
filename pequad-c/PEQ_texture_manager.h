//
//  PEQ_texture_manager.h
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#ifndef PEQ_texture_manager_h
#define PEQ_texture_manager_h

#define IMAGEDIR assets/images

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string.h>
#include "PEQ_SETTINGS.h"
#include "PEQ_geometry.h"

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
