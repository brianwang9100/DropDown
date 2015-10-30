#include "mylib.h"
u16 *videoBuffer = (u16 *)0x6000000;
void setPixel(int r, int c, u16 color) { 
	videoBuffer[r*240 + c] = color; 
}

void drawRect(int r, int c, int width, int height, u16 color) {
	int row,col;
	for(row=0; row<height; row++) {
		for(col=0; col<width; col++) {
			setPixel(row+r, col+c, color);
		}
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
