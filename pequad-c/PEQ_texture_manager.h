

#ifndef PEQ_texture_manager_h
#define PEQ_texture_manager_h

#define IMAGEDIR assets/images

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string.h>
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


typedef struct {
    char img_name[50];
    char filename[255];
    point2D pos;
     int width,
        height;
    SDL_RendererFlip flip_flag;
} PEQ_image;

void PEQ_load_texture(SDL_Renderer *r, PEQ_TEXTURE *t);

PEQ_TEXTURE PEQ_get_texture(SDL_Renderer *r, char name[], char filename[], point2D p, SDL_RendererFlip flip_flag);


void PEQ_draw_texture(SDL_Renderer *r, PEQ_TEXTURE *t, int draw_x, int draw_y, int draw_width, int draw_height, SDL_RendererFlip flip_flag);


#endif /* PEQ_texture_manager_h */
