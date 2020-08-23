#pragma once
#include "Bus.h"

class Core6502
{
public:
	Core6502(Bus<>* b);
	Core6502() {};
protected:

private:
	Bus<>* _bus;
};

