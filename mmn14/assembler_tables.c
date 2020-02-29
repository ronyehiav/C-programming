#include "assembler.h"

/* operation code table initialization */
opcode opcodes_table[NUM_OF_OPCODE] = {
	{0, "mov"},
	{1, "cmp"},
	{2, "add"},
	{3, "sub"},
	{4, "lea"},
	{5, "clr"},
	{6, "not"},
	{7, "inc"},
	{8, "dec"},
	{9, "jmp"},
	{10, "bne"},
	{11, "red"},
	{12, "prn"},
	{13, "jsr"},
	{14, "rts"},
	{15, "stop"}
	};
