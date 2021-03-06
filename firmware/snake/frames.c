typedef struct {
	uint8_t* matrixGreen;
	uint8_t* matrixRed;
} frame;

uint8_t ecGreen[8] = {0xf0, 0x80, 0xe0, 0x80, 0xf0, 0, 0, 0};
uint8_t ecRed[8] = {0, 0, 0, 0x07, 0x08, 0x08, 0x08, 0x07}; 
uint8_t ecTicker[72] = {
	0x7c, 0x54, 0x44, 0x00, 0x7c, 0x04, 0x04, 0x00, 0x7c, 0x54, 0x44, 0x00, 0x7c, 0x44, 0x44, 0x00, 0x40, 0x7c, 0x40, 0x00,
	0x7c, 0x50, 0x50, 0x2c, 0x00, 0x38, 0x44, 0x44, 0x38, 0x00, 0x7c, 0x20, 0x10, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x44, 0x44,
	0x00, 0x74, 0x54, 0x5c, 0x00, 0x00, 0x00, 0x7c, 0x44, 0x44, 0x00, 0x7c, 0x04, 0x04, 0x00, 0x78, 0x04, 0x04, 0x78, 0x00,
	0x7c, 0x54, 0x54, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	
uint8_t blank[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t full[8]  = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

uint8_t sq1[8] = {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00};
uint8_t sq2[8] = {0x00, 0x00, 0x3c, 0x24, 0x24, 0x3c, 0x00, 0x00};
uint8_t sq3[8] = {0x00, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x00};
uint8_t sq4[8] = {0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff};

uint8_t cl1[8] = {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00};
uint8_t cl2[8] = {0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00};
uint8_t cl3[8] = {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00};
uint8_t cl4[8] = {0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c};

uint8_t smiley[8] = {0x00, 0x00, 0x24, 0x00, 0x42, 0x3c, 0x00, 0x00};
