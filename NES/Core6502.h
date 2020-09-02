#pragma once
#include "Bus.h"
#include "Types.h"
// This #define command defines the Template for opcodes and make the code more readable
// Every opcode definition consists of an function that executes and then returns the cycles it took.
#define OPCODE(x) void x();
#define MODE(x) bool x();
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
	u8 curOp = 0;
	ptr ProgramCounter = 0xC000;
	ptr addressOperate = 0x0000;
	u8 adrContent;
	pptr StackPtr;
	CPUFlags6502 StatusReg;
	Core6502(Bus* b, ptr ProgramCount);

	void Tick()
	{
		if (cycles == 0)
		{
			curOp = _bus->Read(ProgramCounter);
			ProgramCounter++;
			(this->*codes[curOp])();
			(this->*AddressingMode[curOp])();
		}
		cycles--;
	}

	u8 Reset();

	// Registers a, x and y
	u8 a; // The accumulator
	u8 x; // The X-Register
	u8 y; // The Y-Register

	// ------------------ Opcode Matrix ------------------------
	void (Core6502::*codes[256])() =
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
	bool(Core6502::* AddressingMode[256])() =
	{//			0		1		2		3		4		5		6		7		8		9		a		b		c		d		e		f
	/*	0	*/	p(IMP), p(IDX), p(IMP), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(ABS), p(ABS), p(ABS), p(ABS),
	/*	1	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPX), p(ZPX), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABX), p(ABX),
	/*	2	*/	p(ABS), p(IDX), p(IMP), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(ABS), p(ABS), p(ABS), p(ABS),
	/*	3	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPX), p(ZPX), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABX), p(ABX),
	/*	4	*/	p(IMP), p(IDX), p(IMP), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(ABS), p(ABS), p(ABS), p(ABS),
	/*	5	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPX), p(ZPX), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABX), p(ABX),
	/*	6	*/	p(IMP), p(IDX), p(IMP), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(IND), p(ABS), p(ABS), p(ABS),
	/*	7	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPX), p(ZPX), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABX), p(ABX),
	/*	8	*/	p(IMM), p(IDX), p(IMM), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(ABS), p(ABS), p(ABS), p(ABS),
	/*	9	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPY), p(ZPY), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABY), p(ABY),
	/*	a	*/	p(IMM), p(IDX), p(IMM), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(ABS), p(ABS), p(ABS), p(ABS),
	/*	b	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPY), p(ZPY), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABY), p(ABY),
	/*	c	*/	p(IMM), p(IDX), p(IMM), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(ABS), p(ABS), p(ABS), p(ABS),
	/*	d	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPX), p(ZPX), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABX), p(ABX),
	/*	e	*/	p(IMM), p(IDX), p(IMM), p(IDX), p(_ZP), p(_ZP), p(_ZP), p(_ZP), p(IMP), p(IMM), p(IMP), p(IMM), p(ABS), p(ABS), p(ABS), p(ABS),
	/*	f	*/	p(REL), p(IDY), p(IMP), p(IDY), p(ZPX), p(ZPX), p(ZPX), p(ZPX), p(IMP), p(ABY), p(IMP), p(ABY), p(ABX), p(ABX), p(ABX), p(ABX)
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
	OPCODE(ORA)
	OPCODE(AND)
	OPCODE(EOR)
	OPCODE(ADC)
	OPCODE(SBC)
	OPCODE(CMP)
	OPCODE(CPX)
	OPCODE(CPY)
	OPCODE(DEC)
	OPCODE(DEX)
	OPCODE(DEY)
	OPCODE(INC)
	OPCODE(INX)
	OPCODE(INY)
	OPCODE(ASL)
	OPCODE(ROL)
	OPCODE(LSR)
	OPCODE(ROR)
	OPCODE(LDA)
	OPCODE(STA)
	OPCODE(LDX)
	OPCODE(STX)
	OPCODE(LDY)
	OPCODE(STY)
	OPCODE(TAX)
	OPCODE(TXA)
	OPCODE(TAY)
	OPCODE(TYA)
	OPCODE(TSX)
	OPCODE(TXS)
	OPCODE(PLA)
	OPCODE(PHA)
	OPCODE(PLP)
	OPCODE(PHP)
};

#undef OPCODE
#undef MODE