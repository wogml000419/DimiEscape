#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define		LEFT	75
#define		RIGHT	77
#define		UP		72
#define		DOWN	80

HANDLE HND;

void init(void);
void gotoxy(int x, int y);
void titleScreen(void);
void printWithPosition(char str[], int cols, int color, int x, int y);
int main(void)
{
	
	HND = GetStdHandle(STD_OUTPUT_HANDLE);

	init();
	titleScreen();
	printWithPosition("ฐ่ผำวฯทมธ้ พฦนซ ลฐณช ดฉธฃผผฟไ...", strlen("ฐ่ผำวฯทมธ้ พฦนซ ลฐณช ดฉธฃผผฟไ..."), 0x17, 50, 10);
	getchar();
	return 0;
}
void init(void)
{
	COORD C = { 0, 0 };
	//system("mode con: cols=150 lines=40");
	SetConsoleTitleA("DIMI ESCAPE");
	SetConsoleDisplayMode(HND, CONSOLE_FULLSCREEN_MODE, &C); 
}
void titleScreen(void)
{
	puts(""); puts(""); puts(""); 
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกแกแกกกกกแกแกแกกกแกกกกกกกแกกกแกแกแ");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกกกกกแกกกกกแกกกกกแกแกกกแกแกกกกกแกก");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกกกกกแกกกกกแกกกกกแกกกแกกกแกกกกกแกก");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกกกกกแกกกกกแกกกกกแกกกกกกกแกกกกกแกก");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกแกแกกกกกแกแกแกกกแกกกกกกกแกกกแกแกแ");
	puts("");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกแกแกแกกกแกแกแกแกกกแกแกแกแกกกกกแกแกกกกกแกแกแกกกกกแกแกแกแ");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกกกกกกกกกแกกกกกกกกกแกกกกกแกกกแกกกกกแกกกแกกกกกแกกกแกกกกกก");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกแกแกแกกกแกแกแกแกกกแกกกกกกกกกแกแกแกแกกกแกแกแกกกกกแกแกแกแ");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกกกกกกกกกกกกกกกแกกกแกกกกกแกกกแกกกกกแกกกแกกกกกกกกกแกกกกกก");
	puts("กกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกกแกแกแกแกกกแกแกแกแกกกแกแกแกแกกกแกกกกกแกกกแกกกกกกกกกแกแกแกแ");
}
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(HND, pos);
}
void printWithPosition(char str[], int cols, int color, int x, int y)
{
	int j;
	COORD POS = { x, y };
	SetConsoleTextAttribute(HND, color);
	gotoxy(x , y);
	printf("%s", str);
	SetConsoleTextAttribute(HND, 0x07);
}