// Win32Lesson1.cpp : Defines the entry point for the application.
//
#define JGN_WINDOWS_CPP
#include "stdafx.h"
#include "JGN_Resource.h"
#include "JGN_DropFile.h"
#include "JGN_Windows.h"

/////////////////////////////////////////////////
//
//Window
//


HWND JGN_CreateWindow(char* EszTitle,
	int       nCmdShow,
	HINSTANCE hInstance
)
{
	if (jgn_wndcnt > 9)
	{
		perror("Max Number Of Windows Has Reached");
		return NULL;
	}

	int i = 0;
	while (EszTitle[i] != '\0' && i < 100)
	{
		szTitle[i] = EszTitle[i];
		i++;
	}




	// Initialize global strings
	LoadString(hInstance, jgn_int_macro_map[jgn_wndcnt], szWindowClass, MAX_LOADSTRING);


	JGN_RegisterClass(hInstance);


	// Perform application initialization:




	// Main message loop:

	jgn_help_to_map_the_draw_func = InitInstance(hInstance, nCmdShow);


	DragAcceptFiles(jgn_help_to_map_the_draw_func, TRUE);
	//wglDeleteContext(hglrc);
	return jgn_help_to_map_the_draw_func;
}
void JGN_InitOpenGL()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

}


void JGN_CreateChild(char* txt,
	int x, int y, int w, int h,
	char* clas,
	DWORD style, HWND hWnd1)
{

	jgn_Child_C++;
	jgn_ChildWin = (HWND*)realloc(jgn_ChildWin, jgn_Child_C * sizeof(HWND));

	TCHAR wclass[20];
	for (int i = 0; i < 20; i++)
	{
		wclass[i] = clas[i];
		if (clas[i] == '\0')
		{
			i = 100;
		}
	}

	TCHAR wtxt[1000];
	for (int i = 0; i < 1000; i++)
	{
		wtxt[i] = txt[i];
		if (txt[i] == '\0')
		{
			i = 2000;
		}
	}
	jgn_ChildWin[jgn_Child_C - 1] = CreateWindow(wclass,
		wtxt, style,
		x, y, w, h,
		hWnd1, NULL, NULL, NULL);

	UpdateWindow(jgn_ChildWin[jgn_Child_C - 1]);


}

void JGN_ClearColor(BYTE r, BYTE g, BYTE  b, BYTE a)
{
	RECT rect = { 0,0,0,0 };
	COLORREF crColor = RGB(r, g, b);
	HBRUSH brush = CreateSolidBrush(crColor);
	HDC hdc = GetDC(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit]);

	GetClientRect(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit], &rect);
	FillRect(hdc, &rect, brush);

	DeleteDC(hdc);


}




//static stuf... will be there from the begining to the end


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM JGN_RegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;


	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS; //CS_HREDRAW | CS_VREDRAW | redraws the hall screen when resized, couses flicks
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JGNICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = MAKEINTRESOURCE(jgn_int_macro_map[jgn_wndcnt]);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_JGNSMALL));

	return RegisterClassEx(&wcex);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

void JGN_InitWindowSize(int w, int h)
{
	jgn_init_wind_size[jgn_wndcnt][0] = w;
	jgn_init_wind_size[jgn_wndcnt][1] = h;

	jgn_glbrect = { jgn_glbrect.left,jgn_glbrect.top,jgn_glbrect.right + w , jgn_glbrect.bottom + h };
	return;
}
void JGN_InitWindowPosition(int x, int y)
{
	jgn_glbrect = { jgn_glbrect.left + x, jgn_glbrect.top + y, jgn_glbrect.right + x, jgn_glbrect.bottom + y };
	return;
}



HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND h = hWnd[jgn_wndcnt] = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_COMPOSITED,//WS_CLIPCHILDREN WS_CLIPSIBLINGS WS_EX_COMPOSITED(double buffer)
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	mnhwnd = h;
	PIXELFORMATDESCRIPTOR pfd;
	HDC hdc;
	int nPixelFormat;
	hdc = GetDC(h);

	pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,0,0,0,0,0,0,0, // useles parameters
		16,
		0,0,0,0,0,0,0
	};
	nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, nPixelFormat, &pfd);


	hglrc = wglCreateContext(hdc);


	wglMakeCurrent(hdc, hglrc);


	DeleteDC(hdc);
	int w = jgn_init_wind_size[jgn_wndcnt][0];
	int he = jgn_init_wind_size[jgn_wndcnt][1];
	glViewport(0, 0, w, he);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= he)
	{
		glOrtho(
			-1.05, +1.05,
			-1.05 * (GLfloat)he / (GLfloat)w, +1.05 * (GLfloat)he / (GLfloat)w,
			-10.0, 10.0);

	}
	else
	{
		glOrtho(
			-1.05 * (GLfloat)w / (GLfloat)he, +1.05 * (GLfloat)w / (GLfloat)he,
			-1.05, +1.05,
			-10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);

	JGN_InitOpenGL();


	if (h != NULL)
	{
		ShowWindow(h, SW_SHOW);
		UpdateWindow(h);

		jgn_hwnd_int_map[h] = jgn_wndcnt;

		jgn_wndcnt++;
	}
	else
	{
		perror("CreateWindow Function Could Not Create Window");
		return NULL;
	}

	DWORD dwStyle = GetWindowLongPtr(h, GWL_STYLE);
	DWORD dwExStyle = GetWindowLongPtr(h, GWL_EXSTYLE);
	HMENU menu = GetMenu(h);



	RECT rc = jgn_glbrect;

	AdjustWindowRectEx(&rc, dwStyle, !(menu == 0), dwExStyle);

	if (menu == 0)
	{
		SetWindowPos(h, NULL, rc.left + 8, rc.top + 30, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

	}
	else
	{
		SetWindowPos(h, NULL, rc.left + 8, rc.top + 50, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
	}

	jgn_glbrect = { 0,0,0,0 };




	return h;
}

void JGN_QRedisplay()
{
	qredisplay = true;
	if (my_postmessages_count == 0)
	{
		PostMessage(jgn_help_to_map_the_draw_func, WM_MOUSEMOVE, -1, rand());
		my_postmessages_count++;
	}

}

void JGN_PostRedisplay()
{

	if (jgn_file_dropd)
	{

		____JGN_DisplayF();


	}
	else
	{
		HDC global_hdc = GetDC(jgn_dawfunc_hwnd_map[JGN_Global_Draw[0]]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		SwapBuffers(global_hdc);

		DeleteDC(global_hdc);

	}

}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//  WM_SETREDRAW
//	

void JGN_DisplayFunc(void JDS())
{
	JGN_Global_Draw[jgn_wndcnt - 1] = JDS;
	jgn_dawfunc_hwnd_map[JDS] = jgn_help_to_map_the_draw_func;
}

void JGN_ReshapeFunc(void RSF(int w, int h))
{
	JGN_User_ReshapeFunc[jgn_wndcnt - 1] = RSF;
	return;

}
void JGN_PassiveMotionFunc(void JPMF(int x, int y))
{
	JGN_User_PassiveMotionFunc[jgn_wndcnt - 1] = JPMF;
	return;
}

void JGN_MotionFunc(void JPMF(int x, int y))
{
	JGN_User_MotionFunc[jgn_wndcnt - 1] = JPMF;
	return;
}

void JGN_MouseFunc(void JMF(int button, int state, int x, int y))
{
	JGN_User_MouseFunc[jgn_wndcnt - 1] = JMF;
	return;

}
void JGN_KeyboardFunc(void JKF(int button, int state, int x, int y))
{
	JGN_User_KeyboardFunc[jgn_wndcnt - 1] = JKF;
	return;
}

void ____JGN_PassiveMotionFunc(int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];

	if (JGN_User_PassiveMotionFunc[xx] == NULL)
	{
	}
	else
	{
		JGN_User_PassiveMotionFunc[xx](x, y);
	}
	return;
}

void ____JGN_MotionFunc(int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];

	if (JGN_User_MotionFunc[xx] == NULL)
	{
	}
	else
	{
		JGN_User_MotionFunc[xx](x, y);
	}
	return;
}


void ____JGN_MouseFunc(int button, int state, int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];
	if (JGN_User_MouseFunc[xx] == NULL)
	{

	}
	else
	{
		JGN_User_MouseFunc[xx](button, state, x, y);
	}
	return;
}
void ____JGN_KeyboardFunc(int button, int state, int x, int y, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];

	if (JGN_User_KeyboardFunc[xx] == NULL)
	{

	}
	else
	{
		JGN_User_KeyboardFunc[xx](button, state, x, y);
	}
	return;
}

void ____JGN_ReshapeFunc(int w, int h, HWND hwnd1)
{
	int xx = jgn_hwnd_int_map[hwnd1];


	if (JGN_User_ReshapeFunc[xx] == NULL)
	{

	}
	else
	{
		JGN_User_ReshapeFunc[xx](w, h);
	}
	return;
}
void ____JGN_DisplayF()
{


	for (int i = 0; i < jgn_wndcnt; i++)
	{

		jgn_curent_window_to_edit = JGN_Global_Draw[i];


		HDC global_hdc = GetDC(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit]);



		//hdc = BeginPaint(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit], &ps);

		/*hdcMem = CreateCompatibleDC(hdc);
		hbmMem = CreateCompatibleBitmap(hdc, 1000, 1000);

		hOld = SelectObject(hdcMem, hbmMem);*/

		cout << 1 << endl;

		JGN_Global_Draw[0]();
		cout << 4 << endl;


		//BitBlt(hdc, 0, 0, 1000, 1000, hdcMem, 0, 0, SRCCOPY);

		//// Free-up the off-screen DC
		//SelectObject(hdcMem, hOld);
		//DeleteObject(hbmMem);
		//DeleteDC(hdcMem);

		//EndPaint(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit], &ps);



		SwapBuffers(global_hdc);



		DeleteDC(global_hdc);

		//UpdateWindow(jgn_dawfunc_hwnd_map[jgn_curent_window_to_edit]);
	}

	//RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT);



	return;
}
LRESULT CALLBACK WndProcEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case VK_RETURN:
			return 0;
			break;
		}
		break;
	}

	return CallWindowProc(oldEditProc, hWnd, message, wParam, lParam);

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{



	switch (message)
	{
	case WM_CTLCOLORSTATIC://////paint child
	{

		hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(0, 255, 255));
		SetBkColor(hdc, RGB(50, 50, 50));
		return (INT_PTR)CreateSolidBrush(RGB(50, 50, 50));
	}
	break;

	case WM_CTLCOLOREDIT://///paint child
	{

		hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(0, 255, 255));
		SetBkColor(hdc, RGB(50, 50, 50));
		return (INT_PTR)CreateSolidBrush(RGB(50, 50, 50));
	}
	break;
	case WM_SIZING:

		//JGN_PostRedisplay();

		break;
	case WM_DROPFILES:

		CustomSurfacesOn = 1;
		was_supercell = 0;
		jgn_supercell = 0;
		Right_Hexagonal = 1;
		want_cyrcle[0] = 'n';
		figure_1 = 1;
		Rod_like = 1;
		nanotube = 0;


		//initialize min and max coordinates of the volum of crystal in Angstrom
		min_xyz[0] = 10000;
		min_xyz[1] = 10000;
		min_xyz[2] = 10000;
		max_xyz[0] = -10000;
		max_xyz[1] = -10000;
		max_xyz[2] = -10000;

		//read the path of the droped file
		DragQueryFile((HDROP)wParam, 0, lpszFile, 500);

		//initialize facetes
		S1 = "100";
		S2 = "110";
		S3 = "111";

		//buffer
		delete s;
		s = new char[SBYTES];

		//LPTSTR to char*
		for (int i = 0; i < 500; i++)
		{
			inpf[i] = (char)lpszFile[i];
			if (inpf[i] == 0)
			{
				i = 1000;
			}
		}

		//print the droped path
		found = std::string(inpf).find(".lmp");
		if (found != std::string::npos)
		{
			ftype = 'l';
		}
		else
		{
			ftype = 'p';
		}


		//open the droped path
		uc_file = fopen(inpf, "r");



		//initialize facetes
		S1i[0] = atoi(S1) / 100;
		S1i[1] = fmod(atoi(S1) / 10, 10);
		S1i[2] = fmod(atoi(S1), 10);

		S2i[0] = atoi(S2) / 100;
		S2i[1] = fmod(atoi(S2) / 10, 10);
		S2i[2] = fmod(atoi(S2), 10);

		S3i[0] = atoi(S3) / 100;
		S3i[1] = fmod(atoi(S3) / 10, 10);
		S3i[2] = fmod(atoi(S3), 10);

		//shorting bullshit
		if (S1[3] != '\0')
		{
			//__asm {
			//	mov esi, [S1]
			//	mov[esi + 3], 0
			//}
			S1[3] = '\0';
		}
		if (S2[3] != '\0') {
			//__asm {
			//	mov esi, [S2]
			//	mov[esi + 3], 0
			//}
			S2[3] = '\0';

		}if (S3[3] != '\0')
		{
			//__asm {
			//	mov esi, [S3]
			//	mov[esi + 3], 0
			//}
			S3[3] = '\0';

		}

		//define Svmax for a proper display (zoom)
		//__asm {
		//	mov esi, [S1v]
		//	mov[Svmax], esi
		//}
		Svmax = S1v;
		//Svmax = S1v;
		if (S2v > Svmax)
		{
			/*__asm {
				mov esi, [S2v]
				mov[Svmax], esi
			}*/
			Svmax = S2v;
		}
		if (S3v > Svmax)
		{
			/*__asm {
				mov esi, [S3v]
				mov[Svmax], esi
			}*/
			Svmax = S3v;
		}
		/*__asm {
			mov esi, [Svmax]
			mov[Svmax_buckup], esi
		}*/
		Svmax_buckup = Svmax;


		JGN_DropFile();

		DragFinish((HDROP)wParam);

		lines_param();
		jgn_file_dropd = 1;


		JGN_PostRedisplay();
		SetForegroundWindow(hWnd);

		break;
	case WM_MOVE:
		GetWindowRect(mnhwnd, glb_rct);
		SetWindowPos(CommandTextField, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35, SWP_ASYNCWINDOWPOS);
		SetWindowPos(CommandTextHistory, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242, SWP_ASYNCWINDOWPOS);

		//JGN_PostRedisplay();
		break;
	case WM_MOVING:

		GetWindowRect(mnhwnd, glb_rct);
		SetWindowPos(CommandTextField, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35, SWP_ASYNCWINDOWPOS);
		SetWindowPos(CommandTextHistory, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242, SWP_ASYNCWINDOWPOS);

		//JGN_PostRedisplay();

		break;
		//////////////////////////////////////
		//
		//Mouse messages
		//

	case WM_LBUTTONDBLCLK:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_LEFT_MOUSE_BUTTON, JGN_DOUBLE_CLICK, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_RBUTTONDBLCLK:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_RIGHT_MOUSE_BUTTON, JGN_DOUBLE_CLICK, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MBUTTONDOWN:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_MIDDLE_MOUSE_BUTTON, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MBUTTONDBLCLK:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_MIDDLE_MOUSE_BUTTON, JGN_DOUBLE_CLICK, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MBUTTONUP:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_MIDDLE_MOUSE_BUTTON, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_MOUSEWHEEL:
		help0 = HIWORD(wParam);
		if ((JGN_CHECK_NEGATIVE_16BIT & help0) == JGN_CHECK_NEGATIVE_16BIT)
		{
			____JGN_MouseFunc(JGN_MOUSE_WHEEL, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		}
		else
		{
			____JGN_MouseFunc(JGN_MOUSE_WHEEL, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		}
		break;
	case WM_MOUSEMOVE:

		if (wParam == -1)
		{

			my_postmessages_count--;

			JGN_PostRedisplay();

		}
		else
		{
			jgn_GlobalMouseCooX = LOWORD(lParam);
			jgn_GlobalMouseCooY = HIWORD(lParam);
			if ((JGN_CHECK_NEGATIVE_16BIT & jgn_GlobalMouseCooX) == JGN_CHECK_NEGATIVE_16BIT)
			{
				jgn_GlobalMouseCooX = jgn_GlobalMouseCooX & 0x7fff;
				help0 = 0x00007fff;
			}
			else
			{
				help0 = 0x00000000;

			}
			if ((JGN_CHECK_NEGATIVE_16BIT & jgn_GlobalMouseCooY) == JGN_CHECK_NEGATIVE_16BIT)
			{
				jgn_GlobalMouseCooY = jgn_GlobalMouseCooY & 0x7fff;
				help1 = 0x00007fff;

			}
			else
			{
				help1 = 0x00000000;
			}
			____JGN_PassiveMotionFunc((int)jgn_GlobalMouseCooX - help0, (int)jgn_GlobalMouseCooY - help1, hWnd);
		}

		break;
	case WM_LBUTTONDOWN:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_LEFT_MOUSE_BUTTON, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		____JGN_PassiveMotionFunc((int)jgn_GlobalMouseCooX, (int)jgn_GlobalMouseCooY, hWnd);

		SetCapture(hWnd);
		break;
	case WM_LBUTTONUP:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_LEFT_MOUSE_BUTTON, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		SetCapture(NULL);
		break;
	case WM_RBUTTONDOWN:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_RIGHT_MOUSE_BUTTON, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		SetCapture(hWnd);
		break;
	case WM_RBUTTONUP:
		jgn_GlobalMouseCooX = LOWORD(lParam);
		jgn_GlobalMouseCooY = HIWORD(lParam);
		____JGN_MouseFunc(JGN_RIGHT_MOUSE_BUTTON, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		SetCapture(NULL);
		break;
		//////////////////////////////////////////
		//
		//Keyboard Messages
		//
	case WM_KEYDOWN:
		____JGN_KeyboardFunc(wParam, JGN_DOWN, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
	case WM_KEYUP:
		____JGN_KeyboardFunc(wParam, JGN_UP, jgn_GlobalMouseCooX, jgn_GlobalMouseCooY, hWnd);
		break;
		//////////////////////////////////////////
		////////////////////////////////////////////////
		////////////////////////////////////////////
	case WM_SIZE:
		____JGN_ReshapeFunc(LOWORD(lParam), HIWORD(lParam), hWnd);
		GetWindowRect(mnhwnd, glb_rct);
		//__asm {
		//	mov esi, [glb_rct]
		//	mov[mnrcpt], esi
		//}
		mnrcpt = (long*)glb_rct;

		mainwndsize[0] = *(mnrcpt + 2) - *mnrcpt;
		mainwndsize[1] = *(mnrcpt + 3) - *(mnrcpt + 1);

		SetWindowPos(CommandTextField, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35, SWP_ASYNCWINDOWPOS);
		SetWindowPos(CommandTextHistory, HWND_TOP, (*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242, SWP_ASYNCWINDOWPOS);
		RedrawWindow(CommandTextField, 0, 0, RDW_NOERASE);

		wasfullscreenflagout++;

		if (wParam == SIZE_MAXIMIZED)
		{
			wasfullscreenflagin++;
			JGN_PostRedisplay();
		}
		if (wasfullscreenflagin == 0)
		{
			wasfullscreenflagout = -1;

		}
		if (wasfullscreenflagout == wasfullscreenflagin)
		{
			JGN_PostRedisplay();
			wasfullscreenflagin = 0;
			wasfullscreenflagout = -1;

		}




		break;
	case WM_EXITSIZEMOVE:
		JGN_PostRedisplay();

		break;
	case WM_COMMAND:

		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:

			hdc = GetDC(hWnd);
			wglMakeCurrent(hdc, NULL);		// release current device context			THIS IS FOR ONE WINDOW ONLY
			wglDeleteContext(hglrc);		// delete rendering context					CHANGE IT
			DeleteDC(hdc);

			if (jgn_trayhwnd != NULL)
			{
				DestroyWindow(jgn_trayhwnd);
			}

			DestroyWindow(hWnd);
			exit(0);
			break;
		case IDM_BUILD_POSCAR:


			DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSE_OUT), hWnd, Choose_Format);

			DialogBox(hInst, MAKEINTRESOURCE(IDD_BUILD_POSCAR), hWnd, Poscar_Build);


			break;
		case IDM_NT:

			max_xyz[0] = crystal[2 + 5 * 0];
			min_xyz[0] = crystal[2 + 5 * 0];

			for (ole3 = 0; ole3 < t * (sized[0])*(sized[1])*(sized[2]); ole3++)
			{
				if (crystal[2 + 5 * ole3] > max_xyz[0])
				{
					max_xyz[0] = crystal[2 + 5 * ole3];
				}
				else if (crystal[2 + 5 * ole3] < min_xyz[0])
				{
					min_xyz[0] = crystal[2 + 5 * ole3];

				}

			}
			sized[0] = custom_sized[0];
			sized[1] = custom_sized[1];
			sized[2] = custom_sized[2];
			jgn_supercell_xyz[0] = sized[0];
			jgn_supercell_xyz[1] = sized[1];
			jgn_supercell_xyz[2] = sized[2];
			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;


			CustomSurfacesOn = 0;
			was_supercell = 1;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			want_cyrcle[0] = 'n';
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 1;

			S1v = 0;
			S2v = 25;
			S3v = 159;
			MakeScroll();

			JGN_PostRedisplay();

			break;
		case IDM_CUSTOM:


			sized[0] = custom_sized[0];
			sized[1] = custom_sized[1];
			sized[2] = custom_sized[2];
			jgn_supercell_xyz[0] = sized[0];
			jgn_supercell_xyz[1] = sized[1];
			jgn_supercell_xyz[2] = sized[2];
			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;

			if (sized[0] / 2 != sized[0] / 2.0)
			{
				xexe[0] = 1;
			}

			if (sized[1] / 2 != sized[1] / 2.0)
			{
				xexe[1] = 1;
			}

			if (sized[2] / 2 != sized[2] / 2.0)
			{
				xexe[2] = 1;
			}

			periodic_table = fopen("periodic_table.jgn", "r");

			crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

			//crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

			for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
				for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
					for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {
						for (ole3 = 0; ole3 < t; ole3++) {
							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

						//selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

							if (inptype == 'd')
							{
								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}

							}
							else if (inptype == 'c')
							{
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
							}



							rewind(periodic_table);

						}
					}
				}
			}


			fclose(periodic_table);




			CustomSurfacesOn = 1;
			was_supercell = 1;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			want_cyrcle[0] = 'n';
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 0;

			JGN_PostRedisplay();


			break;
		case IDM_SUPERCELL:

			CustomSurfacesOn = 0;
			was_supercell = 1;
			jgn_supercell = 1;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;
			want_cyrcle[0] = 'n';
			jgn_supercell_xyz[0] = 10;
			jgn_supercell_xyz[1] = 10;
			jgn_supercell_xyz[2] = 10;
			sized[0] = jgn_supercell_xyz[0];
			sized[1] = jgn_supercell_xyz[1];
			sized[2] = jgn_supercell_xyz[2];

			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;

			periodic_table = fopen("periodic_table.jgn", "r");

			crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

			//crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

			for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
				for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
					for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
						for (ole3 = 0; ole3 < t; ole3++) {
							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

							if (inptype == 'd')
							{
								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}

							}
							else if (inptype == 'c')
							{
								for (ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}

								}
							}



							rewind(periodic_table);

						}
					}
				}
			}


			fclose(periodic_table);

			JGN_PostRedisplay();

			break;
		case IDM_PERSPECTIVE_TUGLE:
			if (perspective_on)
			{

				perspective_on = 0;
				glViewport(0, 0, width, height);//(first 2 sets the lower left corner of the window w h sets width height of the window
				glMatrixMode(GL_PROJECTION);// defines the camera behavior projection is the view point of me
				glLoadIdentity();
				if (width <= height)
				{
					glOrtho(
						-1.05, +1.05,
						-1.05 * (GLfloat)height / (GLfloat)width, +1.05 * (GLfloat)height / (GLfloat)width,
						-10.0, 10.0);
					dipleft = -1;


				}
				else
				{
					glOrtho(
						-1.05 * (GLfloat)width / (GLfloat)height, +1.05 * (GLfloat)width / (GLfloat)height,
						-1.05, +1.05,
						-10.0, 10.0);
					dipleft = -(GLfloat)width / (GLfloat)height;

				}
				glMatrixMode(GL_MODELVIEW);


			}
			else
			{
				perspective_on = 1;

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				//gluPerspective(60, (float)width / (float)height, 0.001, 100);
				glMatrixMode(GL_MODELVIEW);

			}

			JGN_PostRedisplay();
			break;
		case IDM_ROD_LIKE:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];


				periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

				//crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			CustomSurfacesOn = 0;
			Right_Hexagonal = 1;
			jgn_supercell = 0;
			figure_1 = 1;
			Rod_like = -1;
			nanotube = 0;
			Svmax = 50;
			S1v = 11;
			S2v = 17;
			S3v = 23;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 1;
			S1 = "100";
			S2 = "110";
			S3 = "111";
			want_cyrcle[0] = 'n';

			lines_param();

			JGN_PostRedisplay();

			break;
		case IDM_NORMAL:
			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];

				periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			Scase = 1;
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 0;

			Svmax = 40;
			S1v = 25;
			S2v = 30;
			S3v = 40;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 1;
			S1 = "100";
			S2 = "110";
			S3 = "111";
			want_cyrcle[0] = 'n';

			Scase = 1;

			lines_param();

			JGN_PostRedisplay();
			break;
		case IDM_RIGHT_HEXAGONAL:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];

				periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Rod_like = 1;
			figure_1 = 1;
			Right_Hexagonal = -1;
			Svmax = 50;
			S1v = 8;
			S2v = 8;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 0;
			Right_Hexagonal_height = 20;
			S1 = "100";
			S2 = "110";
			S3 = "000";
			want_cyrcle[0] = 'n';

			lines_param();

			JGN_PostRedisplay();



			break;

		case IDM_FIGURE_1:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];

				periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Scase = 1;
			figure_1 = -1;
			Right_Hexagonal = 1;
			Rod_like = 1;
			nanotube = 0;

			Svmax = 50;
			S1v = 15;
			S2v = 30;
			S3v = 40;
			S1i[0] = 1;
			S2i[0] = 1;
			S3i[0] = 1;
			S1 = "100";
			S2 = "110";
			S3 = "111";
			want_cyrcle[0] = 'n';

			lines_param();

			JGN_PostRedisplay();

			break;

		case IDM_TUT:

			DialogBox(hInst, MAKEINTRESOURCE(IDD_TUT), hWnd, TUT);

			break;


		case IDM_WANT_SPHERE:

			if (hWndCommandLine != 0)
			{
				ShowWindow(hWndCommandLine, SW_HIDE);

			}

			if (was_supercell)
			{
				was_supercell = 0;
				xexe[0] = 0;
				xexe[1] = 0;
				xexe[2] = 0;
				sized[0] = jgn_supercell_xyz[0];
				sized[1] = jgn_supercell_xyz[1];
				sized[2] = jgn_supercell_xyz[2];


				periodic_table = fopen("periodic_table.jgn", "r");

				crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
				selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

				//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));

				for (ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2; ole4++) {
					for (ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2; ole2++) {
						for (ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2; ole++) {
							for (ole3 = 0; ole3 < t; ole3++) {
								crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
							//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos

							//selective dynamics
								selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
								selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
								selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][0] = direct[0+5*ole3];
								crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos

								if (inptype == 'd')
								{
									//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}

								}
								else if (inptype == 'c')
								{
									for (ole1 = 0; ole1 < 3; ole1++) {
										crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians
										crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];//cartesians

										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
										{
											min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}
										if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
										{
											max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

										}

									}
								}


								rewind(periodic_table);

							}
						}
					}
				}


				fclose(periodic_table);

			}
			rad = 20;
			want_cyrcle[0] = 'y';
			CustomSurfacesOn = 0;
			jgn_supercell = 0;
			Right_Hexagonal = 1;
			figure_1 = 1;
			Rod_like = 1;
			nanotube = 0;


			JGN_PostRedisplay();
			break;


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_ERASEBKGND: // return 1 so it doesnt flick, prevents to erase window content
		return 1;
		break;

	case WM_DESTROY:
		//PostQuitMessage(0);


		hdc = GetDC(hWnd);
		wglMakeCurrent(hdc, NULL);		// release current device context			THIS IS FOR ONE WINDOW ONLY
		wglDeleteContext(hglrc);		// delete rendering context					CHANGE IT
		DeleteDC(hdc);



		if (jgn_trayhwnd != NULL)
		{
			DestroyWindow(jgn_trayhwnd);
		}
		if (hWndCommandLine != 0)
		{
			DestroyWindow(hWndCommandLine);

		}
		//delete(S1);
		//delete(S2);
		//delete(S3);
		//delete(s1);
		//delete(NewPC);
		//delete(PCtype);
		//delete(lpszFile);
		//delete(new_num_atoms);
		//delete(atomic_number);
		//delete(an_and_aw);
		//delete(atoms);
		//delete(ea);
		//delete(my_direct);
		//delete(uccartesian);
		//delete(crystal);
		//delete(atoms_to_print);



		exit(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}



	//JGN_DisplayF(JGN_Global_Draw);

	return 0;
}


LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{

	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	LPTSTR  ttt = CommandBuffer;
	FILE* periodic_table;
	loop = 0;
	int isngtv = 0;


	int listwrite[testsc];

	for (int i = 0; i < testsc; i++)
	{
		listwrite[i] = 1;
	}

	if (GetFocus() == CommandTextField)
	{
		GetWindowText(CommandTextField, ttt, 500);
		int len = lstrlen(ttt);
		if (len == 0)
		{
			for (int i = 0; i < testsc; i++)
			{
				listwrite[i] = 0;
			}
		}

		for (int j = 0; j < testsc; j++)
		{
			for (int i = 0; i < len; i++)
			{

				if (ttt[i] != test1[j][i] && ttt[i] != test1low[j][i])
				{
					listwrite[j] = 0;
				}
			}
		}



		DestroyWindow(hWndList);
		int itemscnt = 0;
		for (int i = 0; i < testsc; i++)
		{
			if (listwrite[i] == 1)
			{
				itemscnt++;
			}
		}
		if (itemscnt > 6)
		{
			HINSTANCE hinst111 = (HINSTANCE)GetWindowLong(mnhwnd, GWLP_HINSTANCE);
			hWndList = CreateWindow(L"LISTBOX",
				0, WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | WS_VSCROLL,
				0, 222 - 20 * 6, 250, 20 * 6,
				mnhwnd, NULL, hinst111, NULL);
		}
		else
		{
			/////////////////////////////////////////////
						//HINSTANCE hinst111 = (HINSTANCE)GetWindowLong(mnhwnd, GWL_HINSTANCE);

			hWndList = CreateWindow(L"LISTBOX",
				0, WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | WS_VSCROLL,
				0, 222 - 20 * itemscnt, 250, 20 * itemscnt,
				CommandTextHistory, NULL, NULL, NULL);
			///////////////////////////////////////////

		}



		ShowWindow(hWndList, SW_HIDE);

		int another1 = 0;

		for (int i = 0; i < testsc; i++)
		{
			if (listwrite[i] == 1)
			{
				boxlistmap[another1] = test1[i];
				another1++;
				SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)helplist[i]);

			}
		}



		if (wParam == 256)
		{

			if (p->vkCode == 40)
			{
				itemsel++;
				if (itemsel > itemscnt - 1)
				{
					itemsel = itemscnt - 1;
				}
				SendMessage(hWndList, LB_SETSEL, TRUE, itemsel);

			}
			else if (p->vkCode == 38)
			{

				itemsel--;
				if (itemsel < 0)
				{
					itemsel = 0;
				}
				SendMessage(hWndList, LB_SETSEL, TRUE, itemsel);

			}
			else if (p->vkCode == 13)
			{

				if (itemsel != -1)
				{
					predicted = 1;
					SendMessage(CommandTextField, EM_SETSEL, 0, -1);
					char *hasdlf = boxlistmap[itemsel];
					mbstowcs(widechar, hasdlf, 50);
					i = 0;
					while (hasdlf[i] != '\0')
					{

						SendMessage(CommandTextField, WM_CHAR, (TCHAR)hasdlf[i], 0);
						itemsel = -1;

						i++;
					}
					db = 1;

					goto peintit1;
				}
			}

		}
		else
		{
			if (itemsel != -1)
			{
				SendMessage(hWndList, LB_SETSEL, TRUE, itemsel);
			}


		}

		ShowWindow(hWndList, SW_SHOW);
		ole5 = 0;
		for (int i = 0; i < testsc; i++)
		{
			if (listwrite[i] == 1)
			{
				ole5++;
			}
		}

		if (ole5 == 0)
		{
			if (hWndList != 0)
			{
				DestroyWindow(hWndList);
				itemsel = -1;
			}
		}

	}





	if (wParam == 256)
	{
		if (p->vkCode == 13)
		{
			if (GetFocus() == CommandTextField)
			{
				GetWindowText(CommandTextField, ttt, 500);

				endcheck = 1;


				//char *test1 = "fopen(";
				for (i = 0; i < 6; i++)
				{
					if (test1[5][i] == ttt[i])
					{

					}
					else
					{
						i = 100;

					}
				}
				if (i == 6)
				{
					okrender = 1;

					help = (char*)(ttt + 6);

					if (help[0] != '\"')
					{
						cout << "expecting a \"" << endl;
						okrender = 0;
						goto peintit;
					}

					help = help + 2;
					ole = 0;
					ole1 = 0;
					while (help[0] != '\"')
					{
						ole++;
						help = help + 2;
						if (help[0] == '\0')
						{

							ole1 = 1;
						}
					}
					if (ole1 == 1)
					{
						cout << "expecting a \"" << endl;
						okrender = 0;
						goto peintit;
					}
					else
					{
						cout << ole << endl;
						help = help - 2 * ole;
						jgncmdfpath = (char*)malloc(sizeof(char)*(ole + 1));

						for (int i = 0; i < ole; i++)
						{
							jgncmdfpath[i] = help[0];
							help = help + 2;
						}
						jgncmdfpath[ole] = 0;
						jgncmdfile = fopen(jgncmdfpath, "r");


						fgets(jgncmdfline, 100, jgncmdfile);

						while ((jgncmdfline[0] != 'e' && jgncmdfline[1] != 'n' && jgncmdfline[2] != 'd'))
						{
							for (i = 0; i < 100; i++)
							{
								ttt[i] = jgncmdfline[i];
								if (jgncmdfline[i] == 0)
								{
									break;
								}
							}

							jgnCommands(ttt, 0);
							fgets(jgncmdfline, 100, jgncmdfile);

						}
						fclose(jgncmdfile);
						free(jgncmdfpath);
						//jgncmdfpath = 0;
					}
					//goto peintit;

					//return 0;
				}
				else
				{

					jgnCommands(ttt, 1);
				}

			peintit:

				DestroyWindow(CommandTextField);



				CommandTextField = CreateWindow(L"EDIT",
					0, WS_VISIBLE | WS_POPUP | ES_MULTILINE | ES_AUTOHSCROLL,
					(*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35,
					mnhwnd, NULL, NULL, NULL);

				oldEditProc = (WNDPROC)SetWindowLongPtr(CommandTextField, GWLP_WNDPROC, (LONG_PTR)WndProcEditBox);

				SendMessage(CommandTextField, WM_SETFONT, (WPARAM)fOnt, TRUE);

			peintit1:

				if (okrender)
				{
					SendMessage(CommandTextHistory, EM_SETREADONLY, FALSE, NULL);

					okrender = 0;

					SendMessage(CommandTextHistory, EM_SETSEL, 0, -1);
					SendMessage(CommandTextHistory, EM_SETSEL, -1, 0);

					for (i = 0; i < 50; i++)
					{

						if (i == 0 && ttt[0] == 13)
						{

						}
						else
						{
							if (ttt[i] == 0)
							{
								i = 100;
							}
							else
							{
								SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ttt[i], 0);


							}
						}
					}

					SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ucender[0], 0);

					SetFocus(CommandTextField);
					SendMessage(CommandTextHistory, EM_SETREADONLY, TRUE, NULL);

					for (i = 0; i < 50; i++)
					{
						CommandBuffer[i] = 0;

					}

				}
				else
				{
					SetFocus(CommandTextField);
				}



			}
		}

	}



	return 0;
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///////////////////////////////////////////////////////////
//
//Tray
//
HWND JGN_CreateTray(string traytitle, HINSTANCE hInstance)
{
	// prepare for XP style controls
	InitCommonControls();

	// store instance handle and create dialog
	HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DLG_DIALOG),
		NULL, (DLGPROC)DlgProc);

	if (!hWnd)
	{
		perror("Could Not Create System Tray");
		return FALSE;
	}

	jgn_trayhwnd = hWnd;

	// Fill the NOTIFYICONDATA structure and call Shell_NotifyIcon

	// zero the structure - note:	Some Windows funtions require this but
	//								I can't be bothered which ones do and
	//								which ones don't.
	ZeroMemory(&niData, sizeof(NOTIFYICONDATA));

	// get Shell32 version number and set the size of the structure
	//		note:	the MSDN documentation about this is a little
	//				dubious and I'm not at all sure if the method
	//				bellow is correct

	ULONGLONG ullVersion = GetDllVersion(_T("Shell32.dll"));

	if (ullVersion >= MAKEDLLVERULL(5, 0, 0, 0))
		niData.cbSize = sizeof(NOTIFYICONDATA);
	else niData.cbSize = NOTIFYICONDATA_V2_SIZE;

	// the ID number can be anything you choose
	niData.uID = JGN_TRAYICON;

	// state which structure members are valid
	niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	// load the icon
	niData.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(JGN_TRAYICON),
		IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);

	// the window to send messages to and the message to send
	//		note:	the message value should be in the
	//				range of WM_APP through 0xBFFF
	niData.hWnd = hWnd;
	niData.uCallbackMessage = JGN_TRAYMSG;

	// tooltip message
	int i = 0;
	while (traytitle[i] != '\0' && i < 100)
	{
		szTitle[i] = traytitle[i];
		i++;
	}
	lstrcpyn(niData.szTip, szTitle, sizeof(niData.szTip) / sizeof(TCHAR));

	Shell_NotifyIcon(NIM_ADD, &niData);

	// free icon handle
	if (niData.hIcon && DestroyIcon(niData.hIcon))
		niData.hIcon = NULL;

	// call ShowWindow here to make the dialog initially visible

	return hWnd;
}



ULONGLONG GetDllVersion(LPCTSTR lpszDllName)
{
	ULONGLONG ullVersion = 0;
	HINSTANCE hinstDll;
	hinstDll = LoadLibrary(lpszDllName);
	if (hinstDll)
	{
		DLLGETVERSIONPROC pDllGetVersion;
		pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");
		if (pDllGetVersion)
		{
			DLLVERSIONINFO dvi;
			HRESULT hr;
			ZeroMemory(&dvi, sizeof(dvi));
			dvi.cbSize = sizeof(dvi);
			hr = (*pDllGetVersion)(&dvi);
			if (SUCCEEDED(hr))
				ullVersion = MAKEDLLVERULL(dvi.dwMajorVersion, dvi.dwMinorVersion, 0, 0);
		}
		FreeLibrary(hinstDll);
	}
	return ullVersion;
}




INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case JGN_TRAYMSG:
		switch (lParam)
		{
		case WM_LBUTTONDBLCLK:
			ShowWindow(hWnd, SW_RESTORE);
			break;
		case WM_RBUTTONDOWN:
		case WM_CONTEXTMENU:
			ShowContextMenu(hWnd);
		}
		break;
	case WM_SYSCOMMAND:
		if ((wParam & 0xFFF0) == SC_MINIMIZE)
		{
			ShowWindow(hWnd, SW_HIDE);
			return 1;
		}
		else if (wParam == IDM_ABOUT)
		{
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
		}



		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		case SWM_SHOW:
			ShowWindow(hWnd, SW_RESTORE);
			break;
		case SWM_HIDE:
		case IDOK:
			ShowWindow(hWnd, SW_HIDE);
			break;
		case SWM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		}
		return 1;
	case WM_INITDIALOG:
		return OnInitDialog(hWnd);
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		niData.uFlags = 0;
		Shell_NotifyIcon(NIM_DELETE, &niData);
		PostQuitMessage(0);
		break;
	}
	return 0;
}


void ShowContextMenu(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	HMENU hMenu = CreatePopupMenu();
	if (hMenu)
	{
		if (IsWindowVisible(hWnd))
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_HIDE, _T("Hide"));
		else
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SHOW, _T("Show"));
		InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, _T("Exit"));

		// note:	must set window to the foreground or the
		//			menu won't disappear when it should
		SetForegroundWindow(hWnd);

		TrackPopupMenu(hMenu, TPM_BOTTOMALIGN,
			pt.x, pt.y, 0, hWnd, NULL);
		DestroyMenu(hMenu);
	}
}


BOOL OnInitDialog(HWND hWnd)
{
	HMENU hMenu = GetSystemMenu(hWnd, FALSE);
	if (hMenu)
	{
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, IDM_ABOUT, _T("About"));
	}
	HICON hIcon = (HICON)LoadImage(hInst,
		MAKEINTRESOURCE(JGN_TRAYICON),
		IMAGE_ICON, 0, 0, LR_SHARED | LR_DEFAULTSIZE);
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	return TRUE;
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///////////////////////////////////////////////////////
//
//General
//


//The Main Loop
void JGN_MainLoop()
{
	MSG msg;

	HACCEL hAccelTable;

	hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_JGNCLASS0));

	jgn_runing = 1;

	//UINT_PTR timerId = SetTimer(NULL, NULL, 1, NULL);

	while (GetMessage(&msg, NULL, 0, 0))
		//while (PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE))
	{

		if ((!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) || !IsDialogMessage(msg.hwnd, &msg)))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Poscar_Build(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{

			EndDialog(hDlg, LOWORD(wParam));

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Choose_Format(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_CHOOSE_POSCAR)
		{
			EndDialog(hDlg, LOWORD(wParam));
			BuildPoscar(NewPC);


			return (INT_PTR)1;
		}
		else if (LOWORD(wParam) == ID_CHOOSE_LAMMPS)
		{
			EndDialog(hDlg, LOWORD(wParam));
			BuildLammps(NewPC);


			return (INT_PTR)2;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			return (INT_PTR)-1;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TUT(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		ShowWindow(hDlg, SW_SHOW);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void jgnCommands(LPTSTR ttt, int d)
{
	FILE* periodic_table;
	int isngtv = 0;
	//char *test1 = "Vector(";
	for (i = 0; i < 7; i++)
	{
		if (test1[0][i] == ttt[i])
		{

		}
		else
		{
			i = 100;

		}
	}
	if (i == 7)
	{

		okrender = 1;
		CustomSurfacesCount++;

		CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
		CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
		CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0;
		help = (char*)(ttt + 7);
		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalh = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalh = 10 * crystalh + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalh = -crystalh;
		}

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[0][0] * crystalh;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[0][1] * crystalh;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[0][2] * crystalh;

		help += 2;
		isngtv = 0;


		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalk = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalk = 10 * crystalk + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalk = -crystalk;
		}
		help += 2;
		isngtv = 0;

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[1][0] * crystalk;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[1][1] * crystalk;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[1][2] * crystalk;

		if (help[0] >= 48 && help[0] <= 57)
		{
			crystall = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystall = 10 * crystall + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			crystall = -crystall;
		}

		CustomSurfaces[CustomSurfacesCount - 1][0] += ijk[2][0] * crystall;
		CustomSurfaces[CustomSurfacesCount - 1][1] += ijk[2][1] * crystall;
		CustomSurfaces[CustomSurfacesCount - 1][2] += ijk[2][2] * crystall;

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		CustomSurfaces[CustomSurfacesCount - 1][0] = CustomSurfaces[CustomSurfacesCount - 1][0] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][1] = CustomSurfaces[CustomSurfacesCount - 1][1] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][2] = CustomSurfaces[CustomSurfacesCount - 1][2] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));

		help += 2;
		isngtv = 0;



		if (help[0] >= 48 && help[0] <= 57)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;

		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
		}
		help += 2;
		isngtv = 0;


		if (okrender == 0)
		{
			CustomSurfacesCount--;
		}

		goto peintit;


	}
	//render on/off
	for (i = 0; i < 6; i++)
	{
		if (test1[9][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		help = (char*)(ttt + 7);

		jgn::string option = LPTSTR2string((LPTSTR)help, ')', 2);

		if (option == "on")
		{
			render_is_on = true;
		}
		else if (option == "of")
		{
			render_is_on = false;
		}
		else
		{
			okrender = 0;
			return;
		}
		goto peintit;

	}
	//"rand("
	for (i = 0; i < 5; i++)
	{
		if (test1[8][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 5)
	{
		okrender = 1;

		float r = 0;

		help = (char*)(ttt + 5);

		jgn::string rstr = LPTSTR2string((LPTSTR)help, ')');

		if (rstr.isnumber())
		{
			ole = t * sized[0] * sized[1] * sized[2];

			r = stof(rstr);
			srand(time(NULL));
#pragma omp parallel for firstprivate(ole, r)
			for (int ole1 = 0; ole1 < ole; ole1++)
			{
				crystal[2 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
				crystal[3 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
				crystal[4 + 5 * ole1] += r * (2 * (rand() / (float)RAND_MAX) - 1);
			}
		}
		else
		{
			okrender = 0;
			return;
		}

		goto peintit;

	}
	//"Plane("
	for (i = 0; i < 6; i++)
	{
		if (test1[4][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{

		okrender = 1;
		CustomSurfacesCount++;

		CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
		CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
		CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
		CustomSurfaces[CustomSurfacesCount - 1][3] = 0;
		crystalh = 0;
		crystalk = 0;
		crystall = 0;
		help = (char*)(ttt + 6);
		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalh = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalh = 10 * crystalh + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;


			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalh = -crystalh;
		}




		help += 2;
		isngtv = 0;


		if (help[0] >= 48 && help[0] <= 57)
		{
			crystalk = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;

		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystalk = 10 * crystalk + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystalk = -crystalk;
		}
		help += 2;
		isngtv = 0;





		if (help[0] >= 48 && help[0] <= 57)
		{
			crystall = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		loop = 0;
		while (help[0] != ',' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				crystall = 10 * crystall + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		if (isngtv)
		{
			crystall = -crystall;
		}

		if (crystalh == 0)
		{
			if (crystalk == 0)
			{
				if (crystall == 0)//000 ok
				{
					CustomSurfacesCount--;
					okrender = 0;
					return;
				}
				else//00l ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[0][1] * ijk[1][2] - ijk[0][2] * ijk[1][1];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[0][0] * ijk[1][2] + ijk[0][2] * ijk[1][0];
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[0][0] * ijk[1][1] - ijk[0][1] * ijk[1][0];


					CustomSurfaces[CustomSurfacesCount - 1][0] = crystall * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystall * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystall * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
			}
			else
			{
				if (crystall == 0)//0k0 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = -ijk[0][1] * ijk[2][2] + ijk[0][2] * ijk[2][1];
					CustomSurfaces[CustomSurfacesCount - 1][1] = ijk[0][0] * ijk[2][2] - ijk[0][2] * ijk[2][0];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -ijk[0][0] * ijk[2][1] + ijk[0][1] * ijk[2][0];

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
				else//0kl ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[0][1] * (ijk[1][2] / crystalk - ijk[2][2] / crystall) - ijk[0][2] * (ijk[1][1] / crystalk - ijk[2][1] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[0][0] * (ijk[1][2] / crystalk - ijk[2][2] / crystall) + ijk[0][2] * (ijk[1][0] / crystalk - ijk[2][0] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[0][0] * (ijk[1][1] / crystalk - ijk[2][1] / crystall) - ijk[0][1] * (ijk[1][0] / crystalk - ijk[2][0] / crystall);

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];
				}
			}
		}
		else
		{
			if (crystalk == 0)
			{
				if (crystall == 0)//h00 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[1][1] * ijk[2][2] - ijk[1][2] * ijk[2][1];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[1][0] * ijk[2][2] + ijk[1][2] * ijk[2][0];
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[1][0] * ijk[2][1] - ijk[1][1] * ijk[2][0];

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalh * CustomSurfaces[CustomSurfacesCount - 1][2];

				}
				else//h0l ok
				{


					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[1][1] * (ijk[0][2] / crystalh - ijk[2][2] / crystall) - ijk[1][2] * (ijk[0][1] / crystalh - ijk[2][1] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[1][0] * (ijk[0][2] / crystalh - ijk[2][2] / crystall) + ijk[1][2] * (ijk[0][0] / crystalh - ijk[2][0] / crystall);
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[1][0] * (ijk[0][1] / crystalh - ijk[2][1] / crystall) - ijk[1][1] * (ijk[0][0] / crystalh - ijk[2][0] / crystall);

					CustomSurfaces[CustomSurfacesCount - 1][0] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -crystalh * crystall*CustomSurfaces[CustomSurfacesCount - 1][2];


				}
			}
			else
			{
				if (crystall == 0)//hk0 ok
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = ijk[2][1] * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) - ijk[2][2] * (ijk[0][1] / crystalh - ijk[1][1] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -ijk[2][0] * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) + ijk[2][2] * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][2] = ijk[2][0] * (ijk[0][1] / crystalh - ijk[1][1] / crystalk) - ijk[2][1] * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);

					CustomSurfaces[CustomSurfacesCount - 1][0] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = crystalk * crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];
				}
				else//hkl
				{
					CustomSurfaces[CustomSurfacesCount - 1][0] = (ijk[0][1] / crystalh - ijk[2][1] / crystall) * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) - (ijk[0][2] / crystalh - ijk[2][2] / crystall) * (ijk[0][1] / crystalh - ijk[1][1] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][1] = -(ijk[0][0] / crystalh - ijk[2][0] / crystall) * (ijk[0][2] / crystalh - ijk[1][2] / crystalk) + (ijk[0][2] / crystalh - ijk[2][2] / crystall) * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);
					CustomSurfaces[CustomSurfacesCount - 1][2] = (ijk[0][0] / crystalh - ijk[2][0] / crystall) * (ijk[0][1] / crystalh - ijk[1][1] / crystalk) - (ijk[0][1] / crystalh - ijk[2][1] / crystall) * (ijk[0][0] / crystalh - ijk[1][0] / crystalk);

					CustomSurfaces[CustomSurfacesCount - 1][0] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][0];
					CustomSurfaces[CustomSurfacesCount - 1][1] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][1];
					CustomSurfaces[CustomSurfacesCount - 1][2] = -crystall * crystalk*crystalh*CustomSurfaces[CustomSurfacesCount - 1][2];

				}
			}
		}



		/*if (crystalh == 0)
		{
		if (JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[0][1], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0], 0, -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0], -ijk[0][0], 0) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[0][0], 0, ijk[0][2], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0] , -ijk[0][0], ijk[0][1], helping1*ijk[0][1] - helping2*ijk[0][0], 0) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[0][0], ijk[0][1], 0, ijk[0][2], 0, helping1*ijk[0][2] - helping3*ijk[0][0] , ijk[0][1], -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0]) / JGN_Det3x3(ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][2], 0, -ijk[0][0], ijk[0][1], -ijk[0][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[0][2]-helping3*ijk[0][1], ijk[0][2], -ijk[0][1], 0, ijk[0][1], ijk[0][2], helping1*ijk[0][1]-helping2*ijk[0][0], -ijk[0][0], 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[0][2] - helping3*ijk[0][1], -ijk[0][1], ijk[0][0], 0, ijk[0][2], ijk[0][1], helping1*ijk[0][1] - helping2*ijk[0][0] , 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[0][2], helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][0], ijk[0][1], 0, ijk[0][1], -ijk[0][0], helping1*ijk[0][1] - helping2*ijk[0][0]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][0], ijk[0][1], ijk[0][2], ijk[0][1], -ijk[0][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][2], -ijk[0][1], helping1*ijk[0][2] - helping3*ijk[0][0], 0, -ijk[0][0], 0, ijk[0][1], ijk[0][2]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[0][2] - helping3*ijk[0][1], -ijk[0][1], ijk[0][2], helping1*ijk[0][2] - helping3*ijk[0][0], -ijk[0][0], ijk[0][0], 0, ijk[0][2]) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[0][2], helping2*ijk[0][2] - helping3*ijk[0][1], ijk[0][2], 0, helping1*ijk[0][2] - helping3*ijk[0][0], ijk[0][0], ijk[0][1], 0) / JGN_Det3x3(0, ijk[0][2], -ijk[0][1], ijk[0][2], 0, -ijk[0][0], ijk[0][0], ijk[0][1], ijk[0][2]);
		}

		}

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		if (crystalk == 0)
		{
		if (JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[1][1], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], 0, -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0], -ijk[1][0], 0) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[1][0], 0, ijk[1][2], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], -ijk[1][0], ijk[1][1], helping1*ijk[1][1] - helping2*ijk[1][0], 0) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[1][0], ijk[1][1], 0, ijk[1][2], 0, helping1*ijk[1][2] - helping3*ijk[1][0], ijk[1][1], -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0]) / JGN_Det3x3(ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][2], 0, -ijk[1][0], ijk[1][1], -ijk[1][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], -ijk[1][1], 0, ijk[1][1], ijk[1][2], helping1*ijk[1][1] - helping2*ijk[1][0], -ijk[1][0], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[1][2] - helping3*ijk[1][1], -ijk[1][1], ijk[1][0], 0, ijk[1][2], ijk[1][1], helping1*ijk[1][1] - helping2*ijk[1][0], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[1][2], helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][0], ijk[1][1], 0, ijk[1][1], -ijk[1][0], helping1*ijk[1][1] - helping2*ijk[1][0]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][0], ijk[1][1], ijk[1][2], ijk[1][1], -ijk[1][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]) != 0)
		{
		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], -ijk[1][1], helping1*ijk[1][2] - helping3*ijk[1][0], 0, -ijk[1][0], 0, ijk[1][1], ijk[1][2]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[1][2] - helping3*ijk[1][1], -ijk[1][1], ijk[1][2], helping1*ijk[1][2] - helping3*ijk[1][0], -ijk[1][0], ijk[1][0], 0, ijk[1][2]) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[1][2], helping2*ijk[1][2] - helping3*ijk[1][1], ijk[1][2], 0, helping1*ijk[1][2] - helping3*ijk[1][0], ijk[1][0], ijk[1][1], 0) / JGN_Det3x3(0, ijk[1][2], -ijk[1][1], ijk[1][2], 0, -ijk[1][0], ijk[1][0], ijk[1][1], ijk[1][2]);
		}
		}

		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		if (crystall == 0)
		{
		if (JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(0, ijk[2][1], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], 0, -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0], -ijk[2][0], 0) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(ijk[2][0], 0, ijk[2][2], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], -ijk[2][0], ijk[2][1], helping1*ijk[2][1] - helping2*ijk[2][0], 0) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(ijk[2][0], ijk[2][1], 0, ijk[2][2], 0, helping1*ijk[2][2] - helping3*ijk[2][0], ijk[2][1], -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0]) / JGN_Det3x3(ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][2], 0, -ijk[2][0], ijk[2][1], -ijk[2][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], -ijk[2][1], 0, ijk[2][1], ijk[2][2], helping1*ijk[2][1] - helping2*ijk[2][0], -ijk[2][0], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[2][2] - helping3*ijk[2][1], -ijk[2][1], ijk[2][0], 0, ijk[2][2], ijk[2][1], helping1*ijk[2][1] - helping2*ijk[2][0], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[2][2], helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][0], ijk[2][1], 0, ijk[2][1], -ijk[2][0], helping1*ijk[2][1] - helping2*ijk[2][0]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][0], ijk[2][1], ijk[2][2], ijk[2][1], -ijk[2][0], 0);
		}
		else if (JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]) != 0)
		{

		CustomSurfaces[CustomSurfacesCount - 1][0] = JGN_Det3x3(helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], -ijk[2][1], helping1*ijk[2][2] - helping3*ijk[2][0], 0, -ijk[2][0], 0, ijk[2][1], ijk[2][2]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		CustomSurfaces[CustomSurfacesCount - 1][1] = JGN_Det3x3(0, helping2*ijk[2][2] - helping3*ijk[2][1], -ijk[2][1], ijk[2][2], helping1*ijk[2][2] - helping3*ijk[2][0], -ijk[2][0], ijk[2][0], 0, ijk[2][2]) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		CustomSurfaces[CustomSurfacesCount - 1][2] = JGN_Det3x3(0, ijk[2][2], helping2*ijk[2][2] - helping3*ijk[2][1], ijk[2][2], 0, helping1*ijk[2][2] - helping3*ijk[2][0], ijk[2][0], ijk[2][1], 0) / JGN_Det3x3(0, ijk[2][2], -ijk[2][1], ijk[2][2], 0, -ijk[2][0], ijk[2][0], ijk[2][1], ijk[2][2]);
		}
		}*/


		helping1 = CustomSurfaces[CustomSurfacesCount - 1][0];
		helping2 = CustomSurfaces[CustomSurfacesCount - 1][1];
		helping3 = CustomSurfaces[CustomSurfacesCount - 1][2];

		CustomSurfaces[CustomSurfacesCount - 1][0] = CustomSurfaces[CustomSurfacesCount - 1][0] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][1] = CustomSurfaces[CustomSurfacesCount - 1][1] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));
		CustomSurfaces[CustomSurfacesCount - 1][2] = CustomSurfaces[CustomSurfacesCount - 1][2] / sqrt(pow(helping1, 2) + pow(helping2, 2) + pow(helping3, 2));

		help += 2;
		isngtv = 0;



		if (help[0] >= 48 && help[0] <= 57)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
		}
		else if (help[0] == '-')
		{
			isngtv = 1;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)

		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;
			}
		}
		loop = 0;
		if (isngtv)
		{
			CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
		}
		help += 2;
		isngtv = 0;


		if (okrender == 0)
		{
			CustomSurfacesCount--;
		}

		goto peintit;


	}



	//"PlaneH("
	/*for (i = 0; i < 7; i++)
	{
	if (test5[i] == ttt[i])
	{

	}
	else
	{
	i = 100;
	}
	}
	if (i == 7)
	{
	okrender = 1;
	CustomSurfacesCount++;

	CustomSurfaces = (float**)realloc(CustomSurfaces, sizeof(float*)*CustomSurfacesCount);
	CustomSurfaces[CustomSurfacesCount - 1] = (float*)malloc(sizeof(float) * 4);
	CustomSurfaces[CustomSurfacesCount - 1][0] = 0;
	CustomSurfaces[CustomSurfacesCount - 1][1] = 0;
	CustomSurfaces[CustomSurfacesCount - 1][2] = 0;
	CustomSurfaces[CustomSurfacesCount - 1][3] = 0;

	int u = 0;
	int v = 0;

	help = (char*)(ttt + 7);
	if (help[0] >= 48 && help[0] <= 57)
	{
	u = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;
	}
	help = help + 2;
	loop = 0;
	while (help[0] != ',' && loop<6)
	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	u = 10 * u + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;


	}
	}
	loop = 0;
	if (isngtv)
	{
	u = -u;
	}
	help += 2;
	isngtv = 0;


	if (help[0] >= 48 && help[0] <= 57)
	{
	v = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;

	}
	help = help + 2;
	while (help[0] != ',' && loop<6)

	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	v = 10 * v + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;


	}
	}
	loop = 0;
	if (isngtv)
	{
	v = -v;
	}
	help += 2;
	isngtv = 0;

	CustomSurfaces[CustomSurfacesCount - 1][0] = u;
	CustomSurfaces[CustomSurfacesCount - 1][1] = u/sqrt(3) + v*2.0 / sqrt(3);

	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][2] = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;

	}
	help = help + 2;
	while (help[0] != ',' && loop<6)

	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][2] = 10 * CustomSurfaces[CustomSurfacesCount - 1][2] + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;

	}
	}
	loop = 0;
	if (isngtv)
	{
	CustomSurfaces[CustomSurfacesCount - 1][2] = -CustomSurfaces[CustomSurfacesCount - 1][2];
	}
	help += 2;
	isngtv = 0;



	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][3] = help[0] - 48;
	}
	else if (help[0] == '-')
	{
	isngtv = 1;
	}
	else
	{
	okrender = 0;

	}
	help = help + 2;
	while (help[0] != ')' && loop<6)

	{
	loop++;
	if (help[0] >= 48 && help[0] <= 57)
	{
	CustomSurfaces[CustomSurfacesCount - 1][3] = 10 * CustomSurfaces[CustomSurfacesCount - 1][3] + help[0] - 48;
	help += 2;
	}
	else
	{
	okrender = 0;

	}
	}
	loop = 0;
	if (isngtv)
	{
	CustomSurfaces[CustomSurfacesCount - 1][3] = -CustomSurfaces[CustomSurfacesCount - 1][3];
	}
	help += 2;
	isngtv = 0;


	if (okrender == 0)
	{
	CustomSurfacesCount--;
	}
	JGN_PostRedisplay();

	goto peintit;

	}*/





	//char *test2 = "Clean";
	for (i = 0; i < 5; i++)
	{
		if (test1[1][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}

	if (i == 5)
	{
		okrender = 1;
		CustomSurfacesCount = 0;
		for (i = 0; i < CustomSurfacesCount; i++)
		{
			delete(CustomSurfaces[i]);
		}
		delete(CustomSurfaces);
		CustomSurfaces = NULL;
		goto peintit;



	}

	//char *test3 = "Undo";
	for (i = 0; i < 4; i++)
	{
		if (test1[2][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 4)
	{
		okrender = 1;
		CustomSurfacesCount--;
		if (CustomSurfacesCount < 0)
		{
			CustomSurfacesCount = 0;
		}

		goto peintit;


	}
	//char *test4 = "spheres";
	for (i = 0; i < 7; i++)
	{
		if (test1[6][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 7)
	{
		okrender = 1;
		shperes_on = 1;
		glEnable(GL_LIGHTING);

		sphStacks = 2;
		sphSides = 3;

		goto peintit;

	}

	//char *test4 = "points";
	for (i = 0; i < 6; i++)
	{
		if (test1[7][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 6)
	{
		okrender = 1;
		shperes_on = 0;
		glDisable(GL_LIGHTING);

		goto peintit;

	}

	//char *test4 = "SuperCell(";
	for (i = 0; i < 10; i++)
	{
		if (test1[3][i] == ttt[i])
		{

		}
		else
		{
			i = 100;
		}
	}
	if (i == 10)
	{
		okrender = 1;
		help = (char*)(ttt + 10);
		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[0] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[0] = 10 * sizedprotector[0] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		help += 2;




		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[1] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ',' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[1] = 10 * sizedprotector[1] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;
				return;

			}
		}
		loop = 0;
		help += 2;



		if (help[0] >= 48 && help[0] <= 57)
		{
			sizedprotector[2] = help[0] - 48;
		}
		else
		{
			okrender = 0;
			return;
		}
		help = help + 2;
		while (help[0] != ')' && loop < 6)
		{
			loop++;
			if (help[0] >= 48 && help[0] <= 57)
			{
				sizedprotector[2] = 10 * sizedprotector[2] + help[0] - 48;
				help += 2;
			}
			else
			{
				okrender = 0;

				return;
			}
		}
		loop = 0;
		help += 2;



		if (okrender)
		{


			xexe[0] = 0;
			xexe[1] = 0;
			xexe[2] = 0;

			sized[0] = sizedprotector[0];
			sized[1] = sizedprotector[1];
			sized[2] = sizedprotector[2];
			custom_sized[0] = sizedprotector[0];
			custom_sized[1] = sizedprotector[1];
			custom_sized[2] = sizedprotector[2];

			jgn_supercell_xyz[0] = sized[0];
			jgn_supercell_xyz[1] = sized[1];
			jgn_supercell_xyz[2] = sized[2];

			if (sized[0] / 2 != sized[0] / 2.0)
			{
				xexe[0] = 1;
			}

			if (sized[1] / 2 != sized[1] / 2.0)
			{
				xexe[1] = 1;
			}

			if (sized[2] / 2 != sized[2] / 2.0)
			{
				xexe[2] = 1;
			}
			//periodic_table = fopen("periodic_table.jgn", "r");

			crystal = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			selective_dynamics = (char*)realloc(selective_dynamics, sizeof(char)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 3));

			//	crystal_backup = (float*)realloc(NULL, sizeof(float)*(jgn_supercell_xyz[0] * jgn_supercell_xyz[1] * jgn_supercell_xyz[2] * t * 5));
			//double ttest = omp_get_wtime();

#pragma omp parallel for firstprivate(jgn_supercell_xyz, xexe, my_direct, inptype, uccartesian, ijk, t)
			for (int ole3 = 0; ole3 < t; ole3++) {//for every atom in the unit cell
				for (int ole4 = -jgn_supercell_xyz[2] / 2; ole4 < jgn_supercell_xyz[2] / 2 + xexe[2]; ole4++) {
					for (int ole2 = -jgn_supercell_xyz[1] / 2; ole2 < jgn_supercell_xyz[1] / 2 + xexe[1]; ole2++) {
						for (int ole = -jgn_supercell_xyz[0] / 2; ole < jgn_supercell_xyz[0] / 2 + xexe[0]; ole++) {

							crystal[0 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						//	crystal_backup[0 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[0 + 5 * ole3];//atomikos ari8mos
						//selective dynamics
							selective_dynamics[0 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[0 + 3 * (ole3)];
							selective_dynamics[1 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[1 + 3 * (ole3)];
							selective_dynamics[2 + 3 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = selective_dynamics[2 + 3 * (ole3)];

							crystal[1 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
						//	crystal_backup[1 + 5 * (ole3 + t*(ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[1 + 5 * ole3];//atomiko varos
							if (inptype == 'd')
							{
								//crystal[ole + sized[0] / 2][ole2 + sized[1] / 2][ole4 + sized[2] / 2][ole3][1] = direct[1+5*ole3];
								for (int ole1 = 0; ole1 < 3; ole1++) {
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] = uccartesian[ole1 + 3 * ole3] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

									//if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									//{
									//	min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									//}
									//if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									//{
									//	max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									//}

								}

							}
							else if (inptype == 'c')
							{
								float oleh[3] = { ole,ole2,ole4 };
								for (ole1 = 0; ole1 < 3; ole1++) {
									if (oleh[ole1] >= 0)
										oleh[ole1]++;
									crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3)] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians
									crystal_backup[ole1 + 2 + 5 * (ole3 + t * (ole4 + jgn_supercell_xyz[2] / 2 + jgn_supercell_xyz[2] * (ole2 + jgn_supercell_xyz[1] / 2 + jgn_supercell_xyz[1] * (ole + jgn_supercell_xyz[0] / 2))))] = my_direct[ole1 + 2 + 5 * (ole3)] + ole * ijk[0][ole1] + ole2 * ijk[1][ole1] + ole4 * ijk[2][ole1];//cartesians

	/*								if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] < min_xyz[ole1])
									{
										min_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}
									if (crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))] > max_xyz[ole1])
									{
										max_xyz[ole1] = crystal[ole1 + 2 + 5 * (ole3 + t * (ole4 + sized[2] / 2 + sized[2] * (ole2 + sized[1] / 2 + sized[1] * (ole + sized[0] / 2))))];

									}*/

								}
							}


							//rewind(periodic_table);

						}
					}
				}
			}
			//ttest =  omp_get_wtime() - ttest;
			//cout << ttest << endl;
			//fclose(periodic_table);


		}

		goto peintit;

	}


peintit:

	DestroyWindow(CommandTextField);



	CommandTextField = CreateWindow(L"EDIT",
		0, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL,
		0, 735, 300, 40,
		hWndCommandLine, NULL, NULL, NULL);

	oldEditProc = (WNDPROC)SetWindowLongPtr(CommandTextField, GWLP_WNDPROC, (LONG_PTR)WndProcEditBox);

	SendMessage(CommandTextField, WM_SETFONT, (WPARAM)fOnt, TRUE);

peintit1:


	if (okrender)
	{
		SendMessage(CommandTextHistory, EM_SETREADONLY, FALSE, NULL);

		okrender = 0;

		SendMessage(CommandTextHistory, EM_SETSEL, 0, -1);
		SendMessage(CommandTextHistory, EM_SETSEL, -1, 0);

		for (i = 0; i < 50; i++)
		{

			if (i == 0 && ttt[0] == 13)
			{

			}
			else
			{
				if (ttt[i] == 0)
				{
					i = 100;
				}
				else
				{
					SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ttt[i], 0);


				}
			}
		}

		if (d == 1)
		{
			SendMessage(CommandTextHistory, WM_CHAR, (TCHAR)ucender[0], 0);
		}

		SetFocus(CommandTextField);
		SendMessage(CommandTextHistory, EM_SETREADONLY, TRUE, NULL);

		for (i = 0; i < 50; i++)
		{
			CommandBuffer[i] = 0;

		}

		JGN_PostRedisplay();

	}
	else
	{
		SetFocus(CommandTextField);
	}

}




void jgn_initcmd()
{
	HINSTANCE hinst111 = (HINSTANCE)GetWindowLong(hWndCommandLine, GWLP_HINSTANCE);

	char *enderrr = "\n";
	mbstowcs(ucender, enderrr, 2);


	GetWindowRect(mnhwnd, glb_rct);

	CommandTextHistory = CreateWindow(L"EDIT",
		0, WS_VISIBLE | WS_POPUP | WS_VSCROLL | ES_MULTILINE,
		(*glb_rct).left + 7, (*glb_rct).bottom - 286, (*glb_rct).right - (*glb_rct).left - 15, 242,
		mnhwnd, NULL, hinst111, NULL);

	fOnt = CreateFont(30, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Arial");


	SendMessage(CommandTextHistory, EM_SETREADONLY, TRUE, NULL);
	SendMessage(CommandTextHistory, WM_SETFONT, (WPARAM)fOnt, TRUE);


	CommandTextField = CreateWindow(L"EDIT",
		0, WS_VISIBLE | WS_POPUP | ES_MULTILINE | ES_AUTOHSCROLL,
		(*glb_rct).left + 7, (*glb_rct).bottom - 42, (*glb_rct).right - (*glb_rct).left - 14, 35,
		mnhwnd, NULL, hinst111, NULL);


	oldEditProc = (WNDPROC)SetWindowLongPtr(CommandTextField, GWLP_WNDPROC, (LONG_PTR)WndProcEditBox);

	SendMessage(CommandTextField, WM_SETFONT, (WPARAM)fOnt, TRUE);

	JGN_PostRedisplay();
}


float f(float x, float R)
{

	return (max_xyz[0] - min_xyz[0]) - (R / (x * 2))*(x*sqrt(1 + x * x) + log(x + sqrt(1 + x * x)));
}

float df(float x, float R)
{
	return (R / (2 * x*x))*(-x * sqrt(1 + x * x) + asinh(x));
}
float find_theta(float R)
{
	//float x0 = 1;
	//float x1 = 100;
	//Bisection
	//for (int i = 0; i < 100; i++)
	//{
	//
	//	//cout << f(x0, R)*f(x1, R) << endl;
	//	float xnew = (x0 + x1) / 2.0;
	//	if (f(x0,R)*f(xnew,R) <= 0)
	//	{
	//		x1 = xnew;
	//	}
	//	else
	//	{
	//		x0 = xnew;
	//	}
	//}
	//float xnew = (x0 + x1) / 2;

	//Newton Raphson

	float xnew = 200 + f(200, R) / (R*0.5);


	return xnew;
}
void MakeScroll()
{
	//S1v=tube_rin
	//S2v=tube_rout
	//S3v=tube_param

	int S2vforreal = S2v - S1v;
	//cout << S1v << ' ' << S2v << ' ' << S3v << endl;
	//cout << (max_xyz[0] - min_xyz[0]) << ' ' << S3v << endl;
	int ajklsdfl = t * (sized[0])*(sized[1])*(sized[2]);

	//Bisection to find max_theta
	float max_theta = find_theta(float(S2v));
	float min_theta = find_theta(float(S1v));



	S3v = ((max_xyz[0] - min_xyz[0]) * 2 * M_PI) / max_theta;
	S3v = S3v + ((max_xyz[0] - min_xyz[0]) * 2 * M_PI) / min_theta;

	cout << S3v << endl;

	//S3v = max_theta / (max_xyz[0]);
	cout << S3v << endl;

	for (ole3 = 0; ole3 < ajklsdfl; ole3++)
	{
		crystal[2 + 5 * ole3] = crystal_backup[2 + 5 * ole3];
		crystal[4 + 5 * ole3] = crystal_backup[4 + 5 * ole3];

		double R = S1v + S2vforreal * (crystal[2 + 5 * ole3] - min_xyz[0]) / (max_xyz[0] - min_xyz[0]);

		//Archimedes' Spiral
		//http://mathworld.wolfram.com/ArchimedesSpiral.html

		float theta = crystal[2 + 5 * ole3] * (2 * M_PI / S3v);


		crystal[4 + 5 * ole3] = R * sin(theta);

		crystal[2 + 5 * ole3] = R * cos(theta);
	}


}