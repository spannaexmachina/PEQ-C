//
//  PEQ_texture_manager.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_texture_manager.h"

PEQ_TEXTURE PEQ_get_texture(char filename[], char ID[], SDL_Renderer *r)
{
    SDL_Surface *tempsurface;
    SDL_Texture *temptexture;
    PEQ_TEXTURE temp;
    
    if ((tempsurface = IMG_Load(filename)) != 0) {
        printf("entered IMG_LOAD\n");
        temptexture = SDL_CreateTextureFromSurface(r, tempsurface);
        printf("created texture\n");
        SDL_FreeSurface(tempsurface);
        printf("freed surface\n");
        if (temptexture != 0) {
            printf("entered copy loop\n");
            strcpy(temp.filename, filename);
            strcpy(temp.textureID, ID);
            temp.texture = temptexture;
            printf("storing %s, %s", temp.filename, temp.textureID);
        }
    }
    return temp;
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



