#pragma once
#include "Bus.h"
#include "Types.h"
// This #define command defines the Template for opcodes and make the code more readable
// Every opcode definition consists of an function that executes and then returns the cycles it took.
#define OPCODE(x) void x();
#define MODE(x) void x();
// This declares a function pointer to a member of the cpu. It's just for better code readability
#define p(x) &Core6502:: ## x


#ifdef _DEBUG
// ---------------------- illegal opcodes ------------------------
/*
	These define statements enable the emulator to work without 
	imlementing the illegal opcodes while still having them in the 
	opcode matrix. They should be implemented for the final release.
	This is definitly not the best solution, but it does the job for 
	debug purposes. For a good emulator, these opcodes have to be 
	impolemented, but most roms work without them.
*/
#define KIL XXX
#define SLO XXX
#define ANC XXX
#define RLA XXX
#define SRE XXX
#define ALR XXX
#define RRA XXX
#define ARR XXX
#define SAX XXX
#define XAA XXX
#define AHX XXX
#define TAS XXX
#define SHY XXX
#define SHX XXX
#define AHX XXX
#define LAX XXX
#define LAS XXX
#define DCP XXX
#define AXS XXX
#define ISC XXX
#endif


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
	Bit<4> B;
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
	/*	0	*/	p(BRK), p(ORA), p(KIL), p(SLO), p(NOP), p(ORA), p(ASL), p(SLO), p(PHP), p(ORA), p(ASL), p(ANC), p(NOP), p(ORA), p(ASL), p(SLO),
	/*	1	*/	p(BPL), p(ORA), p(KIL), p(SLO), p(NOP), p(ORA), p(ASL), p(SLO), p(CLC), p(ORA), p(NOP), p(SLO), p(NOP), p(ORA), p(ASL), p(SLO),
	/*	2	*/	p(JSR), p(AND), p(KIL), p(RLA), p(BIT), p(AND), p(ROL), p(RLA), p(PLP), p(AND), p(ROL), p(ANC), p(BIT), p(AND), p(ROL), p(RLA),
	/*	3	*/	p(BMI), p(AND), p(KIL), p(RLA), p(NOP), p(AND), p(ROL), p(RLA), p(SEC), p(AND), p(NOP), p(RLA), p(NOP), p(AND), p(ROL), p(RLA),
	/*	4	*/	p(RTI), p(EOR), p(KIL), p(SRE), p(NOP), p(EOR), p(LSR), p(SRE), p(PHA), p(EOR), p(LSR), p(ALR), p(JMP), p(EOR), p(LSR), p(SRE),
	/*	5	*/	p(BVC), p(EOR), p(KIL), p(SRE), p(NOP), p(EOR), p(LSR), p(SRE), p(CLI), p(EOR), p(NOP), p(SRE), p(NOP), p(EOR), p(LSR), p(SRE),
	/*	6	*/	p(RTS), p(ADC), p(KIL), p(RRA), p(NOP), p(ADC), p(ROR), p(RRA), p(PLA), p(ADC), p(ROR), p(ARR), p(JMP), p(ADC), p(ROR), p(RRA),
	/*	7	*/	p(BVS), p(ADC), p(KIL), p(RRA), p(NOP), p(ADC), p(ROR), p(RRA), p(SEI), p(ADC), p(NOP), p(RRA), p(NOP), p(ADC), p(ROR), p(RRA),
	/*	8	*/	p(NOP), p(STA), p(NOP), p(SAX), p(STY), p(STA), p(STX), p(SAX), p(DEY), p(NOP), p(TXA), p(XAA), p(STY), p(STA), p(STX), p(SAX),
	/*	9	*/	p(BCC), p(STA), p(KIL), p(AHX), p(STY), p(STA), p(STX), p(SAX), p(TYA), p(STA), p(TSX), p(TAS), p(SHY), p(STA), p(SHX), p(AHX),
	/*	a	*/	p(LDY), p(LDA), p(LDX), p(LAX), p(LDY), p(LDA), p(LDX), p(LAX), p(TAY), p(LDA), p(TAX), p(LAX), p(LDY), p(LDA), p(LDX), p(LAX),
	/*	b	*/	p(BCS), p(LDA), p(KIL), p(LAX), p(LDY), p(LDA), p(LDX), p(LAX), p(CLV), p(LDA), p(TAX), p(LAS), p(LDY), p(LDA), p(LDX), p(LAX),
	/*	c	*/	p(CPY), p(CMP), p(NOP), p(DCP), p(CPY), p(CMP), p(DEC), p(DCP), p(INY), p(CMP), p(DEX), p(AXS), p(CPY), p(CMP), p(DEC), p(DCP),
	/*	d	*/	p(BNE), p(CMP), p(KIL), p(DCP), p(NOP), p(CMP), p(DEC), p(DCP), p(CLD), p(CMP), p(NOP), p(DCP), p(NOP), p(CMP), p(DEC), p(DCP),
	/*	e	*/	p(CPX), p(SBC), p(NOP), p(ISC), p(CPX), p(SBC), p(INC), p(ISC), p(INX), p(SBC), p(NOP), p(SBC), p(CPX), p(SBC), p(INC), p(ISC),
	/*	f	*/	p(BEQ), p(SBC), p(KIL), p(ISC), p(NOP), p(SBC), p(INC), p(ISC), p(SED), p(SBC), p(NOP), p(ISC), p(NOP), p(SBC), p(INC), p(ISC)
	};


	// Addressingmode matrix
	void(Core6502::* AddressingMode[256])() =
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
	OPCODE(BPL)
	OPCODE(BMI)
	OPCODE(BVC)
	OPCODE(BVS)
	OPCODE(BCC)
	OPCODE(BCS)
	OPCODE(BNE)
	OPCODE(BEQ)
	OPCODE(CLC)
	OPCODE(SEC)
	OPCODE(CLD)
	OPCODE(SED)
	OPCODE(CLI)
	OPCODE(SEI)
	OPCODE(CLV)
	OPCODE(BIT)
	OPCODE(JMP)
	OPCODE(JSR)
	OPCODE(RTS)
	OPCODE(BRK)
	OPCODE(RTI)
};

#undef OPCODE
#undef MODE