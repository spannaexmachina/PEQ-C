//
//  PEQ_texture_manager.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_texture_manager.h"

//PEQ_TEXTURE PEQ_get_texture(char filename[], char ID[], SDL_Renderer *r)
int PEQ_load_texture(SDL_Renderer *r, PEQ_TEXTURE *t)
{
    SDL_Surface *tempsurface;
    //SDL_Texture *temptexture;
    //PEQ_TEXTURE temp;
    
        tempsurface = IMG_Load(t->filename);
        printf("entered IMG_LOAD\n");
        t->texture = SDL_CreateTextureFromSurface(r, tempsurface);
        printf("created texture\n");
        SDL_FreeSurface(tempsurface);
        printf("freed surface\n");
        if (t->texture != 0) {
            printf("%s (%s) loaded!\n", t->textureID, t->filename);
            return 0;
        } else
            printf("skipped: %s\n", SDL_GetError());
    return -1;
}

void PEQ_draw(SDL_Texture *texture, int x, int y, int width, int height, SDL_Renderer *r, SDL_RendererFlip flip_flag)
{
    SDL_Rect src_r, dest_r;
    
    src_r.x = src_r.y = 0;
    src_r.w = dest_r.w = width;
    src_r.h = dest_r.h = height;
    dest_r.x = x;
    dest_r.y = y;
    
    SDL_RenderCopyEx(r, texture, &src_r, &dest_r, 0, 0, flip_flag);
}

//todo drawframe



