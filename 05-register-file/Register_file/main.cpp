/*
 * Register_file.cpp
 *
 * Created: 12/02/2023 12:17:33 PM
 * Author : afschy
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define WRITE_REG_	0x01
#define CLK_		0x02
#define RESET_		0x04
#define OUTPUT_		0x08

uint8_t register_file[8] = {0};

int main(void)
{
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRB = 0x00;	// B[3:0] - SrcReg1, B[7:4] - SrcReg2, MSB = 3 and 7
	DDRD = 0x00;	// D[3:0] - DstReg, D[7:4] - Write Data, MSB = 3 and 7
	
	DDRA = 0xFF;	// A[3:0] - $1, A[7:4] - $2, MSB = 3 and 7
	DDRC = 0xF0;	// C[0] - WriteReg, C[1] - CLK, C[2] - RESET
	
	uint8_t src, dst_data, last_control = 0, current_control;
	
	while (1)
	{
		src = PINB;
		dst_data = PIND;
		current_control = PINC;
		
		PORTA = (register_file[(src>>4) & 0x7]<<4) | (register_file[src & 0x7]);
		if (current_control & RESET_) {		// Reset all registers
			for (int i=0; i<8; i++) register_file[i] = 0;
			_delay_ms(50);
			continue;
		}
		
		if ((current_control ^ last_control) & CLK_) {		// EDGE
			if ((last_control & CLK_) && (last_control & WRITE_REG_)) {		// NEGATIVE EDGE with WRITE INSTRUCTION
				register_file[dst_data & 0x7] = (dst_data >> 4);
				PORTD = dst_data & 0xf0;
			}
			_delay_ms(50);
		}
		
		last_control = current_control;
	}
}

