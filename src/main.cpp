#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include "common.h"
#include "nes.h"

int main(int argc, char* argv[])
{
	//NES setup
	NES* nes = new NES;
	char* rom = argv[1];
	nes->Reset(rom);

	// SDL setup
	SDL_Window* window = SDL_CreateWindow("tikiNES", 800, 600, 0);
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete nes;
	return 0;
}