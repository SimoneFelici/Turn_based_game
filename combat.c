#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "combat.h"

void attack(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, SDL_Rect *player, SDL_Window *window)
{
    int window_width1, window_height1;
    SDL_GetWindowSize(window, &window_width1, &window_height1);

    player->x += 20;
    player->y = (window_height1 - player->h) / 1.3;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderPresent(renderer);

    shoot(renderer, background, player_img, player, window);

    player->x -= 20;
    player->y = (window_height1 - player->h) / 1.3;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, player_img, NULL, player);
    SDL_RenderPresent(renderer);
}

void	shoot(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, SDL_Rect *player, SDL_Window *window)
{
	int window_width, window_height;
	SDL_GetWindowSize(window, &window_width, &window_height);

	SDL_Surface *surface_bullet = IMG_Load("resources/fire.png");
	if (!surface_bullet) {
        return;
    }
	SDL_Texture *texture_bullet = SDL_CreateTextureFromSurface(renderer, surface_bullet);
	SDL_FreeSurface(surface_bullet);
	if (!texture_bullet) {
        return;
    }
	SDL_Rect bullet;
	SDL_QueryTexture(texture_bullet, NULL, NULL, &bullet.w, &bullet.h);
	bullet.x = player->x + bullet.w;  
	bullet.y = player->y + (player->h / 2) - (bullet.h / 2);
	while(bullet.x < (window_width - bullet.w))
	{
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, player_img, NULL, player);
		SDL_RenderCopy(renderer, texture_bullet, NULL, &bullet);
		SDL_RenderPresent(renderer);
		bullet.x += 12;
		SDL_Delay(16);
	}
    SDL_DestroyTexture(texture_bullet);
}