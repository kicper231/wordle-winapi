#pragma once
#include <string>
#include <windows.h>
#include "resource.h"
#include "tchar.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <Windows.h>


// baz¹ programu by³ tutorial i program 2048.app
class board
{
public:
	bool register_class();
	static bool animation;
	static int animacja;
	HWND create_window(int);
	HINSTANCE hInstance;
	HWND windows[4];
	
	static std::wstring const s_class_name;
	static POINT condinate;
	POINT center;
	POINT klikpoint = { 0,0 };
	static int klik;
	static int stan;
	board(HINSTANCE instance);
	int run(int show_command);
	int getstan() { return stan; }
	 friend  LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

	 static int licznik;
	 static int colors[4][10][5];
	 static TCHAR litters[10][5];
	 static std::string words[4];
	 static int wygrana[4];
	 int id;
	 static std::set<std::string> slownik;
	 static int winpisanie[4];

};