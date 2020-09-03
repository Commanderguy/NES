#include "Core6502.h"
#define OPCODE(x) void Core6502:: ## x()
#define MODE(x) void Core6502:: ## x()

Core6502::Core6502(Bus* b, ptr ProgramCounter):
_bus{ b },
ProgramCounter{ ProgramCounter },
StatusReg{ 0 }
{}

OPCODE(XXX)
{
	throw "This opcode has not been implemented yet";
}


/// <summary>
/// No operation.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
OPCODE(NOP)
{}


/// <summary>
/// Bitwise OR operation on the accumulator with an address.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
OPCODE(ORA)
{
	u8 val;
	if (curOp == 0x09)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
	{
		val = _bus->Read(addressOperate);
	}
	a |= val;
	if (a == 0)
		StatusReg.Z.Set();
	if (a & 128)
		StatusReg.N.Set();
}


OPCODE(AND)
{
	u8 val;
	if (curOp == 0x29)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
	{
		val = _bus->Read(addressOperate);
	}
	a &= val;
	if (a == 0)
		StatusReg.Z.Set();
	if (a & 128)
		StatusReg.N.Set();
}



OPCODE(EOR)
{
	u8 val;
	if (curOp == 0x49)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
	{
		val = _bus->Read(addressOperate);
	}
	a ^= val;
	if (a == 0)
		StatusReg.Z.Set();
	if (a & 128)
		StatusReg.N.Set();
}


OPCODE(ADC)
{
	u8 val;
	if (curOp == 0x69)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
	{
		val = _bus->Read(addressOperate);
	}
	u16 tmp = a + val + StatusReg.C.Get();
	if (tmp > 255)
		StatusReg.C.Set();
	if ((~((u16)a ^ (u16)val) & ((u16)a ^ (u16)tmp)) & 0x0080)
		StatusReg.V.Set();
	if (a & 128)
		StatusReg.N.Set();
	if (a == 0)
		StatusReg.Z.Set();
	a = tmp & 0x00FF;
}


OPCODE(SBC)
{
	u8 val;
	if (curOp == 0xE9)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
		val = _bus->Read(addressOperate);
	u16 vv = ((u16)val) ^ 0x00FF;
	u16 tmp = a + vv + StatusReg.C.Get();
	if (tmp > 255)
		StatusReg.C.Set();
	if ((tmp ^ (u8)a) & (tmp ^ vv) & 0x0080)
		StatusReg.V.Set();
	if (a & 128)
		StatusReg.N.Set();
	if (a == 0)
		StatusReg.Z.Set();
	a = tmp & 0x00FF;
}


OPCODE(CMP)
{
	u8 val;
	if (curOp == 0xC9)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
		val = _bus->Read(addressOperate);
	u16 tmp = (u16)a - (u16)val;
	if (a >= val)
		StatusReg.C.Set();
	if ((tmp & 0x00FF) == 0x0000)
	{
		StatusReg.Z.Set();
		StatusReg.C.Set();
	}
	if (tmp & 0x0080)
		StatusReg.N.Set();
}


OPCODE(CPX)
{
	u8 val;
	if (curOp == 0xE0)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
		val = _bus->Read(addressOperate);
	u16 tmp = (u16)x - (u16)val;
	if (x >= val)
		StatusReg.C.Set();
	if ((tmp & 0x00FF) == 0x0000)
	{
		StatusReg.Z.Set();
		StatusReg.C.Set();
	}
	if (tmp & 0x0080)
		StatusReg.N.Set();
}

OPCODE(CPY)
{
	u8 val;
	if (curOp == 0xC0)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
		val = _bus->Read(addressOperate);
	u16 tmp = (u16)y - (u16)val;
	if (y >= val)
		StatusReg.C.Set();
	if ((tmp & 0x00FF) == 0x0000)
	{
		StatusReg.Z.Set();
		StatusReg.C.Set();
	}
	if (tmp & 0x0080)
		StatusReg.N.Set();

}


OPCODE(DEC)
{
	u8 tmp = _bus->Read(addressOperate) - 1;
	_bus->Write(addressOperate, tmp);
	if (tmp == 0)
		StatusReg.Z.Set();
	if (tmp & 128)
		StatusReg.N.Set();
}


OPCODE(DEX)
{
	x--;
	if (x == 0)
		StatusReg.Z.Set();
	if (x & 128)
		StatusReg.N.Set();
}


OPCODE(DEY)
{
	y--;
	if (y == 0)
		StatusReg.Z.Set();
	if (y & 128)
		StatusReg.N.Set();
}


OPCODE(INC)
{
	u8 tmp = _bus->Read(addressOperate) + 1;
	_bus->Write(addressOperate, tmp);
	if (tmp == 0)
		StatusReg.Z.Set();
	if (tmp & 128)
		StatusReg.N.Set();
}


OPCODE(INX)
{
	x++;
	if (x == 0)
		StatusReg.Z.Set();
	if (x & 128)
		StatusReg.N.Set();
}


OPCODE(INY)
{
	y++;
	if (y == 0)
		StatusReg.Z.Set();
	if (y & 128)
		StatusReg.N.Set();
}


OPCODE(ASL)
{
	u8 t;
	if (curOp == 0x0A)
		t = a;
	else
		t = _bus->Read(addressOperate);

	if (t & 128)
		StatusReg.C.Set();
	t <<= 1;
	t &= ~ 1;
	if (t & 128)
		StatusReg.N.Set();
	if (t == 0)
		StatusReg.Z.Set();
	if (curOp == 0x0A)
		a = t;
	else
		_bus->Write(addressOperate, t);
}


OPCODE(ROL)
{
	u8 t;
	if (curOp == 0x0A)
		t = a;
	else
		t = _bus->Read(addressOperate);
	bool oBit = StatusReg.C.Get();
	if (t & 128)
		StatusReg.C.Set();
	t <<= 1;
	t &= ~1;
	if (oBit)
		t |= 1;
	if (t & 128)
		StatusReg.N.Set();
	if (t == 0)
		StatusReg.Z.Set();
	if (curOp == 0x0A)
		a = t;
	else
		_bus->Write(addressOperate, t);
}


OPCODE(LSR)
{
	u8 t;
	if (curOp == 0x0A)
		t = a;
	else
		t = _bus->Read(addressOperate);

	if (t & 1)
		StatusReg.C.Set();
	t >>= 1;
	t &= ~128;
	if (t & 128)
		StatusReg.N.Set();
	if (t == 0)
		StatusReg.Z.Set();
	if (curOp == 0x0A)
		a = t;
	else
		_bus->Write(addressOperate, t);
}

OPCODE(ROR)
{
	u8 t;
	if (curOp == 0x0A)
		t = a;
	else
		t = _bus->Read(addressOperate);
	bool oBit = StatusReg.C.Get();
	if (t & 1)
		StatusReg.C.Set();
	t >>= 1;
	t &= ~128;
	if (oBit)
		t |= 128;
	if (t & 128)
		StatusReg.N.Set();
	if (t == 0)
		StatusReg.Z.Set();
	if (curOp == 0x0A)
		a = t;
	else
		_bus->Write(addressOperate, t);
}


OPCODE(LDA)
{
	u8 val;
	if (curOp == 0xA9)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
		val = _bus->Read(addressOperate);
	a = val;
	if (a == 0)
		StatusReg.Z.Set();
	if (a & 128)
		StatusReg.N.Set();
}


OPCODE(STA)
{
	_bus->Write(addressOperate, a);
}


OPCODE(LDX)
{
	u8 val;
	if (curOp == 0xA2)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
		val = _bus->Read(addressOperate);
	x = val;
	if (x == 0)
		StatusReg.Z.Set();
	if (x & 128)
		StatusReg.N.Set();
}


OPCODE(STX)
{
	_bus->Write(addressOperate, x);
}


OPCODE(LDY)
{
	u8 val;
	if (curOp == 0xA2)
	{
		val = _bus->Read(ProgramCounter);
		ProgramCounter++;
	}
	else
		val = _bus->Read(addressOperate);
	y = val;
	if (y == 0)
		StatusReg.Z.Set();
	if (y & 128)
		StatusReg.N.Set();
}


OPCODE(STY)
{
	_bus->Write(addressOperate, y);
}


OPCODE(TAX)
{
	x = a;
	if (a == 0)
		StatusReg.Z.Set();
	if (a & 128)
		StatusReg.N.Set();
}


OPCODE(TXA)
{
	a = x;
	if (x == 0)
		StatusReg.Z.Set();
	if (x & 128)
		StatusReg.N.Set();
}


OPCODE(TAY)
{
	y = a;
	if (a == 0)
		StatusReg.Z.Set();
	if (a & 128)
		StatusReg.N.Set();
}


OPCODE(TYA)
{
	a = y;
	if (y == 0)
		StatusReg.Z.Set();
	if (y & 128)
		StatusReg.N.Set();
}

OPCODE(TSX)
{
	x = StackPtr;
	if (x == 0)
		StatusReg.Z.Set();
	if (x & 128)
		StatusReg.N.Set();
}


OPCODE(TXS)
{
	StackPtr = x;
}


OPCODE(PLA)
{
	StackPtr++;
	a = _bus->Read(0x0100 + StackPtr);
	if (a == 0)
		StatusReg.Z.Set();
	if (a & 128)
		StatusReg.N.Set();
}


OPCODE(PHA)
{
	_bus->Write(0x0100 + StackPtr, a);
	StackPtr--;
}


OPCODE(PLP)
{
	StackPtr++;
	StatusReg.data = _bus->Read(0x0100 + StackPtr);
}


OPCODE(PHP)
{
	_bus->Write(0x0100 + StackPtr, StatusReg.data);
	StackPtr--;
}


OPCODE(BPL)
{
	if (!StatusReg.N.Get())
		ProgramCounter = addressOperate;
}

OPCODE(BMI)
{
	if (StatusReg.N.Get())
		ProgramCounter = addressOperate;
}

OPCODE(BVC)
{
	if (!StatusReg.V.Get())
		ProgramCounter = addressOperate;
}


OPCODE(BVS)
{
	if (StatusReg.V.Get())
		ProgramCounter = addressOperate;
}


OPCODE(BCC)
{
	if (!StatusReg.C.Get())
		ProgramCounter = addressOperate;
}


OPCODE(BCS)
{
	if (StatusReg.C.Get())
		ProgramCounter = addressOperate;
}


OPCODE(BNE)
{
	if (!StatusReg.Z.Get())
		ProgramCounter = addressOperate;
}

OPCODE(BEQ)
{
	if (StatusReg.Z.Get())
		ProgramCounter = addressOperate;
}


OPCODE(CLC)
{
	StatusReg.C.Clear();
}


OPCODE(SEC)
{
	StatusReg.C.Set();
}

OPCODE(CLD)
{
	StatusReg.D.Clear();
}


OPCODE(SED)
{
	StatusReg.D.Set();
}


OPCODE(CLI)
{
	StatusReg.I.Clear();
}


OPCODE(SEI)
{
	StatusReg.I.Set();
}

OPCODE(CLV)
{
	StatusReg.V.Clear();
}


OPCODE(BIT)
{
	u8 var = _bus->Read(addressOperate);
	u8 tmp = a & var;
	if(!tmp)
		StatusReg.Z.Set();
	if (var & (1 << 7))
		StatusReg.N.Set();
	if (var & (1 << 6))
		StatusReg.V.Set();
}


OPCODE(JMP)
{
	if (curOp == 0x4C)
		ProgramCounter = addressOperate;
	else
	{
		ProgramCounter = _bus->Read(addressOperate);
	}
	
}


OPCODE(JSR)
{
	ProgramCounter--;

	_bus->Write(0x0100 + StackPtr, (ProgramCounter >> 8) & 0x00FF);
	StackPtr--;
	_bus->Write(0x0100 + StackPtr, ProgramCounter & 0x00FF);
	StackPtr--;
	ProgramCounter = addressOperate;
}


OPCODE(RTS)
{
	ToPtr t;
	StackPtr++;
	t.lo = _bus->Read(0x0100 + StackPtr);
	StackPtr++;
	t.hi = _bus->Read(0x100 + StackPtr);
	ProgramCounter = t.p;
	ProgramCounter++;
}


OPCODE(BRK)
{
	ToPtr w;
	w.p = ProgramCounter;
	StatusReg.I.Set();
	_bus->Write(0x100 + StackPtr, w.hi);
	StackPtr--;
	_bus->Write(0x100 + StackPtr, w.lo);
	StackPtr--;
	StatusReg.B.Set();
	_bus->Write(0x100 + StackPtr, StatusReg.data);
	StatusReg.B.Clear();
	StackPtr--;

	ProgramCounter = (u16)_bus->Read(0xFFFE) | ((u16)_bus->Read(0xFFFF) << 8);
}


OPCODE(RTI)
{
	StackPtr++;
	StatusReg.data = _bus->Read(0x0100 + StackPtr);
	StatusReg.B.Clear(); // About this line I'm not really sure.
	ToPtr dest;
	StackPtr++;
	dest.lo = _bus->Read(0x100 + StackPtr);
	StackPtr++;
	dest.hi = _bus->Read(0x100 + StackPtr);
	ProgramCounter = dest.p;
}



/// <summary>
/// Implied/Implicit. The operand is defined by the instruction, and we don't need to operate on a address on the ram.
/// </summary>
MODE(IMP)
{

}


/// <summary>
/// Zeropage adressing mode. The adresses high byte is always 0x00 and the low byte is provided by the next byte.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(_ZP)
{
	ToPtr t;
	t.hi = 0x00;
	t.lo = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p;
}


/// <summary>
/// Absolute addressing mode. Similar to zero page adressing mode, but this time, the high byte is also included in the program.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ABS)
{
	ToPtr t;
	t.p = 0;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p;
}


/// <summary>
/// AccumulatorAdressingMode. The Accumulator addressing mode is a special version of the immediate mode for working on the acummulator.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(AAM)
{

}


/// <summary>
/// Immediate mode: There is nothing to do here. It's the same as implied, but opcodes that work with implied have arguments specified in the next byte
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(IMM)
{

}


/// <summary>
/// Relative mode. The relative mode operates on the program counter + the value in the next byte. The next byte has to be read as a signed number, so the range is -127 - 127
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(REL)
{
	ToPtr t;
	t.lo = 0;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = ProgramCounter + ((signed char)(t.p));
}


/// <summary>
/// Indirect addressing is only used by a special type of JMP. The operate address is set to the pointer found at the address specified in the memory that get's pointed to by the next two bytes.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(IND)
{
	ToPtr t;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	
	ToPtr f;
	f.lo = _bus->Read(t.p);
	t.p++;
	f.hi = _bus->Read(t.p);
	addressOperate = f.p;
}


/// <summary>
/// Zero page address mode with x index. The address to operate on is the content of the next byte + x.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ZPX)
{
	ToPtr t;
	t.hi = 0x00;
	t.lo = _bus->Read(ProgramCounter) + x;
	ProgramCounter++;
	addressOperate = t.p;
}

/// <summary>
/// Zero page address mode with x index. The address to operate on is the content of the next byte + y.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ZPY)
{

	ToPtr t;
	t.hi = 0x00;
	t.lo = _bus->Read(ProgramCounter) + y;
	ProgramCounter++;
	addressOperate = t.p;
}


/// <summary>
/// Absolute addressing mode indexed with the x register.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ABX)
{
	ToPtr t;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p + x;
}


/// <summary>
/// Absolute addressing mode indexed with t´he y register
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ABY)
{
	ToPtr t;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p + y;
}


/// <summary>
/// Indexed indirect: operandAddress = $(byte + x). The operand address is set to the content of the address that get's pointed to by the operand + the x register modulo 0xFF to not leave the zero page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(IDX)
{
	ToPtr t;
	t.hi = 0x00;
	t.lo = _bus->Read(ProgramCounter) + x;
	ProgramCounter++;
	addressOperate = t.p;
}


/// <summary>
/// Indirect indexed. This opcode has two bytes as operand that contain the indirect address. The indirect address and the byte after it now contain the operand address, to which we add the content of the y register.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(IDY)
{
	ToPtr i;
	i.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
//	i.hi = _bus->Read(ProgramCounter);
//	ProgramCounter++;
	i.hi = 0;

	ToPtr t;
	t.lo = _bus->Read(i.p);
	t.p++;
	t.hi = _bus->Read(i.p);
	addressOperate = t.p + y;
}