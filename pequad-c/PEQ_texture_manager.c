//
//  PEQ_texture_manager.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_texture_manager.h"

//PEQ_TEXTURE PEQ_get_texture(char filename[], char ID[], SDL_Renderer *r)
void PEQ_load_texture(SDL_Renderer *r, PEQ_TEXTURE *t)
{
    SDL_Surface* tempsurface;
    
    if ((tempsurface = IMG_Load(t->filename))) {
        t->texture = SDL_CreateTextureFromSurface(r, tempsurface);
        if (t->texture != 0) {
            t->w = tempsurface->w;
            t->h = tempsurface->h;
            printf("%s (%s) loaded!\n", t->textureID, t->filename);
            SDL_FreeSurface(tempsurface);
            return;
        }
    }
    
    printf("skipped: %s. ERROR: %s\n", t->textureID, SDL_GetError());
    return;
}

void PEQ_draw_texture(SDL_Renderer *r, PEQ_TEXTURE *t, int draw_x, int draw_y, int draw_width, int draw_height, SDL_RendererFlip flip_flag)
{
    SDL_Rect src_r, dest_r;
    
    src_r.x = src_r.y = 0;  //always zero for full image render
    src_r.w = t->w;         //load preset width
    src_r.h = t->h;         //preset height
    dest_r.x = draw_x;
    dest_r.y = draw_y;
    dest_r.w = draw_width;
    dest_r.h = draw_height;
    SDL_RenderCopyEx(r, t->texture, &src_r, &dest_r, 0, 0, flip_flag);
    
}

//todo drawframe



