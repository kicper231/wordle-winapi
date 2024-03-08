#pragma once
#include <string>
#include <windows.h>
#include "resource.h"
#include "tchar.h"
#include <chrono>
#include <set>
#include "game.h"

#define _CRT_SECURE_NO_WARNINGS 
// baz¹ programu by³ tutorial i program 2048.app

class wordle
{
private:
	bool register_class();
	static std::wstring const s_class_name;
	static LRESULT CALLBACK window_proc_static(
		HWND window,
		UINT message,
		WPARAM wparam,
		LPARAM lparam);
	LRESULT window_proc(
		HWND window,
		UINT message,
		WPARAM wparam,
		LPARAM lparam);
	HWND create_window();
	HINSTANCE hInstance;
	HWND m_main;
	std::chrono::duration<double> czas;
	std::chrono::steady_clock::time_point clock_start;
	std::chrono::steady_clock::time_point clock_end;
	friend class board;
	board tablica;
	int stan = 1;
	char znaki[26] = { 'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F',
	'G', 'H','J','K','L','Z','X','C','V','B','N','M' };
	int triagxy[26][2];
	
	int color[4][26];
	


public:
	
	wordle(HINSTANCE instance);
	int run(int show_command);
};