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

typedef struct {
    char textureID[50];                 /**< unique ID for texure */
    char filename[255];                 /**< unique filename for texure */
    int  w,
         h;
    SDL_Texture *texture;
} PEQ_TEXTURE;


int PEQ_load_texture(SDL_Renderer *r, PEQ_TEXTURE *t);

//void PEQ_draw(SDL_Texture *texture, int x, int y, int width, int height, SDL_Renderer *r, SDL_RendererFlip flip_flag);

void PEQ_draw_texture(SDL_Renderer *r, PEQ_TEXTURE *t, int draw_x, int draw_y, int draw_width, int draw_height, SDL_RendererFlip flip_flag);


#endif /* PEQ_texture_manager_h */
