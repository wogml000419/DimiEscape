#define _WIN32_WINNT 0x0601
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define		LEFT	75
#define		RIGHT	77
#define		UP		72
#define		DOWN	80
#define		ENTER	13
#define		SPACE	32
#define		ESC		27

#define		ITEMNUM	2

HANDLE HND;
int CONSOLE_WIDTH;
char *items[2] = { "사복", "휴대폰" };
int itemObtained[2] = { 0 ,    0 };
void init(void);
void gotoxy(int x, int y);
void printWithPosition(char str[], int color, int x, int y, int isCenterAlign);
void clearText(int y);
int titleScreen(void);
void clearGame(char *rooms[], int roomNum);
void intro(void);
int inGame(char mapName[]);
int HospitalEnd();
int main(void)//@ = 플레이어, # = 벽, ? = 조사 가능 공간, * - 오브젝트
{
	char *rooms[5] = { "exit", "dormitoryRoom", "dormitoryLeftHall", "dormitoryCenter", "dormitoryRightHall" };
	int roomIndex = 1, tReturn;
	FILE *saveFile = fopen("save", "rb");

	init();
	tReturn = titleScreen();
	if (tReturn == 0)
		return 0;
	else if (tReturn == -1)
	{
		clearGame(rooms, 5);
		intro();
	}
	if (saveFile != NULL)
	{
		fread(&roomIndex, sizeof(int), 1, saveFile);
		fread(itemObtained, sizeof(int), ITEMNUM, saveFile);
		fclose(saveFile);
	}
	while (1)
	{
		saveFile = fopen("save", "wb");
		fwrite(&roomIndex, sizeof(int), 1, saveFile);
		fclose(saveFile);
		roomIndex = inGame(rooms[roomIndex]);
		if (roomIndex == 0)
			break;
		else if (roomIndex == -1)
		{
			clearGame(rooms, 5);
			return 0;
		}
	}
	saveFile = fopen("save", "ab");
	fwrite(itemObtained, sizeof(int), ITEMNUM, saveFile);
	fclose(saveFile);
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
		{
			if (flag == 0)
				return 0;
			else
				break;
		}
	}
	system("cls");
	while (1)
	{
		printWithPosition("　■　　■　　■■■　　■　　　■　■■■　■", colors[!flag], 0, 1, 1);
		printWithPosition("■■■　■　■　　　■　■■■■■　■　　　■", colors[!flag], 0, 2, 1);
		printWithPosition("　■　　■　　■■■　　■　　　■　■■■　■", colors[!flag], 0, 3, 1);
		printWithPosition("　■　■■　■■■■■　■■■■■　■　　■■", colors[!flag], 0, 4, 1);
		printWithPosition("■　■　■　　■■■　　■■■■■　■　　　■", colors[!flag], 0, 5, 1);
		printWithPosition("■　■　■　　■■■　　　　■　　　■■■　■", colors[!flag], 0, 6, 1);
	
		printWithPosition("　■　　■　　■　　■　　■　　■", colors[flag], 0, 8, 1);
		printWithPosition("■　■　■　■　■　■　■　■　■", colors[flag], 0, 9, 1);
		printWithPosition("■　■　■　■　■■■　■　■■■", colors[flag], 0, 10, 1);
		printWithPosition("■　■　■　■　■　■　■　■　■", colors[flag], 0, 11, 1);
		printWithPosition("　■　　■　　■　　■　■　■　■", colors[flag], 0, 12, 1);

		ch = _getch();
		if (ch == -32 || ch == 0)
			ch = _getch();

		if (ch == LEFT || ch == RIGHT || ch == UP || ch == DOWN)
			flag = !flag;
		else if (ch)
		{
			if (flag == 0)
				return -1;
			else
				return 1;
		}
	}
}
void clearGame(char *rooms[], int roomNum)
{
	int i, readCnt;
	int tempArr[ITEMNUM] = { 0 };
	FILE *map;
	FILE *mapO;
	FILE *save;
	char str[40];
	char buffer[55];
	for (i = 1; i < roomNum; i++)
	{
		map = fopen(rooms[i], "wt");
		strcpy(str, "Originals/");
		strcat(str, rooms[i]);
		strcat(str, "O.txt");
		mapO = fopen(str, "rt");

		while (1)
		{
			readCnt = fread(buffer, sizeof(char), 50, mapO);
			if (readCnt < 50)
				break;
			fwrite(buffer, sizeof(char), 50, map);
		}
		fwrite(buffer, sizeof(char), readCnt, map);

		fclose(map);
		fclose(mapO);	
	}
	i = 1;
	save = fopen("save", "wb");
	fwrite(&i, sizeof(int), 1, save);
	fwrite(tempArr, sizeof(int), ITEMNUM, save);
	fclose(save);
}
void intro(void)
{
	system("cls");
	printWithPosition("오늘은 전교생이 견학을 가는 날이다.", 0x07, 0, 1, 1);
	_getch();
	printWithPosition("하지만 난 늦잠을 자버렸고,", 0x07, 0, 3, 1);
	_getch();
	printWithPosition("깨어나 보니 학교에는 나밖에 없었다.", 0x07, 0, 5, 1);
	_getch();
	printWithPosition("순간, 지금이 탈디미의 기회라는 생각이 들었고", 0x07, 0, 7, 1);
	_getch();
	printWithPosition("무슨 수를 써서든지 여길 탈출하기로 결심했다.", 0x07, 0, 9, 1);
	_getch();
	system("cls");
}
int inGame(char mapName[])
{
	static char player = 'v';
	static int xface = 0, yface = 1, doorIndex = -1;
	
	FILE *mapFile = fopen(mapName, "rt");
	FILE *mapInfoFile;
	FILE *mapTextFile;
	FILE *mapDoorFile;
	char itemText[30];
	char *mapNameCopy = (char*)calloc(30, sizeof(char));
	char **map;
	char **texts;
	char ***info;
	char ch;
	int *doorInfo;
	int mapXSize, mapYSize, x, y, i, move, textLineNum, textIndex, mapInfoNum, doorNum, retRoomIndex, itemIndex, endIndex, endResult, px = -1, py = -1;
	strcpy(mapNameCopy, mapName);
	mapInfoFile = fopen(strcat(mapNameCopy, "Info"), "rt");
	strcpy(mapNameCopy, mapName);
	mapTextFile = fopen(strcat(mapNameCopy, "Texts"), "rt");
	strcpy(mapNameCopy, mapName);
	mapDoorFile = fopen(strcat(mapNameCopy, "Doors"), "rt");
	free(mapNameCopy);

	system("cls");

	//맵 파일 불러오기 시작
	fscanf(mapFile, "%d %d", &mapYSize, &mapXSize);
	fgetc(mapFile);		//\n없애기
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
			ch = fgetc(mapFile);
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
		clearText(mapYSize + 2);
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
			else if (strncmp(info[py + yface][px + xface], " item", 5) == 0)
			{
				sscanf(info[py + yface][px + xface], " item %d", &itemIndex);
				if (!itemObtained[itemIndex])
				{
					itemObtained[itemIndex] = 1;
					sprintf(itemText, "%s(을)를 얻었다.", items[itemIndex]);
					printWithPosition(itemText, 0x0E, 0, mapYSize + 2, 1);
				}
				else
				{
					sprintf(itemText, "%s(은)는 이미 가져갔다.", items[itemIndex]);
					printWithPosition(itemText, 0x07, 0, mapYSize + 2, 1);
				}
			}
			else if (strncmp(info[py + yface][px + xface], " esca", 5) == 0)
			{
				sscanf(info[py + yface][px + xface], " esca %d", &endIndex);
				switch (endIndex)
				{
				case 0:
					endResult = HospitalEnd();
					break;
				}
				if (endResult == 1)
				{
					retRoomIndex = -1;
					break;
				}
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
void clearText(int y)
{
	int i;
	gotoxy(0, y);
	for (i = 0; i < CONSOLE_WIDTH; i++)
		putchar(' ');
}
int HospitalEnd()
{
	int choise = 0;
	int colors[2] = { 0x07, 0x70 };
	char ch;
	printWithPosition("여기로 떨어지면 며칠동안은 병원에 있을 수 있다.", 0x07, 0, 17, 1);
	_getch();
	clearText(17);
	printWithPosition("그렇지만 많이 아플 것이다.", 0x07, 0, 17, 1);
	_getch();
	clearText(17);
	printWithPosition("어떻게 할까?", 0x07, 0, 17, 1);
	while (1)
	{
		printWithPosition("탈디미를 택한다.", colors[choise], CONSOLE_WIDTH / 2 - 19, 19, 0);
		printWithPosition("건강을 택한다.", colors[!choise], CONSOLE_WIDTH / 2 + 2, 19, 0);
		ch = _getch();
		if (ch == LEFT || ch == RIGHT)
			choise = !choise;
		else if (ch == ENTER || ch == SPACE)
			break;
	}
	clearText(17);
	clearText(19);
	if(choise == 0)
		printWithPosition("이건 아닌 것 같아.", 0x07, 0, 17, 1);
	else 
	{
		system("cls");
		printWithPosition("\"쿵\"", 0x07, 0, 1, 1);
		_getch();
		printWithPosition("다리가 움직이질 않는다.", 0x07, 0, 3, 1);
		_getch();
		if (itemObtained[1])
		{
			printWithPosition("휴대폰으로 119에 전화를 걸었다.", 0x07, 0, 5, 1);
			_getch();
			printWithPosition("생각보다 구급차는 금방 왔고,", 0x07, 0, 7, 1);
			_getch();
			printWithPosition("나는 이틀을 병원에서 보낼 수 있었다.", 0x07, 0, 9, 1);
			_getch();
			printWithPosition("=끝=", 0x07, 0, 11, 1);
		}
		else
		{
			printWithPosition("휴대폰으로 전화를 하려고 했지만, 휴대폰이 생활관에 있다.", 0x07, 0, 5, 1);
			_getch();
			printWithPosition("결국 나는 친구들이 올 때까지 차가운 바닥에 누워있었고,", 0x07, 0, 7, 1);
			_getch();
			printWithPosition("병원에서 깁스만 한 뒤 바로 학교로 돌아왔다.", 0x07, 0, 9, 1);
			_getch();
			printWithPosition("=끝=", 0x07, 0, 11, 1);
		}
	}
	putchar('\n');
	return choise;
}
//y, x door [roomIndex] [doorIndex]
//y, x item [itemIndex]
//y, x text [textIndex]
//y, x esca [endIndex]  (1을 리턴하면 게임 종료, 0은 계속)

