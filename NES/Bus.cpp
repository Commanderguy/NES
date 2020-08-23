#include "Bus.h"
template<long addressSpace>
inline u8& Bus<addressSpace>::Read(ptr Address)
{
	return addresses[Address];
}

template<long addressSpace>
void Bus<addressSpace>::Write(ptr Address, u8 value)
{
	if (Address > addressSpace)
		return;
	addresses[Address] = value;
}

template<long addressSpace>
Bus<addressSpace>::Bus()
{
	CPU = Core6502(this);
}
