#include <iostream>
#include <fstream>
#include "../include/common.h"
#include "../include/cpu.h"
#include "../include/mem.h"


int main(int argc, char* argv[])
{
	CPU* cpu = new CPU;
	WRAM* wram = new WRAM;
	cpu->displayReg();

	return 0;
}