#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "combat.h"

void	attack(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, SDL_Rect *player, SDL_Window *window)
{
	player->x += 20;
	player->y = (600 - player->h) / 1.3;
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderCopy(renderer, player_img, NULL, player);
	SDL_RenderPresent(renderer);

	shoot(renderer, background, player_img, player, window);

	player->x -= 20;
	player->y = (600 - player->h) / 1.3;
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
	SDL_Texture *texture_bullet = SDL_CreateTextureFromSurface(renderer, surface_bullet);
	SDL_FreeSurface(surface_bullet);
	SDL_Rect bullet;
	SDL_QueryTexture(texture_bullet, NULL, NULL, &bullet.w, &bullet.h);
	bullet.x = player->x + bullet.w;  
	bullet.y = player->y + bullet.h;
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
	return;
}