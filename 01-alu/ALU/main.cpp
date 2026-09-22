/*
 * ALU.cpp
 *
 * Created: 12/02/2023 1:41:40 PM
 * Author : afschy
 */ 

#include <avr/io.h>
#define F_CPU 1000000 // Clock Frequency
#include <util/delay.h>

int main(void)
{
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);

	DDRB = 0x00;				// in1 - B[3:0], in2 - B[7:4]
	DDRD = 0xF8;				// ALUOp D[2:0]
	DDRC = 0x8f;				// C[7] - Zero Flag | C[3:0] - Output

	uint8_t control_bits;
	uint8_t in1, in2, out;

	while (1)
	{
		control_bits = PIND & 0x07;

		in1 = PINB & 0x0f;
		in2 = (PINB & 0xf0) >> 4;
		out = 0;

		if(control_bits == 0) {
			out = in1 + in2;
		} else if(control_bits == 1){
			out = in1 - in2;
		} else if(control_bits == 2) {
			out = in1 & in2;
		} else if(control_bits == 3) {
			out = in1 | in2;
		} else if(control_bits == 4) {
			out = ~(in1 | in2);
		} else if(control_bits == 5) {
			out = in1 << in2;
		} else if(control_bits == 6) {
			out = in1 >> in2;
		}

		out = out & 0x0f;
		if(!out) {
			out = out | 0x80;
		}

		PORTC = out;
	}
}
