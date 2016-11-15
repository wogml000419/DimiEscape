#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define		LEFT	75
#define		RIGHT	77
#define		UP		72
#define		DOWN	80
#define		ENTER	13
#define		ESC		27

HANDLE HND;
int CONSOLE_WIDTH;

void init(void);
void gotoxy(int x, int y);
void printWithPosition(char str[], int color, int x, int y, int isCenterAlign);
int titleScreen(void);
int inGame(char mapName[], int door);
int main(void)//@ = �÷��̾�, # = ��, ? = ���� ���� ����, * - ������Ʈ
{
	char *rooms[1] = { "dormitoryRoom" };
	int roomIndex = 0;

	init();
	if (titleScreen() == 0)
		return 0;
	
	inGame(rooms[roomIndex], 1);
	_getch();
	return 0;
}
void init(void)
{
	COORD C = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO INFO; 
	HND = GetStdHandle(STD_OUTPUT_HANDLE);
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
	COORD POS = { x, y };
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
	printWithPosition("���ᡡ�����ᡡ�ᡡ�����ᡡ����", 0x07, 0, 3, 1);
	printWithPosition("�ᡡ���ᡡ���ᡡ����ᡡ��ᡡ���ᡡ", 0x07, 0, 4, 1);
	printWithPosition("�ᡡ���ᡡ���ᡡ���ᡡ�ᡡ�ᡡ���ᡡ", 0x07, 0, 5, 1);
	printWithPosition("�ᡡ���ᡡ���ᡡ���ᡡ�����ᡡ���ᡡ", 0x07, 0, 6, 1);
	printWithPosition("���ᡡ�����ᡡ�ᡡ�����ᡡ����", 0x07, 0, 7, 1);

	printWithPosition("����ᡡ����ᡡ����ᡡ����ᡡ�����ᡡ�������", 0x07, 0, 9, 1);
	printWithPosition("�ᡡ�������ᡡ�������ᡡ���ᡡ�ᡡ���ᡡ�ᡡ���ᡡ�ᡡ����", 0x07, 0, 10, 1);
	printWithPosition("����ᡡ����ᡡ�ᡡ����������ᡡ���ᡡ�������", 0x07, 0, 11, 1);
	printWithPosition("�ᡡ�������������ᡡ�ᡡ���ᡡ�ᡡ���ᡡ�ᡡ�������ᡡ����", 0x07, 0, 12, 1);
	printWithPosition("����ᡡ����ᡡ����ᡡ�ᡡ���ᡡ�ᡡ�����������", 0x07, 0, 13, 1);

	while (1)
	{
		printWithPosition("����ᡡ���ᡡ����ᡡ�����ᡡ������", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 16, 0);
		printWithPosition("�ᡡ���������ᡡ���ᡡ���ᡡ�ᡡ���ᡡ���ᡡ", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 17, 0);
		printWithPosition("����ᡡ���ᡡ������ᡡ���ᡡ�����ᡡ", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 18, 0);
		printWithPosition("�������ᡡ���ᡡ���ᡡ���ᡡ�ᡡ�ᡡ�����ᡡ", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 19, 0);
		printWithPosition("����ᡡ���ᡡ���ᡡ���ᡡ�ᡡ���ᡡ���ᡡ", colors[flag], (CONSOLE_WIDTH / 2 - 45) / 2, 20, 0);

		printWithPosition("����ᡡ�ᡡ���ᡡ���ᡡ����", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 16, 0);
		printWithPosition("�ᡡ�������ᡡ���ᡡ���ᡡ�����ᡡ", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 17, 0);
		printWithPosition("����ᡡ����ᡡ�����ᡡ�����ᡡ", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 18, 0);
		printWithPosition("�ᡡ�������ᡡ���ᡡ���ᡡ�����ᡡ", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 19, 0);
		printWithPosition("����ᡡ�ᡡ���ᡡ���ᡡ���ᡡ", colors[!flag], (CONSOLE_WIDTH / 2 - 35) / 2 + CONSOLE_WIDTH / 2, 20, 0);
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

int inGame(char mapName[], int door)
{
	static char player = 'v';
	static int xface = 0, yface = 1;
	FILE *mapFile = fopen(mapName, "rt");
	FILE *mapInfoFile;
	FILE *mapTextFile;
	char *mapNameCopy = (char*)calloc(30, sizeof(char));
	char **map;
	char **texts;
	char ***info;
	char ch;
	int mapXSize, mapYSize, x, y, i, move, textLineNum, textIndex, mapInfoNum, px = 3, py = 7;
	strcpy(mapNameCopy, mapName);
	mapInfoFile = fopen(strcat(mapNameCopy, "Info"), "rt");
	strcpy(mapNameCopy, mapName);
	mapTextFile = fopen(strcat(mapNameCopy, "Texts"), "rt");
	free(mapNameCopy);

	system("cls");
	//�� ���� �ҷ����� ����
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
			}
			if (x == mapXSize)
				map[y][x] = 0;
			else
				map[y][x] = ch;
		}	
	}
	fclose(mapFile);
	//�� ���� �� �ҷ���
	//�ؽ�Ʈ ���� �ҷ����� ����
	fscanf(mapTextFile, "%d", &textLineNum);
	texts = (char**)calloc(textLineNum, sizeof(char*));
	for (x = 0; x < textLineNum; x++)
	{
		fscanf(mapTextFile, "%d", &textIndex);
		texts[textIndex] = (char*)calloc(100, sizeof(char));
		fgets(texts[textIndex], 100, mapTextFile);
	}
	fclose(mapTextFile);
	//�ؽ�Ʈ ���� �� �ҷ���
	//�� ���� ���� �ҷ����� ����
	fscanf(mapInfoFile, "%d", &mapInfoNum);
	for (i = 0; i < mapInfoNum; i++)
	{
		fscanf(mapInfoFile, "%d, %d", &y, &x);
		info[y][x] = (char*)calloc(30, sizeof(char));
		fgets(info[y][x], 30, mapInfoFile);
	}
	fclose(mapInfoFile);
	//�� ���� ���� �ҷ����� ��
	map[py][px] = player;
	for (y = 0; y < mapYSize; y++)
		printWithPosition(map[y], 0x07, 0, y + 1, 1);

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
			move = 0;
			break;
		}

		if (ch == ESC)
			break;
		if (move && map[py + yface][px + xface] == ' ')
		{
			map[py][px] = ' ';
			printWithPosition(map[py], 0x07, 0, py + 1, 1);
			py += yface;
			px += xface;
		}
		else if (!move && info[py + yface][px + xface] != NULL)
		{
			if (strncmp(info[py + yface][px + xface], "text", 4))
			{
				sscanf(info[py + yface][px + xface], "text %d", &textIndex);
				printWithPosition(texts[textIndex], 0x07, 0, mapYSize + 2, 1);
			}
		}
		map[py][px] = player;
		printWithPosition(map[py], 0x07, 0, py + 1, 1);
		
	}
	//������ �ҷ����� ����
	mapFile = fopen(mapName, "wt");
	fprintf(mapFile, "%d %d\n", mapYSize, mapXSize);
	for (y = 0; y < mapYSize; y++)
		fprintf(mapFile, "%s\n", map[y]);
	fclose(mapFile);
	//������ �ҷ����� ��
	for (y = 0; y < mapYSize; y++)
		free(map[y]);
	free(map);

	for (x = 0; x < textLineNum; x++)
		free(texts[x]);
	free(texts);
	return 1;
}
//y, x door [roomIndex]
//y, x inve [fileName]
//y, x text [textIndex]
//�÷��̾� ��ǥ ������ ���� �����ϸ�
//����� �ʿ��� �������� �����ڰ�
//��ǥ�� ������ ������
//���� �̵��ϸ� �÷��̾ ���� �ʿ��� ���ְ�
//�̵��� ���� �� ������
//���� �� ������ �� �� ��ǥ�� �÷��̾ ������ ����

//�ؽ�Ʈ ������ �ϳ� �� �����
//�ű�ٰ� �� �� �� ��������
