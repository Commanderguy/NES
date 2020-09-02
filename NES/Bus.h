#pragma once
#include "Types.h"
class Bus
{
public:
	u8 PLACEHOLDERRAM[0xFFFF];
	u8 Read(ptr loc);
	void Write(ptr loc, u8 data);

	Bus();
private:

protected:

};

