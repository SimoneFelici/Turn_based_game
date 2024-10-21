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
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	Uint32	render_flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Renderer *renderer = SDL_CreateRenderer(window,
									-1, render_flags);
	if (!renderer)
	{
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	SDL_Surface *background = IMG_Load("resources/background.png");
	if (!background)
	{
		printf("Error creating texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface(background);
	if (!texture)
	{
		printf("Error creating texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,
					texture,
					NULL,
					NULL);
	SDL_RenderPresent(renderer);

	SDL_Delay(3000);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}