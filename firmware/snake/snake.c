#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../common/macros.h"
#include "frames.c"

#define XTAL		8000000L	//Crystal Freq.
#define TIMER_CLOCK     2       // Toggling Freq.

//volatile uint8_t matrixGreen[8] = {0xff, 0x81, 0xbd, 0xa5, 0xa5, 0xbd, 0x81, 0xff};
//volatile uint8_t matrixRed[8] = {0x00, 0x7e, 0x42, 0x5a, 0x5a, 0x42, 0x7e, 0x00}; 
volatile uint8_t* matrixGreen;
volatile uint8_t* matrixRed; 

volatile uint8_t count = 0;
volatile uint8_t updateFlag = 0;
volatile uint8_t drawFlag = 1;

uint16_t animationCount = 0;

void dispSingleLed(uint8_t x, uint8_t y, uint8_t color){
	if(color == 0)	cbi(PORTB, PB7);
	else if(color == 1){
		cbi(PORTB, PB7);
		PORTB = (PORTB & 0x78) + x;
		PORTD = (PORTD & 0x0f) + (y << 4);
		cbi(PORTD, PD7);
		sbi(PORTB, PB7);
		}
	else if(color == 2){
		cbi(PORTB, PB7);
		PORTB = (PORTB & 0x78) + x;
		PORTD = (PORTD & 0x0f) + (y << 4);
		sbi(PORTD, PD7);
		sbi(PORTB, PB7);
		}
	return;
}

void invertDisplay(void){
   	char i;
	for(i=0; i<8; i++){
		matrixGreen[i] = ~matrixGreen[i];
		matrixRed[i]   = ~matrixRed[i];
		char j;
		for(j=0; j<8; j++){
			if((_BV(j) & (matrixGreen[i] & matrixRed[i]))){
				matrixGreen[i] &= ~(_BV(j));
				matrixRed[i]   &= ~(_BV(j));
				}
			}
		}
};

void addNLeftShift(uint8_t leftCol, char color){
    uint8_t* matrixEdit;
    if(color == 1) matrixEdit = matrixGreen;
    if(color == 2) matrixEdit = matrixRed;

    char i;
    for(i = 0; i < 8; i++){
        matrixEdit[i] = (matrixEdit[i] << 1) + ((leftCol & _BV(7-i)) >> (7-i));
    }
}

void updateMatrices(void){
	drawFlag = 0;
	
    if(animationCount < 10){
        if(animationCount %  5 == 0){
            matrixGreen = cl1;
            matrixRed   = blank;
        }
        if(animationCount % 5 == 1){
            matrixGreen = cl2;
            matrixRed   = cl1;
        }
        if(animationCount % 5 == 2){
            matrixGreen = cl3;
            matrixRed   = cl2;
        }
        if(animationCount % 5 == 3){
            matrixGreen = cl4;
            matrixRed   = cl3;
        }
        if(animationCount % 5 == 4){
            matrixGreen = blank;
            matrixRed   = cl4;
        }
    }

    if(animationCount == 11){
        matrixGreen = smiley;
        matrixRed   = cl4;
    }

    if(animationCount == 12){
        matrixGreen = full;
        matrixRed   = blank;
    }

    if(animationCount > 12 && animationCount < 85){
        addNLeftShift(ecTicker[animationCount-13], 2);
    }
    
	++animationCount;
	drawFlag = 1;
};

ISR(TIMER0_OVF_vect){
if(!drawFlag) return;

//Display routine
uint8_t tcount = (uint8_t) (count % 128);
uint8_t x = ((tcount / 8) % 8);
uint8_t y = (tcount % 8);

if((matrixRed[y] & _BV(x)) && tcount < 64) dispSingleLed(x, y, 2);
else if(matrixGreen[y] & _BV(x) && tcount >= 64) dispSingleLed(x, y, 1);
else dispSingleLed(x, y, 0);

++count;

if(count == 128){
	updateFlag = 1;
	count = 0;
	}
}

void snake_init(void){
//PORT initializations
DDRD = 0xf0;
DDRB = 0x87;
PORTB = 0x00;
PORTD = 0x00;

//TIMER 1 CTC Mode Compare Match Interrupt
TCCR0 = _BV(CS00); //Prescaler is 64 for 8 Mhz clock
TIMSK = _BV(TOIE0); // Enable interrupt on overflow occurs aprrx every 2ms (2.048ms)

matrixGreen = blank;
matrixRed   = blank;

//sei();
}

int main(void){    

snake_init();
char i,j;
for(i=0; i<8; i++){
	for(j=0; j<8; j++){
		dispSingleLed(i, j, 1);
		_delay_ms(30);
		dispSingleLed(i, j, 2);
		_delay_ms(30);		
	};
};

dispSingleLed(7, 7, 0);
_delay_ms(200);

sei();

//	dispSingleLed(1, 4, 1);


while (1){
	_delay_ms(100);
	if(updateFlag) updateMatrices();
	}
	
return 0;
}
