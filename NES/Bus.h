#pragma once
#include "Types.h"
#include "Ram.h"


class Bus
{
public:
	u8 Read(ptr loc);
	void Write(ptr loc, u8 data);
	Bus();

	///////////////// Devices ///////////////////
	
	/// <summary>
	/// The ram handles reads and writes at position 0x0000 through 0x1FFF and has an actual size of 2kb. The other 6 kb are just mirrors of the ram
	/// </summary>
	Ram<0x0000, 0x1FFF, 2048> RAM;





private:

protected:

};

