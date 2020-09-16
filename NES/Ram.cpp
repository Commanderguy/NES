#include "Ram.h"

template<int idxs, int idxe, int actualSize>
inline u8 Ram<idxs, idxe, actualSize>::Read(ptr loc)
{
	return _loc[loc & (actualSize - 1)] ;
}

template<int idxs, int idxe, int actualSize>
inline void Ram<idxs, idxe, actualSize>::Write(ptr loc, u8 data)
{
	_loc[loc & (actualSize - 1)] = data;
}
