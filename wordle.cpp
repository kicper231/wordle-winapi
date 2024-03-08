#include "wordle.h"
#include <stdexcept>
#include <string>


#define MAX_LOADSTRING 100

std::wstring const wordle::s_class_name{ L"2048 Window" }; 



                    
WCHAR szWindowClass[MAX_LOADSTRING];


bool wordle::register_class()
{
	

	
	//tutorial

	
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = window_proc_static;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
	wcex.lpszClassName = MAKEINTRESOURCEW(keyboard_name);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);

}


HWND wordle::create_window()
{
	RECT wr = { 0, 0, 616, 195 };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, TRUE);
	

	return CreateWindowW(
		MAKEINTRESOURCEW(keyboard_name),
		L"Wordle Keyboard",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		tablica.center.x-(wr.right-wr.left)/2,
		tablica.center.y+100,
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,
		nullptr,
		nullptr,
		hInstance,
		this);
}



LRESULT wordle::window_proc_static(
	HWND window,
	UINT message,
	WPARAM wparam,
	LPARAM lparam)
{
	//tutorial
	wordle* app = nullptr;
	if (message == WM_NCCREATE)
	{
		app = static_cast<wordle*>(
			reinterpret_cast<LPCREATESTRUCTW>(lparam)
			-> lpCreateParams);
		SetWindowLongPtrW(window, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(app));
		SetTimer(window, 7, 50, NULL);

		app->clock_start = std::chrono::steady_clock::now();
		

		app->tablica.stan = 1;

	}
	else
		app = reinterpret_cast<wordle*>(
			GetWindowLongPtrW(window, GWLP_USERDATA));
	LRESULT res = app ?
		app -> window_proc(window, message, wparam, lparam) :
		DefWindowProcW(window, message, wparam, lparam);
	if (message == WM_NCDESTROY)
		SetWindowLongPtrW(window, GWLP_USERDATA, 0);
	return res;
}




LRESULT wordle::window_proc(
	HWND window,
	UINT message,
	WPARAM wparam,
	LPARAM lparam)
{
	 const int bufSize = 256;
	 TCHAR buf[bufSize] =_T("a");
	 // baz¹ programu by³ tutorial i program 2048.app
	HMENU a = GetMenu(window);
	switch (message)
	{

	case WM_CHAR:
	{
		int n = 0;
		if (board::stan == 1) n = 6;
		if (board::stan == 2) n = 8;
		if (board::stan == 4) n = 10;

		if (L'\x0008' == WCHAR(wparam))
		{

			if (tablica.klikpoint.x > 0)
			{
				tablica.litters[tablica.klikpoint.y][tablica.klikpoint.x - 1] = ' ';
				tablica.klikpoint.x--;
				for (int i = 0; i < tablica.stan; i++)
					if (tablica.wygrana[i] != 1)
					{
						InvalidateRect(tablica.windows[i], NULL, TRUE);
					}
			}

			break;

		}

		if (tablica.klikpoint.x == 5) {

			if (WCHAR(wparam) == L'\r')
			{

				char str[5] = { 0 }; 

				// konwersja wchar_t na char
				std::wcstombs(str, tablica.litters[tablica.klikpoint.y], 5);


				std::string slowo_string(str, 5);

				if (tablica.slownik.count(slowo_string)) {

					tablica.klikpoint.x = 0;
					tablica.klikpoint.y++;
					tablica.licznik++;
					int wczesniej[4] = {};
					
					for (int z = 0; z < stan; z++)
					{
						LONG_PTR userData = GetWindowLongPtr(tablica.windows[z], GWLP_USERDATA);

						int id = userData;

						wczesniej[z] = board::wygrana[z];
						for (int i = 0; i < 5; i++)
						{
							for (int j = 0; j < 5; j++)
							{

								if (slowo_string[i] == board::words[z][j]) {
									if (i == j) board::colors[id][tablica.licznik - 1][i] = 4;
									else board::colors[id][tablica.licznik - 1][i] = 3;
								}
							}
							if (board::colors[id][tablica.licznik - 1][i] == 1) board::colors[id][tablica.licznik - 1][i] = 2;

							int indeks = 0;

							for (int k = 0; k < 26; k++) {
								if (tolower(znaki[k]) == slowo_string[i]) {
									indeks = k; // przypisz aktualny indeks, jeœli literka zostanie znaleziona
									break; // przerwij pêtlê, gdy literka zostanie znaleziona
								}
							}
							color[z][indeks] = board::colors[z][tablica.licznik - 1][i];

						}




						if (slowo_string == board::words[id])
						{
							board::wygrana[id] = 1;

						}

					}





					for (int i = 0; i < tablica.stan; i++)
					{
						if (board::wygrana[i] != 1 || board::wygrana[i] != wczesniej[i])
						{
							InvalidateRect(tablica.windows[i], NULL, TRUE);
							InvalidateRect(window, NULL, TRUE);
						}

					}


					if (board::licznik < n)
						board::animation = true;


				}
				else
				{
					for (int i = 0; i < 5; i++)
					{
						tablica.litters[tablica.klikpoint.y][tablica.klikpoint.x - 1] = ' ';
						tablica.klikpoint.x--;
					}

					for (int i = 0; i < tablica.stan; i++)
					{
						if (tablica.wygrana[i] != 1)
						{
							InvalidateRect(tablica.windows[i], NULL, TRUE);
						}
					}


				}

				break;
			}
			else
			{
				break;
			}

		}


		char ch = (char)wparam;
		ch = std::toupper(ch);

		if (std::strchr(znaki, ch) != nullptr)
		{
			if (board::licznik < n)
			{
				tablica.litters[tablica.klikpoint.y][tablica.klikpoint.x] = (WCHAR)wparam;
				tablica.klikpoint.x++;
				tablica.klik = 1;
				for (int i = 0; i < tablica.stan; i++)
					for (int i = 0; i < tablica.stan; i++)
					{
						if (tablica.wygrana[i] != 1)
						{
							InvalidateRect(tablica.windows[i], NULL, TRUE);
						}
					}
			}
		}






		
		break;

	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wparam);
	
		switch (wmId)
		{




		case ID_DIFFICULTY_EASY:
		{


			for (int i = 0; i < stan; i++)
				DestroyWindow(tablica.windows[i]);
			CheckMenuItem(a, ID_DIFFICULTY_HARD, MF_UNCHECKED);
			CheckMenuItem(a, ID_DIFFICULTY_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(a, ID_DIFFICULTY_EASY, MF_CHECKED);

			for (int z = 0; z < 4; z++)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						tablica.litters[i][j] = ' ';
						tablica.colors[z][i][j] = 1;

					}
				}
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 26; j++)
				{
					color[i][j] = 1;
				}
			}
			tablica.klikpoint = { 0,0 };
			stan = 1;
			tablica.stan = 1;
			tablica.klik = 0;
			tablica.licznik = 0;

			for (int i = 0; i < 4; i++)
			{
				tablica.winpisanie[i] = 6;
				tablica.wygrana[i] = 0;
			}
			InvalidateRect(window, NULL, TRUE);
			tablica.run(1);


		}

		break;
		case ID_DIFFICULTY_MEDIUM:



			for (int i = 0; i < stan; i++)
				DestroyWindow(tablica.windows[i]);

			CheckMenuItem(a, ID_DIFFICULTY_HARD, MF_UNCHECKED);
			CheckMenuItem(a, ID_DIFFICULTY_EASY, MF_UNCHECKED);
			CheckMenuItem(a, ID_DIFFICULTY_MEDIUM, MF_CHECKED);
			for (int z = 0; z < 4; z++)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						tablica.litters[i][j] = ' ';
						tablica.colors[z][i][j] = 1;

					}
				}
				tablica.winpisanie[z] = 8;
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 26; j++)
				{
					color[i][j] = 1;
				}
			}
			tablica.klikpoint = { 0,0 };
			stan = 2;
			tablica.stan = 2;
			tablica.klik = 0;

			tablica.licznik = 0;
			for (int i = 0; i < 4; i++)
			{
				tablica.winpisanie[i] = 8;
				tablica.wygrana[i] = 0;
			}

			tablica.run(1);


			InvalidateRect(window, NULL, TRUE);




			break;

		case ID_DIFFICULTY_HARD:




			for (int i = 0; i < stan; i++)
				DestroyWindow(tablica.windows[i]);

			CheckMenuItem(a, ID_DIFFICULTY_EASY, MF_UNCHECKED);
			CheckMenuItem(a, ID_DIFFICULTY_MEDIUM, MF_UNCHECKED);
			CheckMenuItem(a, ID_DIFFICULTY_HARD, MF_CHECKED);

			for (int z = 0; z < 4; z++)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						tablica.litters[i][j] = ' ';
						tablica.colors[z][i][j] = 1;

					}
				}
				tablica.winpisanie[z] = 10;
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 26; j++)
				{
					color[i][j] = 1;
				}
			}
			tablica.klikpoint = { 0,0 };
			stan = 4;
			tablica.stan = 4;
			tablica.klik = 0;

			tablica.licznik = 0;

			for (int i = 0; i < 4; i++)
			{
				tablica.winpisanie[i] = 10;
				tablica.wygrana[i] = 0;
			}

			tablica.run(1);


			InvalidateRect(window, NULL, TRUE);



			break;


		default:

			return DefWindowProc(window, message, wparam, lparam);
		}
	}
	break;


	case WM_CLOSE:
	{

		WCHAR buffer[16];
		_itow_s(stan, buffer, 10);
		// documentation
		BOOL result= WritePrivateProfileString(L"WORDLE", L"DIFFICULTY", buffer,  L".\\stan.ini");
		// documentation
		if (!result) {
			DWORD error = GetLastError();
			TCHAR message[256];
			DWORD size = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, message, 256, NULL);
			_tprintf(_T("Error %d: %s"), error, message);
			return 1;
		}



		

	for (int i = 0; i < stan; i++)
		DestroyWindow(tablica.windows[i]);

	DestroyWindow(m_main);



	tablica.stan = -1;
	return 0;
	}
		break;
	case WM_DESTROY:

		

		for (int i = 0; i < stan; i++)
			DestroyWindow(tablica.windows[i]);
		    tablica.stan = -1;
		
			PostQuitMessage(EXIT_SUCCESS);
		return 0;

	case WM_TIMER:

		if (wparam == 7) // check timer id
		{ 

			if (board::animation == true)
			{
				board::animacja += 5;
				for (int i = 0; i < stan; i++)
				{
				if(board::wygrana[i]!=1)	InvalidateRect(tablica.windows[i], NULL, TRUE);
				}

			}
		

		clock_end = std::chrono::steady_clock::now();
			
		czas = clock_end - clock_start;
		double nseconds = double(czas.count());

		// dokumnetacja wstring
		std::wstring text = L"Wordle Keyboard: ";
		 std::wstring secunds = std::to_wstring(nseconds);
		 std::wstring wyjscie = text + secunds;
		 LPCWSTR outofficial = wyjscie.c_str();

		 SetWindowText(window, outofficial);

		}
		

		
		




			break;

	 case WM_PAINT:
		 {




			 PAINTSTRUCT ps;
			 HDC hdc = BeginPaint(window, &ps);
			 HPEN pen = CreatePen(0, 1, RGB(164, 174, 196));
			 HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			 HBRUSH brush = CreateSolidBrush(RGB(251, 252, 255));
			 HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
			// Rectangle(hdc, 6, 6, 55, 55);
			 //Rectangle(hdc, 6, 6, 55, 55);
			 for (int i = 0; i < 26; i++)
			 {
				 RoundRect(hdc, triagxy[i][0], triagxy[i][1], triagxy[i][0]+55 ,triagxy[i][1]+55, 7, 7);
			 }
			 //HBRUSH brush1 = CreateSolidBrush(RGB(251, 0, 0));
			
			 HBRUSH brushempty = CreateSolidBrush(RGB(164, 174, 196));
			 HBRUSH brushplace = CreateSolidBrush(RGB(243, 194, 55));
			 HBRUSH brushgood = CreateSolidBrush(RGB(121, 184, 81));
			 HPEN pen1 = CreatePen(PS_NULL, 1, RGB(0,0,0));
			 if (stan == 1)
			 {

				 for (int i = 0; i < 26; i++) {
					 if (color[0][i] == 1)  (HBRUSH)SelectObject(hdc, brush);
					 if (color[0][i] == 2) (HBRUSH)SelectObject(hdc, brushempty);
					 if (color[0][i] == 3)(HBRUSH)SelectObject(hdc, brushplace);
					 if (color[0][i] == 4) (HBRUSH)SelectObject(hdc, brushgood);

					 Rectangle(hdc, triagxy[i][0], triagxy[i][1], triagxy[i][0] + 55, triagxy[i][1] + 55);
				 }
			 }
			if (stan == 2)
				 {
					
						 for (int i = 0; i < 26; i++) {
							 if (color[0][i] == 1)  (HBRUSH)SelectObject(hdc, brush);
							 {
								
								 (HPEN)SelectObject(hdc, pen1);
							 }
							 if (color[0][i] == 2) (HBRUSH)SelectObject(hdc, brushempty);
							 if (color[0][i] == 3)(HBRUSH)SelectObject(hdc, brushplace);
							 if (color[0][i] == 4) (HBRUSH)SelectObject(hdc, brushgood);

							 Rectangle(hdc, triagxy[i][0], triagxy[i][1], triagxy[i][0] +27, triagxy[i][1] + 55);
							 
						  
						 }
						 for (int i = 0; i < 26; i++) {
							 if (color[1][i] == 1)  (HBRUSH)SelectObject(hdc, brush);
							 {

								 (HPEN)SelectObject(hdc, pen1);
							 }
							 if (color[1][i] == 2) (HBRUSH)SelectObject(hdc, brushempty);
							 if (color[1][i] == 3)(HBRUSH)SelectObject(hdc, brushplace);
							 if (color[1][i] == 4) (HBRUSH)SelectObject(hdc, brushgood);

							 Rectangle(hdc, triagxy[i][0] + 26, triagxy[i][1], triagxy[i][0] + 55, triagxy[i][1] + 55);


						 }
				 
			 }
			if (stan == 4)
			{

				for (int i = 0; i < 26; i++) {
					if (color[0][i] == 1)  (HBRUSH)SelectObject(hdc, brush);
					{

						(HPEN)SelectObject(hdc, pen1);
					}
					if (color[0][i] == 2) (HBRUSH)SelectObject(hdc, brushempty);
					if (color[0][i] == 3)(HBRUSH)SelectObject(hdc, brushplace);
					if (color[0][i] == 4) (HBRUSH)SelectObject(hdc, brushgood);

					Rectangle(hdc, triagxy[i][0], triagxy[i][1], triagxy[i][0] + 27, triagxy[i][1] + 27);


				}
				for (int i = 0; i < 26; i++) {
					if (color[1][i] == 1)  (HBRUSH)SelectObject(hdc, brush);
					{

						(HPEN)SelectObject(hdc, pen1);
					}
					if (color[1][i] == 2) (HBRUSH)SelectObject(hdc, brushempty);
					if (color[1][i] == 3)(HBRUSH)SelectObject(hdc, brushplace);
					if (color[1][i] == 4) (HBRUSH)SelectObject(hdc, brushgood);

					Rectangle(hdc, triagxy[i][0] + 26, triagxy[i][1], triagxy[i][0] + 55, triagxy[i][1] + 27);


				}
				for (int i = 0; i < 26; i++) {
					if (color[2][i] == 1)  (HBRUSH)SelectObject(hdc, brush);
					{

						(HPEN)SelectObject(hdc, pen1);
					}
					if (color[2][i] == 2) (HBRUSH)SelectObject(hdc, brushempty);
					if (color[2][i] == 3)(HBRUSH)SelectObject(hdc, brushplace);
					if (color[2][i] == 4) (HBRUSH)SelectObject(hdc, brushgood);

					Rectangle(hdc, triagxy[i][0] , triagxy[i][1]+26, triagxy[i][0] + 27, triagxy[i][1] + 55);


				}
				for (int i = 0; i < 26; i++) {
					if (color[3][i] == 1)  (HBRUSH)SelectObject(hdc, brush);
					{

						(HPEN)SelectObject(hdc, pen1);
					}
					if (color[3][i] == 2) (HBRUSH)SelectObject(hdc, brushempty);
					if (color[3][i] == 3)(HBRUSH)SelectObject(hdc, brushplace);
					if (color[3][i] == 4) (HBRUSH)SelectObject(hdc, brushgood);

					Rectangle(hdc, triagxy[i][0] + 26, triagxy[i][1]+26, triagxy[i][0] + 55, triagxy[i][1] + 55);


				}

			}

			 SelectObject(hdc, oldPen);
			 DeleteObject(pen);
			 DeleteObject(pen1);
			 SelectObject(hdc, oldBrush);
			 DeleteObject(brush);
			 DeleteObject(brushplace);
			 DeleteObject(brushgood);
			 DeleteObject(brushempty);



			 TCHAR dest[27] = { 0, };

			 MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, znaki, strlen(znaki), dest, 27);
			 
				 TCHAR s[] = _T("Q");
				 HFONT font = CreateFont(
					 - MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 50), // Height
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
			
			 
			 SetBkMode(hdc, TRANSPARENT);

			 for (int i = 0; i < 26; i++)
			 {
				 RECT rc = { triagxy[i][0],triagxy[i][1],triagxy[i][0]+55,triagxy[i][1]+55};
				 DrawText(hdc, dest + i, 1, &rc,
					 DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			 }
			 
			
			 SelectObject(hdc, oldFont);
			 DeleteObject(font);
			 EndPaint(window, &ps);



			 }
		break;



	}




	return DefWindowProcW(window, message, wparam, lparam);
}



wordle::wordle(HINSTANCE instance)
	: hInstance{ instance }, m_main{}, tablica{instance} 

{
	

	
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			color[i][j] = 1;
		}
	}


	
	
	
	register_class();
	for (int i = 0; i <10; i++)
	{
		triagxy[i][0] = 6+61*i;
		triagxy[i][1] = 6;
	}
	
	for (int i = 0; i < 9; i++)
	{
		triagxy[i+10][0] = 40 + 61 * i;
		triagxy[i+10][1] = 67;
	}
	for (int i = 0; i < 7; i++)
	{
		triagxy[i + 19][0] = 90 + 61 * i;
		triagxy[i + 19][1] = 128;
	}

	m_main = create_window();
	
		
}

int wordle::run(int show_command)
{
	SetWindowLong(m_main, GWL_EXSTYLE,
		// baz¹ programu by³ tutorial i program 2048.app
		GetWindowLong(m_main, GWL_EXSTYLE) | WS_EX_LAYERED);
	
	SetLayeredWindowAttributes(m_main, 0, (255 * 50) / 100, LWA_ALPHA);
	ShowWindow(m_main, show_command);


	
	stan = 1;
	tablica.stan = 1;

	int value = GetPrivateProfileInt(L"WORDLE", L"DIFFICULTY", 1, L".\\stan.ini");
	stan = value;
	tablica.stan = value;

	HMENU a = GetMenu(m_main);
	if(stan ==1 )
	{
		for (int i = 0; i < stan; i++)
		{
			board::winpisanie[i] = 6;
		}
	CheckMenuItem(a, ID_DIFFICULTY_EASY, MF_CHECKED);
	}
	if (stan == 2)
	{ 
		for (int i = 0; i < stan; i++)
		{
			board::winpisanie[i] = 8;
		}
		CheckMenuItem(a, ID_DIFFICULTY_MEDIUM, MF_CHECKED);
	}
	if (stan == 4)
	{
		for (int i = 0; i < stan; i++)
		{
			board::winpisanie[i] = 10;
		}
		CheckMenuItem(a, ID_DIFFICULTY_HARD, MF_CHECKED);
	}
	

	tablica.run(show_command);
	
		
	
	
	
	MSG msg{};
	BOOL result = TRUE;
	while ((result = GetMessageW(&msg, nullptr, 0, 0)) != 0)
	{
		if (result == -1)
			return EXIT_FAILURE;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return EXIT_SUCCESS;
}
