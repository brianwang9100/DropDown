#include "mylib.h"
#include "ground.h"
#include "startscene.h"
#include "endscene.h"
#define HEIGHTMAX 149
#define GRAVITY 1
#define GOALSSIZE 3
extern u16 *videoBuffer;

typedef struct {
	int row;
	int col;
	int deltar;
	int deltac;
	int size;
	u16 color;
} MAINCHAR;

typedef struct {
	int set;
	int row;
	int col;
	int deltar;
	int deltac;
	int width;
	int height;
	u16 color;
} GOAL;

typedef GOAL COLORBLOCK;

enum GBAState {
	START_SCENE,
	START_SCENE_NODRAW,
	MAIN_SCENE_SETUP,
	MAIN_SCENE,
	END_SCENE,
	END_SCENE_NODRAW
};

int main(void);
void updateChar(MAINCHAR *mainChar, GOAL *goals);
void updateGoal(GOAL *goal);
