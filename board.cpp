#include "game.h"
#include <stdexcept>
#include <string>
#define MAX_LOADSTRING 100
#include <random>
#include "wingdi.h"

bool board::animation = false;
int games[10][5][2];
int board::licznik{ 0 };
std::wstring const board::s_class_name{ L"WORDLE PUZZLE" };
int board::stan{ 1 };
int board::klik{ 0 };
// current instance
// The title bar text

POINT board::condinate = { 6,6 };

WCHAR  board::litters[10][5] = {};
int board::colors[4][10][5]={};
std::string board::words[4] = {};
int board::wygrana[4] = {};
std::set<std::string> board::slownik = {};
int board::winpisanie[4] = {};
int board::animacja = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
	LPARAM lParam)
{
	// baz¹ programu by³ tutorial i program 2048.app
	LONG_PTR userData = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	int since = 0;
	int id = userData;
	switch (message)
	{

	case WM_PAINT:
	{

		
	
		
		 
		

		
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			HPEN pen = CreatePen(0, 1, RGB(164, 174, 196));
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 253));
			HBRUSH brush = CreateSolidBrush(RGB(251, 252, 255));
			HBRUSH brushempty = CreateSolidBrush(RGB(164, 174, 196));
			HBRUSH brushplace = CreateSolidBrush(RGB(243, 194, 55));
			HBRUSH brushgood = CreateSolidBrush(RGB(121, 184, 81));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
			
			RECT rect1;
			GetClientRect(hWnd, &rect1);

			SelectObject(hdc, hBrush);
			Rectangle(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom);
			DeleteObject(hBrush);

			DeleteObject(hBrush);
			
			int n = 6;

			if (board::stan == 2)
				n = 8;
			if (board::stan == 4)
				n = 10;
			
			since = n;
			RECT rect;
			GetClientRect(hWnd, &rect);
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;

			int user_space = 100; 

			

			


			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					games[i][j][0] = 5 + j * 62;
					games[i][j][1] = 7 + i * 63;
				}
			}



			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					
					
					
					
					
						if (board::colors[id][i][j] == 1) HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
						if (board::colors[id][i][j] == 2)  (HBRUSH)SelectObject(hdc, brushempty);
						if (board::colors[id][i][j] == 3)  (HBRUSH)SelectObject(hdc, brushplace);
						if (board::colors[id][i][j] == 4)  (HBRUSH)SelectObject(hdc, brushgood);

					

						if (i == board::licznik-1&&board::animation==true)
						{
							if (board::animacja < 27)
							{
								(HBRUSH)SelectObject(hdc, brush);
								RoundRect(hdc, games[i][j][0], games[i][j][1] + board::animacja, games[i][j][0] + 55, games[i][j][1] + 55 - +board::animacja, 7, 7);
							}
							

							if (board::animacja>27 &&board::animacja <= 55)
							{
								if (board::animacja == 55) {
									board::animation = false;
									board::animacja = 0;
								}
								if (board::colors[id][i][j] == 2)  (HBRUSH)SelectObject(hdc, brushempty);
								if (board::colors[id][i][j] == 3)  (HBRUSH)SelectObject(hdc, brushplace);
								if (board::colors[id][i][j] == 4)  (HBRUSH)SelectObject(hdc, brushgood);
								RoundRect(hdc, games[i][j][0], games[i][j][1] + board::animacja, games[i][j][0] + 55, games[i][j][1] + 55 - +board::animacja, 7, 7);
							}

							


						}
						else
						{
							RoundRect(hdc, games[i][j][0], games[i][j][1], games[i][j][0] + 55, games[i][j][1] + 55, 7, 7);
						}
					
					

					

				}
			}

			
			

			//tutorial 

			HFONT font = CreateFont(
				-MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 40), // Height
				0, // Width
				0, // Escapement
				0, // Orientation
				FW_BOLD, // Weight
				false, // Italic
				FALSE, // Underline
				0, // StrikeOut
				EASTEUROPE_CHARSET, // CharSet
				OUT_DEFAULT_PRECIS, // OutPrecision
				CLIP_DEFAULT_PRECIS, // ClipPrecision
				DEFAULT_QUALITY, // Quality
				DEFAULT_PITCH | FF_SWISS, // PitchAndFamily
				_T(" Verdana ")); // Facename



			HFONT oldFont = (HFONT)SelectObject(hdc, font);

			for (int i = 0; i < board::winpisanie[id]; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					LPWSTR lpwstr = new WCHAR[2];

					lpwstr[0] = board::litters[i][j];
					lpwstr[1] = L'\0';

					

					RECT rc = { games[i][j][0] + 2, games[i][j][1], games[i][j][0] + 61, games[i][j][1] + 61 };
					SetBkMode(hdc, TRANSPARENT);
					DrawText(hdc, lpwstr, 2, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				}
			}



			SelectObject(hdc, oldPen);
			DeleteObject(pen);
			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
			DeleteObject(brushempty);
			DeleteObject(brushplace);
			DeleteObject(brushgood);
			//}

			// baz¹ programu by³ tutorial i program 2048.app
			if (board::wygrana[id] == 1)
			{
				//https://www.codeproject.com/Articles/356/Bitmap-Basics-A-GDI-tutorial
				// //http://www.winprog.org/tutorial/bitmaps.html
				//dokumentacja + jakaœ chiñksa strona z kodem
				COLORREF color = RGB(0, 255, 0);
				BYTE alpha = 128;
				HDC hdcMem = CreateCompatibleDC(hdc);
				HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
				SelectObject(hdcMem, hBitmap);
				HBRUSH hBrush = CreateSolidBrush(color);
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcMem, hBrush);
				
				FillRect(hdcMem, &rect, hBrush);
				SelectObject(hdcMem, hOldBrush);
				DeleteObject(hBrush);
				BLENDFUNCTION blend = { AC_SRC_OVER, 0, alpha };
				SetBkMode(hdc, SRCAND);
				
				AlphaBlend(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, rect.right, rect.bottom, blend);

				
				DeleteObject(hBitmap);
				DeleteDC(hdcMem);

				since = board::licznik;
				board::winpisanie[id] = board::licznik;
				SetTextColor(hdc, RGB(255, 255, 255));
				wchar_t* wstr = new wchar_t[5 + 1];

				std::transform(board::words[id].begin(), board::words[id].end(), board::words[id].begin(), [](unsigned char c) { return std::toupper(c); });

				mbstowcs(wstr, board::words[id].c_str(), 5);
				wstr[5] = 0; 
				PCWSTR pcwstr = wstr;
				DrawText(hdc, pcwstr, 5, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				EndPaint(hWnd, &ps);
			}
			if (board::wygrana[id] == 0 && board::licznik == n)
			{
				//http://www.winprog.org/tutorial/bitmaps.html
				
				//https://www.codeproject.com/Articles/356/Bitmap-Basics-A-GDI-tutorial

				COLORREF color = RGB(255, 0, 0);
				BYTE alpha = 128;

				
				HDC hdcMem = CreateCompatibleDC(hdc);
				HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
				SelectObject(hdcMem, hBitmap);

				HBRUSH hBrush = CreateSolidBrush(color);
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcMem, hBrush);
				
				FillRect(hdcMem, &rect, hBrush);
				SelectObject(hdcMem, hOldBrush);
				DeleteObject(hBrush);

				
				BLENDFUNCTION blend = { AC_SRC_OVER, 0, alpha };
				SetBkMode(hdc, SRCAND);
				
				AlphaBlend(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, rect.right, rect.bottom,blend);

				
				DeleteObject(hBitmap);
				DeleteDC(hdcMem);
				SetTextColor(hdc, RGB(255, 255, 255));
				wchar_t* wstr = new wchar_t[5 + 1];
				//draw
				std::transform(board::words[id].begin(), board::words[id].end(), board::words[id].begin(), [](unsigned char c) { return std::toupper(c); });

				mbstowcs(wstr, board::words[id].c_str(), 5);
				wstr[5] = 0; 
				PCWSTR pcwstr = wstr;
				DrawText(hdc, pcwstr, 5, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				EndPaint(hWnd, &ps);
				

				//EndPaint(hWnd, &ps);

				

			}
			
				
			

		
	}
	break;






	case WM_LBUTTONDOWN:
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		RECT rc;
		GetClientRect(hWnd, &rc);
		if (PtInRect(&rc, pt))
		{
			SendMessage(hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		if (wParam & MK_LBUTTON)
		{
			SendMessage(hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, lParam);
		}
		break;
	}

	case WM_LBUTTONUP:
	{
		ReleaseCapture();
		break;
	}


	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);

		break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


bool board::register_class()
{
	// baz¹ programu by³ tutorial i program 2048.app

	WNDCLASSEXW wcex;
	
		 wcex.cbSize = sizeof(WNDCLASSEX);
	
		 wcex.style = CS_HREDRAW | CS_VREDRAW;
	 wcex.lpfnWndProc = WndProc;
	 wcex.cbClsExtra = 0;
	 wcex.cbWndExtra = 0;
	 wcex.hInstance = hInstance;
	 wcex.hIcon = nullptr;
	 wcex.hCursor = nullptr;
	 wcex.hbrBackground = reinterpret_cast <HBRUSH>(COLOR_WINDOW + 1);
	 wcex.lpszMenuName = nullptr;
	
	 wcex.lpszClassName = MAKEINTRESOURCEW(puzzle_name);
	  wcex.hIconSm = nullptr;
	  
		 return RegisterClassExW(&wcex);
	




	

}


HWND board::create_window(int i)
{
	// baz¹ programu by³ tutorial i program 2048.app
	RECT wr = { 0, 0, 0, 0 };
	if (stan == 1) {
		 wr = { 0, 0, 311, 372 };    // set the size, but not the position
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_BORDER, TRUE);
	}  // adjust the size
	if (stan == 2) {
		 wr = { 0, 0,311 , 494 };    
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_BORDER, TRUE);
	} 
	if (stan == 4) {
		 wr = { 0, 0, 311, 616 };    
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_BORDER, TRUE);
	}  

	


	return CreateWindowW(
		MAKEINTRESOURCEW(puzzle_name),
		L"WORDLE - PUZZLE",
		WS_CAPTION | WS_MINIMIZEBOX| WS_BORDER,
		center.x-(wr.right-wr.left)/2,
		center.y-300,
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,
		nullptr,
		0,
		hInstance,
		this);
}

board::board(HINSTANCE instance)
	: hInstance{ instance }, windows{}, center{ GetSystemMetrics(SM_CXSCREEN) / 2,GetSystemMetrics(SM_CYSCREEN) / 2 }
{
	std::ifstream plik("Wordle.txt");
	std::string slowo;
	//dokumentacja
	if (plik.is_open()) {
		while (getline(plik, slowo)) {
			slownik.insert(slowo);
		}
		plik.close();
	}
	else {
		std::cerr << "Nie uda³o siê otworzyæ pliku" << std::endl;

	}

	register_class();
	for(int z=0;z<4;z++)
	{ 
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			board::litters[i][j] = ' ';
			board::colors[z][i][j] = 1;
			
		}
	}
	board::wygrana[z] = 0;
	if(stan==1)
	{ 
	board::winpisanie[z] = 6;
	
	}
	if (stan == 2)
	{
	board:winpisanie[z] = 8;
	}
	if (stan == 4)
	{
	board::winpisanie[z] = 10;
	}
	

	}
}





int board::run(int show_command)
{
	// baz¹ programu by³ tutorial i program 2048.app
	// baz¹ programu by³ tutorial i program 2048.app
	//srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		

		std::random_device rd; 
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> distr(1, slownik.size()); 

		
		int index = distr(gen);
	
		auto it = std::begin(slownik);
		std::advance(it, index);
		
		words[i] = *it;




	}


	for (int i = 0; i < stan; i++) {
    windows[i] = create_window(i);
	SetWindowLongPtr(windows[i], GWLP_USERDATA, (LONG_PTR)i);
	}


	for(int i=0; i<stan;i++)
	ShowWindow(windows[i], show_command);
	RECT other_rc;
	GetWindowRect(windows[0], &other_rc);

	SIZE a{
	.cx = other_rc.right - other_rc.left,
	.cy = other_rc.bottom - other_rc.top };
	

	if (stan == 1)
	{
		MoveWindow(windows[0], center.x  - a.cx / 2, center.y - a.cy/2-50 , a.cx, a.cy, 0);
		

	}

	if (stan == 2)
	{
		MoveWindow(windows[0], center.x/2-a.cx/2, center.y-a.cy/2, a.cx, a.cy, 0);
		MoveWindow(windows[1], 3*center.x/2-a.cx/2,center.y-a.cy /2, a.cx, a.cy, 0);
	}

	if (stan == 4)
	{
		MoveWindow(windows[0], center.x / 3 - a.cx / 2, center.y - a.cy / 2, a.cx, a.cy, 0);
		MoveWindow(windows[1],  3*center.x/4  - a.cx / 2, center.y - a.cy / 2, a.cx, a.cy, 0);
		MoveWindow(windows[2], center.x  + a.cx/2 / 2, center.y - a.cy / 2, a.cx, a.cy, 0);
		MoveWindow(windows[3],  4*center.x/3  + a.cx / 2, center.y - a.cy / 2, a.cx, a.cy, 0);
	}


	MSG msg{};
	BOOL result = TRUE;
	while (stan>0&&(result = GetMessageW(&msg, nullptr, 0, 0)) != 0)
	{
		if (result == -1)
			return EXIT_FAILURE;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
}
	return EXIT_SUCCESS;
}



 