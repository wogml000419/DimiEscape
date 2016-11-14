#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define		LEFT	75
#define		RIGHT	77
#define		UP		72
#define		DOWN	80
#define		ENTER	13
#define		ESC		27

#define		COLSIZE	158
HANDLE HND;

void init(void);
void gotoxy(int x, int y);
void printWithPosition(char str[], int color, int x, int y, int isCenterAlign);
int titleScreen(void);
int inGame(char mapName[]);
int main(void)//@ = 플레이어, # = 벽, ? = 조사 가능 공간, * - 오브젝트
{
	HND = GetStdHandle(STD_OUTPUT_HANDLE);

	init();
	if (titleScreen() == 0)
		return 0;
	
	inGame("dormitoryRoom");
	_getch();
	return 0;
}
void init(void)
{
	COORD C = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO INFO; 
	SetConsoleTitleA("DIMI ESCAPE");
	SetConsoleDisplayMode(HND, CONSOLE_FULLSCREEN_MODE, &C); 
	GetConsoleScreenBufferInfo(HND, &INFO);
	INFO.dwSize.Y = INFO.srWindow.Bottom + 1;
	SetConsoleScreenBufferSize(HND, INFO.dwSize);
	printf("%d", INFO.dwSize.X);
}
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(HND, pos);
}
void printWithPosition(char str[], int color, int x, int y, int CenterAlign)
{
	COORD POS = { x, y }, SIZE = GetLargestConsoleWindowSize(HND);
	SetConsoleTextAttribute(HND, color);
	if (CenterAlign == 0)
		gotoxy(x, y);
	else
		gotoxy((SIZE.X - strlen(str)) / 2, y);
	printf("%s", str);
	SetConsoleTextAttribute(HND, 0x07);
}
int titleScreen(void)
{
	int flag = 1;
	char ch;
	int colors[2] = { 0x07, 0x70 };
	printWithPosition("■■■　　■■■　■　　　■　■■■", 0x07, 0, 3, 1);
	printWithPosition("■　　■　　■　　■■　■■　　■　", 0x07, 0, 4, 1);
	printWithPosition("■　　■　　■　　■　■　■　　■　", 0x07, 0, 5, 1);
	printWithPosition("■　　■　　■　　■　　　■　　■　", 0x07, 0, 6, 1);
	printWithPosition("■■■　　■■■　■　　　■　■■■", 0x07, 0, 7, 1);

	printWithPosition("■■■■　■■■■　■■■■　　■■　　■■■　　■■■■", 0x07, 0, 9, 1);
	printWithPosition("■　　　　■　　　　■　　■　■　　■　■　　■　■　　　", 0x07, 0, 10, 1);
	printWithPosition("■■■■　■■■■　■　　　　■■■■　■■■　　■■■■", 0x07, 0, 11, 1);
	printWithPosition("■　　　　　　　■　■　　■　■　　■　■　　　　■　　　", 0x07, 0, 12, 1);
	printWithPosition("■■■■　■■■■　■■■■　■　　■　■　　　　■■■■", 0x07, 0, 13, 1);

	while (1)
	{
		printWithPosition("■■■■　■■■　　■■　　■■■　　■■■", colors[flag], (COLSIZE / 2 - 45) / 2, 16, 0);
		printWithPosition("■　　　　　■　　■　　■　■　　■　　■　", colors[flag], (COLSIZE / 2 - 45) / 2, 17, 0);
		printWithPosition("■■■■　　■　　■■■■　■■■　　　■　", colors[flag], (COLSIZE / 2 - 45) / 2, 18, 0);
		printWithPosition("　　　■　　■　　■　　■　■　■　　　■　", colors[flag], (COLSIZE / 2 - 45) / 2, 19, 0);
		printWithPosition("■■■■　　■　　■　　■　■　　■　　■　", colors[flag], (COLSIZE / 2 - 45) / 2, 20, 0);

		printWithPosition("■■■■　■　　■　■■■　■■■", colors[!flag], (COLSIZE / 2 - 35) / 2 + COLSIZE / 2, 16, 0);
		printWithPosition("■　　　　■　　■　　■　　　■　", colors[!flag], (COLSIZE / 2 - 35) / 2 + COLSIZE / 2, 17, 0);
		printWithPosition("■■■■　　■■　　　■　　　■　", colors[!flag], (COLSIZE / 2 - 35) / 2 + COLSIZE / 2, 18, 0);
		printWithPosition("■　　　　■　　■　　■　　　■　", colors[!flag], (COLSIZE / 2 - 35) / 2 + COLSIZE / 2, 19, 0);
		printWithPosition("■■■■　■　　■　■■■　　■　", colors[!flag], (COLSIZE / 2 - 35) / 2 + COLSIZE / 2, 20, 0);
		ch = _getch();
		if (-32 == ch || 0 == ch)
		{
			ch = _getch();
			if (LEFT == ch || RIGHT == ch)
				flag = !flag;
		}
		else if (ENTER == ch)
			return flag;
	}
}

int inGame(char mapName[])
{
	FILE *mapFile = fopen(mapName, "rt");
	char **map;
	char ch;
	int mapXSize, mapYSize, x, y;

	system("cls");
	fscanf(mapFile, "%d %d\n", &mapYSize, &mapXSize);
	map = (char**)calloc(sizeof(char*), mapYSize);
	for (y = 0; y < mapYSize; y++)
		map[y] = (char*)calloc(sizeof(char), mapXSize + 1);
	for (y = 0; y < mapYSize; y++)
	{
		for (x = 0; x < mapXSize + 1; x++)
		{
			fread(&ch, sizeof(char), 1, mapFile);
			if (x == mapXSize)
				map[y][x] = 0;
			else
				map[y][x] = ch;
		}	
	}
	for (y = 0; y < mapYSize; y++)
		printWithPosition(map[y], 0x07, 0, y + 1, 1);
	return 1;
}