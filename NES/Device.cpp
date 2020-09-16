#include "Device.h"
template<int startIdx, int endIdx>
inline const bool Device<startIdx, endIdx>::willRead(const ptr address)
{
	return address >= startIdx && address <= endIdx;
}
