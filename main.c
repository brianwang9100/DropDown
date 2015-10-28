#include "main.h"

int main(void) {
	REG_DISPCTL	= MODE3 | BG2_ENABLE;
	MAINCHAR mainChar = {80, 40, 0, 0, 5, WHITE};
	MAINCHAR oldChar = mainChar;
	while(1) {
		//update oldChar
		oldChar = mainChar;
		//update gravity
		updateChar(&mainChar);	
		//drawing
		waitForVblank();
		drawRect(oldChar.row, oldChar.col, oldChar.size, oldChar.size, BLACK);
		drawRect(mainChar.row, mainChar.col, mainChar.size, mainChar.size, mainChar.color);
	}
	return 0;
}

void updateChar(MAINCHAR *mainChar) {
	mainChar->deltar = mainChar->deltar + GRAVITY;
	mainChar->row = mainChar->row + mainChar->deltar;
	mainChar->col = mainChar->col + mainChar->deltac;
	
	//upperbound
	if (mainChar->row < 0) {
		mainChar->row = 0;
		mainChar->deltar = -mainChar->deltar;
	}
	//lowerbound
	if(mainChar->row > HEIGHTMAX - mainChar->size + 1) {
		mainChar->row = HEIGHTMAX - mainChar->size + 1;
		mainChar->deltar = -mainChar->deltar;
	}

}


