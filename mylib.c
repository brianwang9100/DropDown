#include "mylib.h"
u16 *videoBuffer = (u16 *)0x6000000;
void setPixel(int r, int c, u16 color) { 
	videoBuffer[r*240 + c] = color; 
}

void drawRect(int r, int c, int width, int height, u16 color) {
	//for(int row=0; row<height; row++) {
	//	for(int col=0; col<width; col++) {
	//		setPixel(row+r, col+c, color);
	//	}
	//}
	
	for (int row = 0; row < height; row++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)];
		DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
	}
}

void drawHollowRect(int r, int c, int width, int height, u16 color) {
	for (int row = 0; row < height; row++) {
		setPixel(row + r, c, color);	
		setPixel(row + r,c + width - 1, color); 
	}
	for (int col = 0; col < width; col++) {
		setPixel(r, col + c, color);
		setPixel(r + height - 1, col  + c, color);
	}
}

void fillScreen(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240*160) | DMA_SOURCE_FIXED | DMA_ON;
}

void fillScreenWithPicture(const u16 *image) {
	DMA[3].src = image;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240*160) | DMA_ON;
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			setPixel(row + r, col + c, image[row * width + col]);			
		}	
	}
}

void drawChar(int r, int c, char ch, u16 color) {
	for(int row = 0; row < 8; row++) {
		for(int col = 0; col < 6; col++) {
			if(fontdata_6x8[OFFSET(row, col, 6) + ch*48])			{
				setPixel(r+row, c+col, color);
			}
		}
	}
}

void drawString(int r, int c, char *str, u16 color) {
	while(*str)	{
		drawChar(r, c, *str++, color);
		c += 6;
	}
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}
