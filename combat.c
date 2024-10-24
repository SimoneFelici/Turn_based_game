#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "combat.h"

void attack(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, 
            SDL_Rect *player, SDL_Texture *enemy_img, SDL_Rect *enemy, SDL_Window *window)
{
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    player->x += 20;
    player->y = (window_height - player->h) / 1.3;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderPresent(renderer);
    shoot(renderer, background, player_img, player, enemy_img, enemy, window);
    player->x -= 20;
    player->y = (window_height - player->h) / 1.3;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderPresent(renderer);
}

void shoot(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, 
           SDL_Rect *player, SDL_Texture *enemy_img, SDL_Rect *enemy, SDL_Window *window)
{
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_Surface *surface_bullet = IMG_Load("resources/fire.png");
    if (!surface_bullet)
    {
        return ;
    }
    SDL_Texture *texture_bullet = SDL_CreateTextureFromSurface(renderer, surface_bullet);
    SDL_FreeSurface(surface_bullet);
    if (!texture_bullet)
    {
        return ;
    }
    SDL_Rect bullet;
    SDL_QueryTexture(texture_bullet, NULL, NULL, &bullet.w, &bullet.h);
    bullet.x = player->x + bullet.w;
    bullet.y = player->y + (player->h / 2) - (bullet.h / 2);
    while ((bullet.x + bullet.w) < enemy->x)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, player_img, NULL, player);
        SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
        SDL_RenderCopy(renderer, texture_bullet, NULL, &bullet);
        SDL_RenderPresent(renderer);
        bullet.x += 12;
        SDL_Delay(16);
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderPresent(renderer);
    SDL_SetTextureColorMod(enemy_img, 255, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderPresent(renderer);
    SDL_Delay(200);
    SDL_SetTextureColorMod(enemy_img, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture_bullet);
}

void enemy_attack(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *enemy_img, 
                  SDL_Rect *enemy, SDL_Texture *player_img, SDL_Rect *player, SDL_Window *window)
{
    int window_width1, window_height1;
    SDL_GetWindowSize(window, &window_width1, &window_height1);
    enemy->x -= 20;
    enemy->y = (window_height1 - enemy->h) / 1.3;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderPresent(renderer);
    enemy_shoot(renderer, background, enemy_img, enemy, player_img, player, window);    
    enemy->x += 20;
    enemy->y = (window_height1 - enemy->h) / 1.3;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderPresent(renderer);
}

void enemy_shoot(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *enemy_img, 
                 SDL_Rect *enemy, SDL_Texture *player_img, SDL_Rect *player, SDL_Window *window)
{
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_Surface *surface_bullet = IMG_Load("resources/enemy_fire.png");
    if (!surface_bullet)
    {
        return ;
    }
    SDL_Texture *texture_bullet = SDL_CreateTextureFromSurface(renderer, surface_bullet);
    SDL_FreeSurface(surface_bullet);
    if (!texture_bullet)
    {
        return ;
    }
    SDL_Rect bullet;
    SDL_QueryTexture(texture_bullet, NULL, NULL, &bullet.w, &bullet.h);
    bullet.x = enemy->x - bullet.w;
    bullet.y = enemy->y + (enemy->h / 2) - (bullet.h / 2);
    while (bullet.x > (player->x + player->w))
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
        SDL_RenderCopy(renderer, player_img, NULL, player);
        SDL_RenderCopy(renderer, texture_bullet, NULL, &bullet);
        SDL_RenderPresent(renderer);
        bullet.x -= 12;
        SDL_Delay(16);
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderPresent(renderer);
    SDL_SetTextureColorMod(player_img, 255, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderPresent(renderer);
    SDL_Delay(200);
    SDL_SetTextureColorMod(player_img, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, enemy_img, NULL, enemy);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture_bullet);
}
