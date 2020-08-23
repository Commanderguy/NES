#pragma once
#include "Types.h"
#include "Core6502.h"

template <long addressSpace = 0xffff>
class Bus
{
public:
	/// <summary>
	/// The address space for accessing and writing to memory
	/// </summary>
	u8 addresses[addressSpace];


	Core6502 CPU;


	/// <summary>
	/// Read the byte at the specified address.
	/// </summary>
	/// <param name="Address">The address to be read.</param>
	/// <returns>The value at the address as a reference.</returns>
	u8& Read(ptr Address);


	/// <summary>
	/// Write a 1 byte value to the specified adress.
	/// </summary>
	/// <param name="Address">The address to be written to</param>
	/// <param name="value">The byte to be written to the address</param>
	void Write(ptr Address, u8 value);


	Bus();
protected:

private:

};