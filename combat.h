#ifndef COMBAT_H
#define COMBAT_H
#include <SDL2/SDL.h>
#include "class.h"

void attack(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, 
            SDL_Rect *player, SDL_Texture *enemy_img, SDL_Rect *enemy, SDL_Window *window);
void shoot(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, 
           SDL_Rect *player, SDL_Texture *enemy_img, SDL_Rect *enemy, SDL_Window *window);
void enemy_attack(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *enemy_img, 
                  SDL_Rect *enemy, SDL_Texture *player_img, SDL_Rect *player, SDL_Window *window);
void enemy_shoot(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *enemy_img, 
                 SDL_Rect *enemy, SDL_Texture *player_img, SDL_Rect *player, SDL_Window *window);


#endif
