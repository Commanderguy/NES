#include "iNesFile.h"

iNesFile::iNesFile(const char* filename)
{
	std::ifstream file;
	file.open(std::string(filename), std::ifstream::binary);

	if (file.is_open())
	{
		file.read(HEADER._data, 16);
		trainer = nullptr;
		if (HEADER.header.f6.Trainer.Get())
		{
			file.read((char*)trainer, 512);
		}

		u8 mapperId = HEADER.header.f7.getHiMapper.get() << 4 | HEADER.header.f6.getLoMapper.get();

		PRG_s = 16384	* HEADER.header.PRG_s;
		CHR_s = 8192	* HEADER.header.CHR_s;

		PRG_ROM = new u8[PRG_s];
		CHR_ROM = new u8[CHR_s];

		InstRom = nullptr;
		PROM	= nullptr;

		file.read((char*)PRG_ROM, PRG_s);
		file.read((char*)CHR_ROM, CHR_s);
	}
	else
	{
		std::cout << "Something went terribly wrong!!!" << std::endl;
		for(;;) {}
	}
	file.close();
}

iNesFile::~iNesFile()
{
	delete[] PRG_ROM;
	delete[] CHR_ROM;
	delete[] trainer;
	delete[] InstRom;
	delete[] PROM;
}

std::string header_s::_header::ToString()
{
	std::string s;
	s += "Header: ";
	s += nesHeader[0];
	s += nesHeader[1];
	s += nesHeader[2];
	s += "\nPRG-Rom size: ";
	s += std::to_string((int)PRG_s);
	s += "\nCHR-Rom size: ";
	s += std::to_string((int)CHR_s);
	s += "\nHas trainer: ";
	s += (f6.Trainer.Get() ? "true" : "false");
	s += "\nActual PRG-Rom size: ";
	s += std::to_string(16384 * PRG_s);
	s += "\nActual CHR-Rom size: ";
	s += std::to_string(8192 * CHR_s);

	return s;
}
