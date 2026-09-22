/*
 * Data_memory.cpp
 *
 * Created: 12/02/2023 1:56:52 PM
 * Author : afschy
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define STOGG_		0x10
#define RESET_		0x08
#define CLK_		0x04
#define MEM_READ_	0x02
#define MEM_WRITE_	0x01

uint8_t data_memory[32];
uint8_t stack_memory[32];

void memory_reset() {
	for (int i=0; i<32; i++){
		data_memory[i] = 0;
		stack_memory[i] = 0;
	}
}

int main(void)
{
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRA = 0xE0;	// A[0] - Memory Write | A[1] - Memory Read | A[2] - Clock | A[3] - Reset | A[4] - StackToggle
	DDRB = 0x00;	// Address B[3:0] | Write Data B[7:4]
	DDRC = 0xFF;	// C[3:0] - Data Read
	
	memory_reset();
	
	uint8_t last_control_input = 0b0000, current_control_input;
	uint8_t last_write_data_address = 0b0000, current_write_data_address;
	
	while (1)
	{
		current_control_input = PINA & 0x1F;
		current_write_data_address = PINB;
		if (current_control_input & RESET_) {
			memory_reset();
			_delay_ms(50);
		}
		else if ((last_control_input ^ current_control_input) & CLK_) {			// EDGE
			if ((last_control_input & CLK_) && (last_control_input & MEM_WRITE_)){	// NEG-EDGE - for writing
				if(last_control_input & STOGG_) stack_memory[last_write_data_address & 0xF] = (last_write_data_address >> 4);
				else data_memory[last_write_data_address & 0xF] = (last_write_data_address >> 4);
			}
			_delay_ms(50);
		}
		if (current_control_input & MEM_READ_) {
			if(current_control_input & STOGG_) PORTC = stack_memory[current_write_data_address & 0xF];
			else PORTC = data_memory[current_write_data_address & 0xF];
		}
		
		last_control_input = current_control_input;
		last_write_data_address = current_write_data_address;
	}
}



