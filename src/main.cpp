#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include "common.h"
#include "nes.h"

int main(int argc, char* argv[])
{
	// SDL setup
	SDL_Window* window = SDL_CreateWindow("tikiNES", 800, 600, 0);
	SDL_DestroyWindow(window);
	SDL_Quit();

	//NES setup
	NES* nes = new NES;
	nes->Start();

	delete nes;
	return 0;
}