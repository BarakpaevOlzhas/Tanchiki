#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#pragma warning(disable:4996)

typedef BOOL(WINAPI *SETCONSOLEFONT)(HANDLE, DWORD);
typedef BOOL(WINAPI *SETCURRENTCONSOLEFONTEX)(HANDLE, BOOL, PCONSOLE_FONT_INFOEX);
SETCONSOLEFONT SetConsoleFont;

void start(int row = 25, int column = 80, int fontSizeX = 2, int fontSizeY = 2) {
	OSVERSIONINFOEX osvi;
	CONSOLE_FONT_INFOEX cfon;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&osvi);
	HMODULE hmod = GetModuleHandleA("KERNEL32.DLL");
	if (osvi.dwMajorVersion<6) {
		SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");
		if (!SetConsoleFont) { exit(1); }
		SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	}
	else
	{
		if (!SetCurrentConsoleFontEx) { exit(1); }
		ZeroMemory(&cfon, sizeof(CONSOLE_FONT_INFOEX));

		cfon.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfon.nFont = 5;
		cfon.FontFamily = 0;
		cfon.dwFontSize.X = fontSizeX;
		cfon.dwFontSize.Y = fontSizeY;
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cfon);
	}
	char command[100];
	sprintf(command, "mode con cols=%d lines=%d", column, row);
	system(command);
	system("cls");
}


void SetColor(WORD wAttributes) {
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOUTPUT, wAttributes);
}

void SetColor(int fon, int text) {
	SetColor((fon << 4) + text);
}

void SetPos(int x, int y) {
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}


void HideCursor(bool Visable = false) {
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = Visable;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}


