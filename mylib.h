typedef unsigned short u16;
#define SCANLINECOUNTER *(volatile u16 *)0x4000006
extern u16 *videoBuffer;
extern const unsigned char fontdata_6x8[122288];

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

//DMA STUFF
typedef struct{
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMAREC;

#define DMA ((volatile DMAREC *)0x040000B0)

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define START_ON_FIFO_EMPTY 0x30000000

//PROTOTYPES
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void drawString(int r, int c, char *str, u16 color);
void drawChar(int r, int c, char ch, u16 color);
void waitForVblank();
