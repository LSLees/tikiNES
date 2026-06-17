#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include <iostream>
#include <fstream>

#include "../include/common.h"
#include "../include/nes.h"

int main(int argc, char* argv[])
{
	// SDL setup
	SDL_Window* window = SDL_CreateWindow("tikiNES", 800, 600, 0);
	SDL_DestroyWindow(window);
	SDL_Quit();

	// NES setup
	NES* nes = new NES;
	nes->cpu.Step();

	// Open .nes file
	std::ifstream file("../test/Super Mario Bros. (World).nes", std::ios::binary);

	// Reading first 8 bytes
	unsigned char bytes[8];
	file.read(reinterpret_cast<char*>(bytes), 8);

	// Print first 8 bytes
	for (int i = 0; i < 8; i++)
	{
		std::cout << std::hex << (int)bytes[i] << ' ';
	}

	delete nes;
	return 0;
}