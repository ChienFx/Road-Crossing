#include "MyLib.h"

void SetFontSize(int mSize)
{
	///set font
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = mSize;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	//cfi.FontWeight = FW_HEAVY;

	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ShowCursor(bool show)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.bVisible = show;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(ConsoleHandle, &cursorInfo);
}
void Common_Init()
{
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo = { 0 };
	GetConsoleScreenBufferInfo(ConsoleHandle, &bufferInfo);

	// Set window and buffer width, order is important buffer must always be >= window
	unsigned int windowWidth = bufferInfo.srWindow.Left + bufferInfo.srWindow.Right;
	bufferInfo.dwSize.X = NUM_COLS + WIDE_RIGHT + START_POINT_COL;
	bufferInfo.srWindow.Right = bufferInfo.srWindow.Left + (NUM_COLS + WIDE_RIGHT + START_POINT_COL - 1);
	if (bufferInfo.dwSize.X > windowWidth)
	{
		SetConsoleScreenBufferSize(ConsoleHandle, bufferInfo.dwSize);
		SetConsoleWindowInfo(ConsoleHandle, TRUE, &bufferInfo.srWindow);
	}
	else
	{
		SetConsoleWindowInfo(ConsoleHandle, TRUE, &bufferInfo.srWindow);
		SetConsoleScreenBufferSize(ConsoleHandle, bufferInfo.dwSize);
	}

	// Set window and buffer height, order is important buffer must always be >= window
	unsigned int windowHeight = bufferInfo.srWindow.Top + bufferInfo.srWindow.Bottom;
	bufferInfo.dwSize.Y = NUM_ROWS + WIDE_DOWN + START_POINT_ROW;
	bufferInfo.srWindow.Bottom = bufferInfo.srWindow.Top + (NUM_ROWS + WIDE_DOWN + START_POINT_ROW - 1);
	if (bufferInfo.dwSize.Y > windowHeight)
	{
		SetConsoleScreenBufferSize(ConsoleHandle, bufferInfo.dwSize);
		SetConsoleWindowInfo(ConsoleHandle, TRUE, &bufferInfo.srWindow);
	}
	else
	{
		SetConsoleWindowInfo(ConsoleHandle, TRUE, &bufferInfo.srWindow);
		SetConsoleScreenBufferSize(ConsoleHandle, bufferInfo.dwSize);
	}

	//Set title
	SetConsoleTitleA("ROAD CROSSING - 1612052 - HCMUS");

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);


	// Hide the cursor
	ShowCursor(false);
	//Set font size
	SetFontSize(FONT_SIZE_LARGE);
}

//Di chuyển con trỏ tới vị trí (x, y)
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x + START_POINT_COL;
	coord.Y = y + START_POINT_ROW;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm tô màu.
void TextColor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void CleanScreen()
{
	for (int i = 1; i < NUM_COLS; i++)
	for (int j = 1; j < NUM_ROWS; j++)
	{
			GotoXY(i, j);
			cout << " ";
	}
}
void DrawWall()
{
	for (int i = 0; i <= NUM_COLS; i++)
	for (int j = 0; j <= NUM_ROWS; j++)
	{
		if (i == 0 || j == 0 || i == NUM_COLS || j == NUM_ROWS)
		{
			//TextColor(CO_DEFAULT);
			TextColor(127);
			GotoXY(i, j);
			cout << char(CH_WALL);
		}
	}
	TextColor(CO_TITLE);
	for (int j = 0; j < NUM_ROWS + WIDE_DOWN - 1; j++)
	{
		GotoXY(COMMUNICATE_X-1, j);
		cout << " ";
		GotoXY(COMMUNICATE_X + WIDE_RIGHT- 3, j);
		cout << " ";
	}

	for (int i = COMMUNICATE_X; i < NUM_COLS + WIDE_RIGHT - 1; i++)
	{
		GotoXY(i, NUM_ROWS + WIDE_DOWN - 2);
		cout << " ";
	}

	TextColor(CO_DEFAULT);
}
void CleanCommunicateArea()
{
	for (int i = COMMUNICATE_X; i < NUM_COLS+WIDE_RIGHT-1; i++)
	for (int j = COMMUNICATE_Y; j < NUM_ROWS+WIDE_DOWN-2; j++)
	{
		GotoXY(i, j);
		cout << " ";
	}
}

bool MyPlaySound(bool sound_on, const char* path, int sound_mode)
{
	if (sound_on)
	{
		#ifndef UNICODE
		#define UNICODE
		#endif
		#ifndef WINDOWS_H
		#define WINDOWS_H
		#endif
		#pragma comment(lib, "winmm.lib")
		wchar_t *L_path = new wchar_t[strlen(path) + 1];

		for (int i = 0; i < strlen(path) + 1; i++)
			L_path[i] = path[i];
		switch (sound_mode)
		{
		case E_SOUND_NULL:
			PlaySound(NULL, NULL, 0);
			break;
		case E_SOUND_LOOP:
			PlaySound(L_path, NULL, SND_LOOP | SND_ASYNC);
			break;
		default:
			PlaySound(L_path, NULL, SND_ASYNC);
		}
	}
	return 1;

}

bool MyPlaySound(const char* path)
{
#ifndef UNICODE
#define UNICODE
#endif
#ifndef WINDOWS_H
#define WINDOWS_H
#endif
#pragma comment(lib, "winmm.lib")
	wchar_t *L_path = new wchar_t[strlen(path) + 1];

	for (int i = 0; i < strlen(path) + 1; i++)
		L_path[i] = path[i];
	return PlaySound(L_path, NULL, SND_APPLICATION);
}

int MenuStart(bool sound)
{
	int i, j;
	CleanScreen();
	DrawWall();

	i = NUM_COLS / 2 - 5;
	j = NUM_ROWS / 2;

	//SetFontSize(FONT_SIZE_LARGE);
	TextColor(12);

	GotoXY(i - 1, j - 3);
	cout << "ROAD CROSSING";
	GotoXY(i - 1, j - 2);
	cout << "     +-+      ";

	//SetFontSize(FONT_SIZE_NORMAL);
	TextColor(CO_DEFAULT);
	i--;
	int c = 0;
	int k = 0;
	do
	{
		if (c == 'W' || c == KEY_UP)//up
			k--;
		else if (c == 'S' || c == KEY_DOWN)//down
			k++;
		if (k == -1) k = 3;
		else if (k == 4) k = 0;

		(k == 0) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 0);
		cout << "  New Game  ";

		(k == 1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 1);
		cout << "  Load Game ";

		(k == 2) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 2);
		cout << "  Setting   ";

		(k == 3) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 3);
		cout << "  Exit      ";

		TextColor(CO_HIGHLIGHT);
		GotoXY(i, j + k);
		cout << "->";
		GotoXY(i + 10, j + k);

		if (c == 'W' || c == 'S' || c == KEY_DOWN || c==KEY_UP)
			MyPlaySound(sound, PTH_SOUND_BEEP, E_SOUND_SINGLE);

		c = getch();
		if (c == 0 || c == 224)
			c = 256 + getch();
		c = toupper(c);

	} while (c != 13);//ENTER
	
	return k;
}

int MenuGameOut(bool win, bool sound)
{
	int i, j;
	CleanScreen();
	DrawWall();

	i = NUM_COLS / 2 - 5;
	j = NUM_ROWS / 2 + 1;

	TextColor(12);

	GotoXY(i - 1, j - 4);
	if (!win)
		cout << "  GAME OVER";
	else
		cout << "   VICTORY";

	GotoXY(i - 1, j - 3);
	cout << "     +-+      ";

	TextColor(CO_DEFAULT);
	
	int c = 0; int k = -1;
	do
	{
		if (c == 'W' || c==KEY_UP)//up
		{
			k--;
		}
		else if (c == 'S' || c == KEY_DOWN)//down
		{
			k++;
		}

		if (k == -2) k = 1;
		else if (k == 3) k = -1;

		(k == -1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j - 1);
		cout << "  Replay  ";
		
		(k == 0) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j);
		cout << "  Load Game ";
		
		(k == 1) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 1);
		cout << "  Setting  ";
		
		(k == 2) ? TextColor(CO_HIGHLIGHT) : TextColor(CO_DEFAULT);
		GotoXY(i, j + 2);
		cout << "  Exit   ";
		
		TextColor(CO_HIGHLIGHT);
		GotoXY(i, j + k);
		cout << "->";

		if (c == 'W' || c == 'S' || c == KEY_DOWN || c == KEY_UP)
			MyPlaySound(sound, PTH_SOUND_BEEP, E_SOUND_SINGLE);

		c = getch();
		if (c == 0 || c == 224)
			c = 256 + getch();
		c = toupper(c);

	} while (c != 13);//ENTER

	return k+1;
}
