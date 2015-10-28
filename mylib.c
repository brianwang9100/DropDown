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
		setPixel(row+r, width - 1, color); 
	}
	for (int col = 0; col < width; col++) {
		setPixel(r, col + c, color);
		setPixel(height - 1, col  + c, color);
	}
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			setPixel(row + r, col + c, image[row * width + col]);			
		}	
	}
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}
