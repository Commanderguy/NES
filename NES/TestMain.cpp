#include <iostream>
#include "Bus.h"
#include "Core6502.h"
#include "DisAssemble.h"
#include <fstream>

int main()
{
	iNesFile smb("cpu.nes");
	std::cout << smb.HEADER.header.ToString();
	std::cin.get();
}