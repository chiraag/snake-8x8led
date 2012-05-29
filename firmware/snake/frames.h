typedef struct{
	volatile uint8_t matrixGreen[8];
	volatile uint8_t matrixRed[8]
} frame;

volatile frame animation[128] = {};

uint8_t ecGreen[8] = {0xf0, 0x80, 0xe0, 0x80, 0xf0, 0, 0, 0};
uint8_t ecRed[8] = {0, 0, 0, 0x07, 0x08, 0x08, 0x08, 0x07}; 