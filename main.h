#include "mylib.h"
#define HEIGHTMAX 149
#define GRAVITY 1
extern u16 *videoBuffer;

typedef struct {
	int row;
	int col;
	int deltar;
	int deltac;
	int size;
	u16 color;
} MAINCHAR;

int main(void);
void updateChar(MAINCHAR *mainChar);
