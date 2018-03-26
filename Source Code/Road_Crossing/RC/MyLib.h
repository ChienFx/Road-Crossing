#ifndef MyLib_h
#define MyLib_h
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <thread>

using namespace std;

#define MOVE_STEP		1
#define MOVE_DISTANCE	5 // khoang cach giua 2 xe (tinh theo toa do)

#define NUM_ROWS	14
#define NUM_COLS	60

#define WIDE_RIGHT  24
#define WIDE_DOWN   3

//curcor: 8x16 px
#define HEIGHT		(NUM_ROWS + WIDE_DOWN) * 16
#define WIDTH		(NUM_COLS + WIDE_RIGHT)* 8


#define START_POINT_ROW		1
#define START_POINT_COL		0

#define COMMUNICATE_X		NUM_COLS + 2
#define COMMUNICATE_Y		11

#define FONT_SIZE_SMALL		18
#define FONT_SIZE_NORMAL	24
#define FONT_SIZE_LARGE		30

#define SPEED_EASY			180
#define SPEED_NORMAL		100
#define SPEED_HARD			20

#define COUNTER_EASY		10
#define COUNTER_NORMAL		15
#define COUNTER_HARD		20

#define KEY_LEFT	256 + 75
#define KEY_RIGHT	256 + 77
#define KEY_UP		256 + 72
#define KEY_DOWN	256 + 80

#define CONFIRM_CODE			"1612052_RC"

#define PTH_SAVE				"SAVE/"
#define PTH_SOUND_PEOPLE_CRASH	"SOUND/SOUND_PEOPLE_OHNO.wav"
#define PTH_SOUND_BIRD_CRASH	"SOUND/SOUND_BIRD_CRASH.wav"
#define PTH_SOUND_CAR_CRASH		"SOUND/SOUND_CAR_CRASH.wav"
#define PTH_SOUND_DINO_CRASH	"SOUND/SOUND_DINO_CRASH.wav"
#define PTH_SOUND_TRUCK_CRASH	"SOUND/SOUND_TRUCK_CRASH.wav"
#define PTH_SOUND_BEEP			"SOUND/SOUND_BEEP.wav"
#define PTH_SOUND_BACKGROUND	"SOUND/SOUND_BACKGROUND.wav"
#define PTH_SOUND_WIN			"SOUND/SOUND_WIN.wav"
#define PTH_SOUND_GAMEOVER		"SOUND/SOUND_GAMEOVER.wav"

#define CO_DEFAULT		7
#define CO_HIGHLIGHT	11
#define CO_TITLE		236
#define CO_TEXTSCAN		10
#define CO_CAR			34  //Green back
#define CO_TRUCK		119	//Dark Red back
#define CO_BIRD			204	//Grey back
#define CO_DINO			85  //Violet back
#define CO_PEOPLE		14	//yello
#define CO_PEOPLE_DEAD	222


//Define character
#define CH_WALL			'#'
#define CH_PEOPLE		'Y'
#define CH_BIRD			'B'
#define CH_TRUCK		'T'
#define CH_CAR			'C'
#define CH_DINO			'D'

enum MOVE_WAY
{
	E_STOP, E_UP, E_DOWN, E_LEFT,E_RIGHT
};
enum SOUND_MODE
{
	E_SOUND_NULL,
	E_SOUND_LOOP,
	E_SOUND_SINGLE
};
enum ModeGame
{
	E_EASY,
	E_NORMAL,
	E_HARD
};
static HANDLE ConsoleHandle = NULL;
static CHAR_INFO ConsoleBuffer[NUM_COLS * NUM_ROWS] = { 0 };
static char WriteBuffer[NUM_COLS * NUM_ROWS] = { 0 };

void Common_Init();
void SetFontSize(int mSize);
void ShowCursor(bool show);

//Di chuyển con trỏ tới vị trí (x, y)
void GotoXY(int x, int y);

// Hàm tô màu.
void TextColor(int x);

//Thay đổi kích thước console 
void ResizeConsole(int width, int height);

void CleanScreen();

void CleanCommunicateArea();

bool MyPlaySound(const char* path);

bool MyPlaySound(bool sound_on,const char* path, int sound_mode);

void DrawWall();

int MenuStart(bool sound_mode);

int MenuGameOut(bool win, bool sound_mode);

#endif