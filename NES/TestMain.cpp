#include <iostream>
#include "Bus.h"
#include "Core6502.h"
#include "DisAssemble.h"
#include <fstream>

int main()
{
	void* ptr;
	{
		iNesFile smb("C:/Users/johan/source/repos/NES/x64/Debug/roms/Super Mario Bros.nes");
		ptr = smb.PRG_ROM;
		std::cout << smb.HEADER.header.ToString();
		std::cin.get();
	}
	std::cin.get();
}