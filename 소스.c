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
int main(void)
{
	
	HND = GetStdHandle(STD_OUTPUT_HANDLE);

	init();
	titleScreen();
	return 0;
}
void init(void)
{
	COORD C = { 0, 0 };
	system("mode con: cols=150 lines=40");
	SetConsoleTitleA("DIMI ESCAPE");
	SetConsoleDisplayMode(HND, CONSOLE_FULLSCREEN_MODE, &C);
}
void titleScreen(void)
{
	puts(""); puts(""); puts(""); 
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　＝＝＝　　＝＝＝　＝　　　＝　＝＝＝");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　＝　　＝　　＝　　＝＝　＝＝　　＝　");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　＝　　＝　　＝　　＝　＝　＝　　＝　");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　＝　　＝　　＝　　＝　　　＝　　＝　");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　＝＝＝　　＝＝＝　＝　　　＝　＝＝＝");
	puts("");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　＝＝＝＝　＝＝＝＝　＝＝＝＝　　＝＝　　＝＝＝　　＝＝＝＝");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　＝　　　　＝　　　　＝　　＝　＝　　＝　＝　　＝　＝　　　");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　＝＝＝＝　＝＝＝＝　＝　　　　＝＝＝＝　＝＝＝　　＝＝＝＝");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　＝　　　　　　　＝　＝　　＝　＝　　＝　＝　　　　＝　　　");
	puts("　　　　　　　　　　　　　　　　　　　　　　　　　　＝＝＝＝　＝＝＝＝　＝＝＝＝　＝　　＝　＝　　　　＝＝＝＝");
}
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(HND, pos);
}