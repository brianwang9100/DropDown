typedef unsigned short u16;
#define SCANLINECOUNTER *(volatile u16 *)0x4000006
extern u16 *videoBuffer;

//setup
#define REG_DISPCTL *(u16 *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
//COLORS


#define RGB(R,G,B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   RGB(0 , 0 , 0 )
#define WHITE   RGB(31, 31, 31)
#define RED     RGB(31, 0 , 0 )
#define GREEN   RGB(0 , 31, 0 )
#define BLUE    RGB(0 , 0 , 31)
#define YELLOW  RGB(31, 31, 0 )
#define MAGENTA RGB(31, 0 , 31)
#define CYAN    RGB(0 , 31, 31)
#define ORANGE  RGB(31, 15, 0 )
#define BROWN   RGB(18, 9 , 0 )
#define PURPLE  RGB(15, 0 , 15)
#define TEAL    RGB(0 , 15, 15)
#define MAROON  RGB(15, 0 , 0 )
#define GRAY    RGB(15, 15, 15)
#define PINK    RGB(31, 18, 19)
#define LTGRAY	RGB(22, 22, 22)
#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))
//BUTTONS

#define BUTTONS *(volatile unsigned int *)0x4000130
#define BUTTON_A			(1<<0)
#define BUTTON_B			(1<<1)
#define BUTTON_SELECT		(1<<2)
#define BUTTON_START		(1<<3)
#define BUTTON_RIGHT		(1<<4)
#define BUTTON_LEFT			(1<<5)
#define BUTTON_UP			(1<<6)
#define BUTTON_DOWN			(1<<7)
#define BUTTON_R			(1<<8)
#define BUTTON_L			(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)


void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void waitForVblank();
