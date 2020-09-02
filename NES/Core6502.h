#pragma once
#include "Bus.h"
#include "Types.h"
// This #define command defines the Template for opcodes and make the code more readable
// Every opcode definition consists of an function that executes and then returns the cycles it took.
#define OPCODE(x) u8 x();
#define MODE(x) void x();
// This declares a function pointer to a member of the cpu. It's just for better code readability
#define p(x) &Core6502:: ## x

/// <summary>
/// The bit class is used to set, clear get, and toggle a bit in a union.
/// </summary>
template <int bitPlace, typename unionType = u8>
class Bit
{
	unionType data;
public:
	bool Get() { return (data >> bitPlace) & 1; }
	void Set() { data |= 1 << bitPlace; }
	void Clear() { data &= ~(1 << bitPlace); }
	void Toggle() { data ^= 1 << bitPlace; }
};

class Bus;


/// <summary>
/// The flags of the 6502.
/// </summary>
union CPUFlags6502
{
	u8 data;
	Bit<0> C;
	Bit<1> Z;
	Bit<2> I;
	Bit<3> D;
	Bit<6> V;
	Bit<7> N;
};


union ToPtr
{
	ptr p;
	struct
	{
		u8 hi;
		u8 lo;
	};
};

class Core6502
{
public:
	/// <summary>
	/// The number of cycles the cpu currently has to work down. The next action is only taken,
	/// if the cycles count == 0.
	/// </summary>
	u8 cycles = 0;
	ptr ProgramCounter = 0xC000;
	ptr addressOperate = 0x0000;
	pptr StackPtr;
	u8 StatusReg = 0x00;
	Core6502(Bus* b, ptr ProgramCount);

	void Tick()
	{
		if (cycles == 0)
		{
			cycles = (this->*codes[ProgramCounter])();
		}
		cycles--;
	}

	u8 Reset();

	// Registers a, x and y
	u8 a; // The accumulator
	u8 x; // The X-Register
	u8 y; // The Y-Register

	// ------------------ Opcode Matrix ------------------------
	u8 (Core6502::*codes[256])() =
	{//			0		1		2		3		4		5		6		7		8		9		a		b		c		d		e		f
	/*	0	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	1	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	2	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	3	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	4	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	5	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	6	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	7	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	8	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	9	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	a	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	b	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	c	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	d	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	e	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(NOP), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX),
	/*	f	*/	p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX), p(XXX)
	};


	// Addressingmode matrix
	void(Core6502::* AddressingMode[256])() =
	{//			0		1		2		3		4		5		6		7		8		9		a		b		c		d		e		f
	/*	0	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	1	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	2	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	3	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	4	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	5	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	6	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	7	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	8	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	9	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	a	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	b	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	c	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	d	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	e	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP),
	/*	f	*/	p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP), p(IMP)
	};


protected:


private:
	Bus* _bus;
	// ---------------- Addressing Modes -----------------------
	
	MODE(IMP)
	MODE(IMM)
	MODE(AAM)
	MODE(_ZP)
	MODE(ABS)
	MODE(REL)
	MODE(IND)
	MODE(IDX)
	MODE(IDY)
	MODE(ZPX)
	MODE(ZPY)
	MODE(ABX)
	MODE(ABY)
	
	// --------------------- Opcodes ---------------------------

	/// <summary>
	/// The placeholder OPCODE. It will always throw an exception.
	/// </summary>
	/// <returns></returns>
	OPCODE(XXX)
	OPCODE(NOP)
};

#undef OPCODE
#undef MODE