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
		

		Ram<0x00, 0xFF, 0xFF> test_ram;
		test_ram.Write(0x00, 15);

		void* ptr2 = test_ram._loc;
		
		std::cin.get();

	}
	std::cin.get();
}