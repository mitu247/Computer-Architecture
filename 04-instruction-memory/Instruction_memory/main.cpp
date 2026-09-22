/*
 * Instruction_memory.cpp
 *
 * Created: 12/02/2023 11:44:44 AM
 * Author : afschy
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t reverse_bits(uint8_t num) {
	uint8_t reversed = 0;
	for(int i=0; i<=7; i++) {
		uint8_t temp = num & (1 << i);
		temp = temp >> i;
		reversed = reversed | (temp << (7-i));
	}
	return reversed;
}

uint16_t instruction_memory[] = {
	0x801b, 0x8029, 0xb611, 0xb622, 0x4631, 0x4642, 0xa345, 0x2000
};

int main(void)
{
    MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	DDRB = 0x00;	// Program counter input
	
	// Top 8 bits: A0 - A7, A0 is MSB
	// Bottom 8 bits: C7 - C0, C7 is MSB
	DDRA = 0xff;
	DDRC = 0xff;
	
	// D[0] - Stack Toggle
	DDRD = 0xff;
	
	uint8_t pc = -1, top_8_bits, bottom_8_bits;
	uint16_t instruction;
    while (1) 
    {
		if(pc == PINB) continue;
		pc = PINB;
		instruction = instruction_memory[pc];
		bottom_8_bits = uint8_t(instruction);
		top_8_bits = reverse_bits(uint8_t(instruction >> 8));
		PORTA = top_8_bits;
		PORTC = bottom_8_bits;
		PORTD = 0;
		
		if(((instruction&0xf000) == 0x4000) || ((instruction&0xf000) == 0xb000)) {
			if((instruction&0x0f00) == 0x0600) PORTD = 1;
		}
		_delay_ms(50);
    }
}

