#define _WIN32_WINNT 0x0601
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define		LEFT	75
#define		RIGHT	77
#define		UP		72
#define		DOWN	80
#define		ENTER	13
#define		SPACE	32
#define		ESC		27

HANDLE HND;
int CONSOLE_WIDTH;

void init(void);
void gotoxy(int x, int y);
void printWithPosition(char str[], int color, int x, int y, int isCenterAlign);
int titleScreen(void);
int inGame(char mapName[]);
int main(void)//@ = 플레이어, # = 벽, ? = 조사 가능 공간, * - 오브젝트
{
	char *rooms[3] = { "exit", "dormitoryRoom", "dormitoryLeftHall" };
	int roomIndex = 1;
	FILE *saveFile = fopen("save", "rb");

	init();
	if (titleScreen() == 0)
		return 0;
	if (saveFile != NULL)
	{
		fscanf(saveFile, "%d", &roomIndex);
		fclose(saveFile);
	}
	while (1)
	{
		saveFile = fopen("save", "wb");
		fprintf(saveFile, "%d", roomIndex);
		fclose(saveFile);
		roomIndex = inGame(rooms[roomIndex]);
		if (roomIndex == 0)
			break;
	}
	
	return 0;
}
void init(void)
{
	COORD C = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO INFO;
	CONSOLE_CURSOR_INFO CINFO = { 1, 0 };
	HND = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(HND, &CINFO);
	SetConsoleTitleA("DIMI ESCAPE");
 	SetConsoleDisplayMode(HND, CONSOLE_FULLSCREEN_MODE, &C);
	GetConsoleScreenBufferInfo(HND, &INFO);
	INFO.dwSize.Y = INFO.srWindow.Bottom + 1;
	SetConsoleScreenBufferSize(HND, INFO.dwSize);
	CONSOLE_WIDTH = INFO.dwSize.X;
}
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(HND, pos);
}
void printWithPosition(char str[], int color, int x, int y, int CenterAlign)
{
	SetConsoleTextAttribute(HND, color);
	if (CenterAlign == 0)
		gotoxy(x, y);
	else
		gotoxy((CONSOLE_WIDTH - strlen(str)) / 2, y);
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
		printWithPosition("■■■■　■■■　　■■　　■■■　　■■■", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 16, 0);
		printWithPosition("■　　　　　■　　■　　■　■　　■　　■　", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 17, 0);
		printWithPosition("■■■■　　■　　■■■■　■■■　　　■　", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 18, 0);
		printWithPosition("　　　■　　■　　■　　■　■　■　　　■　", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 19, 0);
		printWithPosition("■■■■　　■　　■　　■　■　　■　　■　", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 20, 0);

		printWithPosition("■■■■　■　　■　■■■　■■■", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 16, 0);
		printWithPosition("■　　　　■　　■　　■　　　■　", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 17, 0);
		printWithPosition("■■■■　　■■　　　■　　　■　", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 18, 0);
		printWithPosition("■　　　　■　　■　　■　　　■　", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 19, 0);
		printWithPosition("■■■■　■　　■　■■■　　■　", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 20, 0);
		ch = _getch();
		if (-32 == ch || 0 == ch)
			ch = _getch();
		if (LEFT == ch || RIGHT == ch)
			flag = !flag;
		else if (ch)
			return flag;
	}
}
int inGame(char mapName[])
{
	static char player = 'v';
	static int xface = 0, yface = 1, doorIndex = -1;
	FILE *mapFile = fopen(mapName, "rt");
	FILE *mapInfoFile;
	FILE *mapTextFile;
	FILE *mapDoorFile;
	char *mapNameCopy = (char*)calloc(30, sizeof(char));
	char **map;
	char **texts;
	char ***info;
	char ch;
	int *doorInfo;
	int mapXSize, mapYSize, x, y, i, move, textLineNum, textIndex, mapInfoNum, doorNum, retRoomIndex, px = -1, py = -1;
	strcpy(mapNameCopy, mapName);
	mapInfoFile = fopen(strcat(mapNameCopy, "Info"), "rt");
	strcpy(mapNameCopy, mapName);
	mapTextFile = fopen(strcat(mapNameCopy, "Texts"), "rt");
	strcpy(mapNameCopy, mapName);
	mapDoorFile = fopen(strcat(mapNameCopy, "Doors"), "rt");
	free(mapNameCopy);

	system("cls");

	//맵 파일 불러오기 시작
	fscanf(mapFile, "%d %d\n", &mapYSize, &mapXSize);

	map = (char**)calloc(sizeof(char*), mapYSize);
	info = (char***)calloc(sizeof(char**), mapYSize);
	for (y = 0; y < mapYSize; y++)
	{
		map[y] = (char*)calloc(sizeof(char), mapXSize + 1);
		info[y] = (char**)calloc(sizeof(char*), mapXSize);
		for (x = 0; x < mapXSize; x++)
			info[y][x] = NULL;
	}

	for (y = 0; y < mapYSize; y++)
	{
		for (x = 0; x < mapXSize + 1; x++)
		{
			fscanf(mapFile, "%c", &ch);
			if (ch == '<' || ch == '>' || ch == 'v' || ch == '^')
			{
				px = x;
				py = y;
				player = ch;
				switch (ch)
				{
				case'<':
					xface = -1;
					yface = 0;
					break;
				case '>':
					xface = 1;
					yface = 0;
				case 'v':
					xface = 0;
					yface = 1;
				case '^':
					xface = 0;
					yface = -1;
				}
			}
			if (x == mapXSize)
				map[y][x] = 0;
			else
				map[y][x] = ch;
		}
	}
	fclose(mapFile);
	//맵 파일 다 불러옴
	//텍스트 파일 불러오기 시작
	fscanf(mapTextFile, "%d", &textLineNum);
	texts = (char**)calloc(textLineNum, sizeof(char*));
	for (x = 0; x < textLineNum; x++)
	{
		fscanf(mapTextFile, "%d", &textIndex);
		texts[textIndex] = (char*)calloc(100, sizeof(char));
		fgets(texts[textIndex], 100, mapTextFile);
	}
	fclose(mapTextFile);
	//텍스트 파일 다 불러옴
	//맵 정보 파일 불러오기 시작
	fscanf(mapInfoFile, "%d", &mapInfoNum);
	for (i = 0; i < mapInfoNum; i++)
	{
		fscanf(mapInfoFile, "%d, %d", &y, &x);
		info[y][x] = (char*)calloc(30, sizeof(char));
		fgets(info[y][x], 30, mapInfoFile);
	}
	fclose(mapInfoFile);
	//맵 정보 파일 불러오기 끝
	//문 정보 파일 불러오기 시작
	fscanf(mapDoorFile, "%d", &doorNum);
	doorInfo = (int*)calloc(doorNum * 2, sizeof(int));
	for (i = 0; i < doorNum; i++)
		fscanf(mapDoorFile, "%d, %d", &doorInfo[i * 2], &doorInfo[i * 2 + 1]);
	fclose(mapDoorFile);
	//문 정보 파일 불러오기 끝
	if (doorIndex != -1)
	{
		py = doorInfo[doorIndex * 2];
		px = doorInfo[doorIndex * 2 + 1];
	}
	if (px == -1 || py == -1)
	{
		if (doorIndex == -1)
			doorIndex = 0;
		py = doorInfo[doorIndex * 2];
		px = doorInfo[doorIndex * 2 + 1];
	}
	map[py][px] = player;
	for (y = 0; y < mapYSize; y++)
		printWithPosition(map[y], 0x07, 0, y + 1, 1);
	printWithPosition(&player, 0x0d, (CONSOLE_WIDTH - mapXSize) / 2 + px, py + 1, 0);
	while (1)
	{
		ch = _getch();
		if (ch == -32 || ch == 0)
			ch = _getch();
		switch (ch)
		{
		case LEFT:
			player = '<';
			xface = -1; yface = 0;
			move = 1;
			break;
		case RIGHT:
			player = '>';
			xface = 1; yface = 0;
			move = 1;
			break;
		case UP:
			player = '^';
			xface = 0; yface = -1;
			move = 1;
			break;
		case DOWN:
			player = 'v';
			xface = 0; yface = 1;
			move = 1;
			break;
		case ENTER:
		case SPACE:
			move = 0;
			break;
		}

		if (ch == ESC)
		{
			
			retRoomIndex = 0;
			break;
		}
		printWithPosition("                                                                    ", 0x07, 0, mapYSize + 2, 1);
		if (move && map[py + yface][px + xface] == ' ')
		{
			map[py][px] = ' ';
			printWithPosition(map[py], 0x07, 0, py + 1, 1);
			py += yface;
			px += xface;
			if (info[py][px] != NULL)
			{
				if (strncmp(info[py][px], " door", 5) == 0)
				{
					sscanf(info[py][px], " door %d %d", &retRoomIndex, &doorIndex);
					map[py][px] = ' ';
					break;
				}
			}
		}
		else if (!move && info[py + yface][px + xface] != NULL)
		{
			if (strncmp(info[py + yface][px + xface], " text", 5) == 0)
			{
				sscanf(info[py + yface][px + xface], " text %d", &textIndex);
				printWithPosition(texts[textIndex], 0x07, 0, mapYSize + 2, 1);
			}
		}
		map[py][px] = player;
		printWithPosition(map[py], 0x07, 0, py + 1, 1);
		printWithPosition(&player, 0x0d, (CONSOLE_WIDTH - mapXSize) / 2 + px, py + 1, 0);
	}
	//맵파일 불러오기 시작
	mapFile = fopen(mapName, "wt");
	fprintf(mapFile, "%d %d\n", mapYSize, mapXSize);
	for (y = 0; y < mapYSize; y++)
		fprintf(mapFile, "%s\n", map[y]);
	fclose(mapFile);
	//맵파일 불러오기 끝
	for (y = 0; y < mapYSize; y++)
		free(map[y]);
	free(map);

	for (x = 0; x < textLineNum; x++)
		free(texts[x]);
	free(texts);

	for (y = 0; y < mapYSize; y++)
	{
		for (x = 0; x < mapXSize; x++)
			if (info[y][x] != NULL)
				free(info[y][x]);
		free(info[y]);
	}
	free(info);

	free(doorInfo);

	return retRoomIndex;
}
//y, x door [roomIndex] [doorIndex]
//y, x inve [fileName]
//y, x text [textIndex]
//y, x esca [endingName]

//To Do:
//인벤토리 구현한 다음
//엔딩을 구현하자
