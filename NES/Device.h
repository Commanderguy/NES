#pragma once
#include "Types.h"

template <int startIdx, int endIdx>
class Device
{
	inline const bool doRead(const ptr address);
	virtual u8 Read(ptr loc) = 0;
	virtual void Write(ptr loc, u8 data) = 0;
};
