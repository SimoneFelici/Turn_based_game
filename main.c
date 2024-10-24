#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include "class.h"
#include "combat.h"

void	damage(t_class *c_player, t_class *c_enemy, int *level)
{
	c_enemy->health -= c_player->damage;
	if (c_enemy->health > 0)
	{
		c_player->health -= c_enemy->damage;
	}
	else
	{
		(*level)++;
	}
}
int	main()
{
	int	class_idx;
	t_class c_player = create_empty_class();

	while(c_player.health == 0)
	{
		printf("Choose your class:\n"
			"1) Cavaliere\n"
			"2) Mago\n");
		scanf("%d", &class_idx);
		c_player = choose_class(class_idx);
		if(c_player.health == 0)
		{
			printf("Not a valid class!\n");
		}
	}
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
	int window_width, window_height;
	SDL_GetWindowSize(window, &window_width, &window_height);

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
	surface = IMG_Load(c_player.sprite);
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
	SDL_Rect player;
	SDL_QueryTexture(player_img, NULL, NULL, &player.w, &player.h);
	player.x = 50;
	player.y = (window_height - player.h) / 1.3;
	int	level = 0;
	int	enemy_lvl = 0;
	int	close_window = 0;
	t_class c_enemy = create_enemy();
	while(!close_window)
	{
	    if (enemy_lvl != level)
	    {
	        c_enemy = create_enemy();
	        enemy_lvl = level;
	    }
	    if(c_player.health > 0)
	    {
	        SDL_Event event;
	        while (SDL_PollEvent(&event))
	        {
	            if (event.type == SDL_QUIT)
	            {
	                close_window = 1;
	            }
	            else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_A)
	            {
	                attack(renderer, background, player_img, &player, window);
	                damage(&c_player, &c_enemy, &level);
	            }
	        }
	        SDL_RenderClear(renderer);
	        SDL_RenderCopy(renderer, background, NULL, NULL);
	        SDL_RenderCopy(renderer, player_img, NULL, &player);
	        SDL_RenderPresent(renderer);
	        SDL_Delay(16);
	    }
		if(c_player.health <= 0)
		{
		    printf("Game over\n");
		    printf("You survived %d levels\n", level);
		    SDL_Delay(2000);
		    close_window = 1;
		}
	}
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}