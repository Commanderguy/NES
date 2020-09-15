#include "iNesFile.h"

iNesFile::iNesFile(const char* filename)
{
	std::ifstream file;
	file.open(filename, std::ifstream::binary);
	if (file.is_open())
	{
		// This is the only important line yet.
		file.read(HEADER._data, 16);
	}
}

std::string header_s::_header::ToString()
{
	std::string s;
	s += "Header: ";
	s += nesHeader[0];
	s += nesHeader[1];
	s += nesHeader[2];
	s += nesHeader[3];
	s += "\nPRG-Rom size: ";
	s += std::to_string((int)PRG_s);
	s += "\nCHR-RomSize: ";
	s += std::to_string((int)CHR_s);
	s += "\nHas trainer: ";
	s += (f6.Trainer.Get() ? "true" : "false");
	s += "\nBinary: ";

	return s;
}
