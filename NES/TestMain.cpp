#include <iostream>
#include "Bus.h"
#include "Core6502.h"
#include "DisAssemble.h"
#include <fstream>

int main()
{
	{
		iNesFile smb("C:/Users/johan/source/repos/NES/x64/Debug/roms/Super Mario Bros.nes");
		std::cout << smb.HEADER.header.ToString();
		std::cin.get();
	}
	std::cin.get();
}