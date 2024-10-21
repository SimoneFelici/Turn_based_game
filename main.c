#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

int	main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return (1);
	}
	SDL_Window *window = SDL_CreateWindow("turnbased",
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									800, 600, 0);
	if (!window)
	{
		printf("Error creating the window: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	Uint32	render_flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Renderer *renderer = SDL_CreateRenderer(window,
									-1, render_flags);
	if (!renderer)
	{
		printf("Error creating the renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	SDL_Surface *surface = IMG_Load("resources/background.png");
	if (!surface)
	{
		printf("Error creating surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!background)
	{
		printf("Error creating the texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	surface = IMG_Load("resources/cat.png");
	if (!surface)
	{
		printf("Error creating surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	SDL_Texture *player_img = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!player_img)
	{
		printf("Error creating the texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,
					background,
					NULL,
					NULL);
	SDL_Rect player;
	player.x = 0;
	SDL_QueryTexture(player_img, NULL, NULL, &player.w, &player.h);
	player.y = (600 - player.h) / 1.5;
	SDL_RenderCopy(renderer, player_img, NULL, &player);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}