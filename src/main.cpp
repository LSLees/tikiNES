#include <iostream>
#include <memory>

#include <random>

#include <SDL3/SDL.h>

#include "common.h"
#include "nes.h"

int main(int argc, char* argv[])
{
	//char* rom = argv[1];
	char* rom = "Super Mario Bros. (World).nes";

	//NES setup
	NES* nes = new NES;
	nes->Reset(rom);

	// SDL setup
	SDL_Window* window = SDL_CreateWindow("tikiNES", 1024, 960, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	
	bool running = true;

	while (running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	std::cout << std::endl << "Cleaning-" << std::endl;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete nes;
	return 0;
}