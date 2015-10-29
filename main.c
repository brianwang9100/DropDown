#include "main.h"
#include <stdio.h>

static int framecounter = 0;
static int drop = 0;
//static enum GBAState state = START_SCENE;
static int lastspeed;

static unsigned short LAST_A = 0;
//static unsigned short LAST_B = 0;
//static unsigned short LAST_SELECT = 0;
//static unsigned short LAST_START = 0;
//static unsigned short LAST_RIGHT = 0;
//static unsigned short LAST_LEFT = 0;
//static unsigned short LAST_UP = 0;
//static unsigned short LAST_DOWN = 0;
//static unsigned short LAST_R = 0;
//static unsigned short LAST_L = 0;

int main(void) {
	REG_DISPCTL	= MODE3 | BG2_ENABLE;
	MAINCHAR mainChar = {40, 40, 0, 0, 10, WHITE};
	MAINCHAR oldChar = mainChar;
	//GOAL goals[];
	//GOAL oldgoals[];	
	//draw ground
	drawRect(HEIGHTMAX + 1, 0, 240, 160 - HEIGHTMAX, LTGRAY); 
	while(1) {
		waitForVblank();
		//update framecounter
		framecounter++;
		//update oldChar
		oldChar = mainChar;
		if (KEY_DOWN_NOW(BUTTON_A) && !LAST_A) {
			drop = 1;
			mainChar.deltar = 30;
		}
		//update gravity
		if (framecounter >= 6) {
			if (!drop) {
				mainChar.deltar = mainChar.deltar + GRAVITY;
			}
			framecounter = 0;
		}
		updateChar(&mainChar);
		//drawing
		drawRect(oldChar.row, oldChar.col, oldChar.size, oldChar.size, BLACK);
		drawRect(mainChar.row, mainChar.col, mainChar.size, mainChar.size, mainChar.color);

		//check last button
		LAST_A = KEY_DOWN_NOW(BUTTON_A); 
    	//LAST_B = KEY_DOWN_NOW(BUTTON_B); 
    	//LAST_SELECT = KEY_DOWN_NOW(BUTTON_SELECT); 
    	//LAST_START = KEY_DOWN_NOW(BUTTON_START);
    	//LAST_RIGHT = KEY_DOWN_NOW(BUTTON_RIGHT);
    	//LAST_LEFT = KEY_DOWN_NOW(BUTTON_LEFT);
    	//LAST_UP = KEY_DOWN_NOW(BUTTON_UP);
    	//LAST_DOWN = KEY_DOWN_NOW(BUTTON_DOWN);
    	//LAST_R = KEY_DOWN_NOW(BUTTON_R);
    	//LAST_L = KEY_DOWN_NOW(BUTTON_L);
	}
	return 0;
}

void updateChar(MAINCHAR *mainChar) {
	mainChar->row = mainChar->row + mainChar->deltar;
	mainChar->col = mainChar->col + mainChar->deltac;
	
	//upperbound
	if (mainChar->row < 0) {
		mainChar->row = 0;
		mainChar->deltar = 0;
		framecounter = 0;
	}
	//lowerbound
	if(mainChar->row > HEIGHTMAX - mainChar->size + 1) {
		mainChar->row = HEIGHTMAX - mainChar->size + 1;
		framecounter = 0;
		if (drop) {
			mainChar->deltar = -lastspeed;
			drop = 0;
		} else {
			lastspeed = mainChar->deltar;
			mainChar->deltar = -mainChar->deltar;
		}
	}

}


