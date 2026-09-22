/*
 * Control.cpp
 *
 * Created: 12/02/2023 1:59:26 PM
 * Author : afschy
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// alu_op: add = 0, sub = 1, and = 2, or = 3, nor = 4, shift_left = 5, shift_right = 6
// reg_dst, alu_src, mem_to_reg, reg_write, mem_read, mem_write, branch_eq, branch_neq, jump, alu_op[3]
uint16_t control_rom[16] = {
	0b000000010001,		// bneq
	0b010100000010,		// andi
	0b000000001000,		// j
	0b010100000110,		// srl
	0b011110000000,		// lw
	0b010100000011,		// ori
	0b100100000100,		// nor
	0b100100000011,		// or
	0b010100000000,		// addi
	0b010100000001,		// subi
	0b100100000001,		// sub
	0b010001000000,		// sw
	0b100100000000,		// add
	0b100100000010,		// and
	0b010100000101,		// sll
	0b000000100001		// beq
};

uint8_t reverse_bits(uint8_t num) {
	uint8_t reversed = 0;
	for(int i=0; i<=7; i++) {
		uint8_t temp = num & (1 << i);
		temp = temp >> i;
		reversed = reversed | (temp << (7-i));
	}
	return reversed;
}

int main(void)
{
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRB = 0xF0; // B[3:0] - Opcode Input
	
	// Control Unit Bits : C[3:0]A[7:0]
	// C[reg_dst[1], alu_src[1], mem_to_reg[1], reg_write[1]] A[mem_read[1], mem_write[1], branch_eq[1], branch_neq[1], jump[1], alu_op[3]]
	DDRA = 0xFF;
	DDRC = 0xFF;
	
	uint8_t opcode = ~0;
	uint8_t real_opcode;
	
	while (1)
	{
		if (opcode != (0x0F & PINB)){
			opcode = (0x0F & PINB);
			real_opcode = reverse_bits(opcode);
			real_opcode = (real_opcode >> 4) & 0x0f;
			PORTA = control_rom[real_opcode];
			PORTC = (control_rom[real_opcode] >> 8);
			//_delay_ms(50);	
		}
	}
}



