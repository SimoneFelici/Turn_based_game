#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void	attack(SDL_Renderer *renderer, SDL_Texture *background, SDL_Texture *player_img, SDL_Rect *player)
{
	player->x = 70;
	player->y = (600 - player->h) / 1.3;
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderCopy(renderer, player_img, NULL, player);
	SDL_RenderPresent(renderer);

	SDL_Delay(100);

	player->x = 50;
	player->y = (600 - player->h) / 1.3;
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderCopy(renderer, player_img, NULL, player);
	SDL_RenderPresent(renderer);
}