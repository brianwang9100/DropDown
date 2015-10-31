#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#define GOALSSIZE 3

static int framecounter = 0;
static int drop = 0;
static int lastspeed = 0;
static int goalcounter = 0;
static int score = 0;
static enum GBAState state = START_SCENE;

static unsigned short LAST_A = 0;
static unsigned short LAST_B = 0;
static unsigned short LAST_SELECT = 0;
static unsigned short LAST_START = 0;
//static unsigned short LAST_RIGHT = 0;
//static unsigned short LAST_LEFT = 0;
//static unsigned short LAST_UP = 0;
//static unsigned short LAST_DOWN = 0;
//static unsigned short LAST_R = 0;
//static unsigned short LAST_L = 0;

int main(void) {
	REG_DISPCTL	= MODE3 | BG2_ENABLE;
	MAINCHAR mainChar = {40, 40, 0, 0, 10, BLACK};
	MAINCHAR oldChar = mainChar;

	u16 colors[] = {RED, GREEN, BLUE};
	int nextcolor = 0;

	GOAL goal1 = {0, 0, 0, 0, 0, 0, 0, WHITE};
	GOAL goal2 = {0, 0, 0, 0, 0, 0, 0, WHITE};
	GOAL goal3 = {0, 0, 0, 0, 0, 0, 0, WHITE};

	GOAL goals[GOALSSIZE] = {goal1, goal2, goal3};
	GOAL oldgoals[GOALSSIZE];
	GOAL *goalpointer = goals;
	GOAL *oldcur;
	GOAL *cur;
	int tutorialdoneA = 0;
	int tutorialdoneB = 0;
	while(1) {
		switch(state) {
			case START_SCENE:
				fillScreen(BLACK);
				drawString(0,0, "START SCREEN", WHITE);
				state = START_SCENE_NODRAW;
				break;
			case START_SCENE_NODRAW:
				if (KEY_DOWN_NOW(BUTTON_SELECT) && !LAST_SELECT)
					state = START_SCENE;
				if (KEY_DOWN_NOW(BUTTON_START) && !LAST_START)
					state = MAIN_SCENE_SETUP;
				break;
			case MAIN_SCENE_SETUP:
				fillScreen(BLACK);
				//mainChar reset
				mainChar.row = 40;
				mainChar.col = 40;
				mainChar.color = BLACK;
				mainChar.deltar = 0;
				mainChar.deltac = 0;
				//goal reset
				goals[0].set = 0;
				goals[1].set = 0;
				goals[2].set = 0;
				goals[0].row = 0;
				goals[1].row = 0;
				goals[2].row = 0;
				goals[0].col = 0;
				goals[1].col = 0;
				goals[2].col = 0;
				//tracker reset
				nextcolor = 0;
				goalpointer = goals;
				framecounter = 0;
				drop = 0;
				lastspeed = 0;
				goalcounter = 0;
				score = 0;
				tutorialdoneA = 0;
				tutorialdoneB = 0;
				drawString(0, 0, "0", WHITE);	
				drawString(8, 0, "PRESS A TO SPEED DROP", WHITE);	
				drawString(16, 0, "PRESS B TO CHANGE COLORS", WHITE);	
				//draw ground
				//fillScreen(PINK);
				drawRect(HEIGHTMAX + 1, 0, 240, 160 - HEIGHTMAX, LTGRAY); 
				state = MAIN_SCENE;
				break;
			case MAIN_SCENE:	
				waitForVblank();
				if (KEY_DOWN_NOW(BUTTON_SELECT && !LAST_SELECT)) {
					state = START_SCENE;
				}
				//update framecounter
				framecounter++;
				goalcounter++;
		
				//update oldChar
				oldChar = mainChar;
				for (int i = 0; i < GOALSSIZE; i++) {
					oldgoals[i] = goals[i];
				}
				
				//check null goals
				if (goalcounter >= 90 && tutorialdoneA && tutorialdoneB) {
					if (!(goalpointer->set)) {
						goalpointer->set = 1;
						goalpointer->row = HEIGHTMAX/4 + rand()%(HEIGHTMAX*3/4) - 20;
						goalpointer->col = 240 - 5;
						goalpointer->deltar = -1 + rand()%2;
						goalpointer->deltac = -1*(rand()%3 + 1);
						goalpointer->width = 5;
						goalpointer->height = 10 + rand()%16;
						goalpointer->color = colors[rand()%3];
						goalpointer++;
						if (goalpointer == &goals[GOALSSIZE]) {
							goalpointer = goals;
						}
					}
					goalcounter = 0;
				}
				//control mechanism
				if (KEY_DOWN_NOW(BUTTON_A) && !LAST_A && lastspeed) {
					drop = 1;
					mainChar.deltar = 30;
					if (!tutorialdoneA) {
						drawString(8, 0, "PRESS A TO SPEED DROP", BLACK);	
						tutorialdoneA = 1;
					}
				}
				if (KEY_DOWN_NOW(BUTTON_B) && !LAST_B && lastspeed) {
					mainChar.color = colors[nextcolor];
					nextcolor++;
					if (nextcolor == 3) {
						nextcolor = 0;
					}
					if (!tutorialdoneB) {
						drawString(16,0, "PRESS B TO CHANGE COLORS", BLACK);	
						tutorialdoneB = 1;
					}
				}
				//update gravity
				if (framecounter >= 8) {
					if (!drop) {
						mainChar.deltar = mainChar.deltar + GRAVITY;
					}
					framecounter = 0;
				}
				//update objects
				for (int i = 0; i < GOALSSIZE; i++) {
					if (goals[i].set) {
						updateGoal(&goals[i]);
					}
				}
				updateChar(&mainChar, goals);
				//drawing
				for (int i = 0; i < GOALSSIZE; i++) {
					oldcur = oldgoals + i;
					if (oldcur->set) {
						drawRect(oldcur->row,
								oldcur->col,
								oldcur->width,
								oldcur->height,
								BLACK);
					}
				}
				for (int i = 0; i < GOALSSIZE; i++) {
					cur = goals + i;
					if (cur->set && cur->color != BLACK) {	
						drawRect(cur->row,
								cur->col,
								cur->width,
								cur->height,
								cur->color);
					}
				}
				drawRect(oldChar.row, oldChar.col, oldChar.size, oldChar.size, BLACK);
				drawRect(mainChar.row, mainChar.col, mainChar.size, mainChar.size, mainChar.color);	
				drawHollowRect(mainChar.row, mainChar.col, mainChar.size, mainChar.size, WHITE);	
				break;
			case END_SCENE:	
				fillScreen(BLACK);
				drawString(0,0, "GAMEOVER", WHITE);
				state = END_SCENE_NODRAW;
				break;
			case END_SCENE_NODRAW:
				if (KEY_DOWN_NOW(BUTTON_SELECT) && !LAST_SELECT)
					state = START_SCENE;
				if (KEY_DOWN_NOW(BUTTON_START) && !LAST_START)
					state = MAIN_SCENE_SETUP;
				break;
		}

		//check last button
		LAST_A = KEY_DOWN_NOW(BUTTON_A); 
		LAST_B = KEY_DOWN_NOW(BUTTON_B); 
		LAST_SELECT = KEY_DOWN_NOW(BUTTON_SELECT); 
		LAST_START = KEY_DOWN_NOW(BUTTON_START);
		//LAST_RIGHT = KEY_DOWN_NOW(BUTTON_RIGHT);
		//LAST_LEFT = KEY_DOWN_NOW(BUTTON_LEFT);
		//LAST_UP = KEY_DOWN_NOW(BUTTON_UP);
		//LAST_DOWN = KEY_DOWN_NOW(BUTTON_DOWN);
		//LAST_R = KEY_DOWN_NOW(BUTTON_R);
		//LAST_L = KEY_DOWN_NOW(BUTTON_L);
	}
	//write 0 on top right
	return 0;
}

void updateChar(MAINCHAR *mainChar, GOAL *goals) {
	mainChar->row = mainChar->row + mainChar->deltar;
	mainChar->col = mainChar->col + mainChar->deltac;
	
	//upperbound
	//if (mainChar->row <= 0) {
	//	mainChar->row = 0;
	//	mainChar->deltar = 0;
	//	framecounter = 0;
	//}
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
	GOAL *cur;
	for (int i = 0; i < GOALSSIZE; i++) {
		cur = goals + i;
		//check topleft
		if (((mainChar->col + mainChar->size) > cur->col && (mainChar->row + mainChar->size) > cur->row && mainChar->col < cur->col && mainChar->row < cur->row)
				|| ((mainChar->col + mainChar->size) > cur-> col && mainChar->row < (cur->row + cur->height) && mainChar->col < cur->col && (mainChar->row + mainChar->size) > (cur->row + cur->height))
				|| (mainChar->col < (cur->col + cur->width) && (mainChar->row + mainChar->size) > cur->row && (mainChar->col + mainChar->size) > (cur->col + cur->width) && mainChar->row < cur->row)
				|| (mainChar->col < (cur->col + cur->width) && mainChar->row < (cur->row + cur->height)&& (mainChar->col + mainChar->size) > (cur->col + cur->width) && (mainChar->row + mainChar->size) > (cur->row + cur->height))
				|| (mainChar->col < cur->col && (mainChar->col+ mainChar->size) > cur->col + cur->width && (((mainChar->row + mainChar->size) > cur->row && mainChar->row < cur->row) || (mainChar->row < (cur->row + cur-> height) && (mainChar->row + mainChar->size) > (cur->row + cur->height))))) {
			if (cur->color == mainChar->color) {
				cur->color = BLACK;	
				score++;
				char buffer[10];
				sprintf(buffer, "%i", score - 1);
				drawString(0, 0, buffer, BLACK);
				sprintf(buffer, "%i", score);
				drawString(0, 0, buffer, WHITE);	
			} else {
				state = END_SCENE;
			}
		}
	}
}

void updateGoal(GOAL *goal) {	
	goal->row = goal->row + goal->deltar;
	goal->col = goal->col + goal->deltac;
	if (goal->col <= 0) {
		goal->set = 0;
	}
	if (goal->row <= 0) {
		goal->row = 0;
		goal->deltar = -goal->deltar;
	}
	if (goal->row > HEIGHTMAX - goal->height + 1) {
		goal->row = HEIGHTMAX - goal->height + 1;
		goal->deltar = -goal->deltar;
	}
}
