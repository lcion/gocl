/*
* Description:	Defines the entry point for the application.
* File:			GSFGen.cpp
* Autor:		Luci
* Date:			20/10/2000
*/

#include "stdafx.h"
#include "GSFGen.h"

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	for(int i = 0; i < MAXO; GraphTable[i++][0] = -1);
	MSG msg;
	HACCEL hAccelTable;

	//gIntInst = NULL;
	chwnd = 0;
	hnumber = 0;
	appADS = NULL;
	btbrVisible = 0; //ToolBar is not visible:

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GSFGEN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_GSFGEN);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_GSFGEN);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_GSFGEN;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}


/*HAN*********************************************************
* Description:
*   Saves instance handle and creates main window
*        In this function, we save the instance handle in a global variable and
*        create and display the main program window.
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   pVector.x = 1; pVector.y = 1;

   return TRUE;
}

/*HAN*********************************************************
* Description:
*   Processes messages for the main window.
*		WM_COMMAND	- process the application menu
*		WM_PAINT	- Paint the main window
*		WM_DESTROY	- post a quit message and return
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message)
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections: CreateToolBar LoadToolBar
			switch (wmId)
			{
				case ID_BOXCNEWO:
					ShowWCreateO(hWnd, lParam);
					break;
				case ID_VIEW_TOOLBAR:
					CreateToolBar(hWnd);
					break;
				case IDM_ABOUT:
					DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				case ID_ACTION_START:
					StartAnimation(hWnd);
					break;
				case ID_ACTION_STOP:
					StopAnimation(hWnd);
					break;
				case ID_ACTION_CREATECHLDW:
					CreateTheCWnd(hWnd);
					break;
				case ID_ACTION_DESTCHLDW:
					DestrChildWindow();
					break;
				case ID_FILE_SAVE:
					SaveAllObjects(hWnd);
					break;
				case ID_FILE_LOAD:
					LoadAllObjects(hWnd);
					break;
				case ID_ACTION_CONNECTADS:
					ConnectAdsSys(hWnd);
					break;
				case ID_ACTION_TESTMEMORYLICK:
					TestMl(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_KEYUP:
			MoveGroup(wParam);//
			break;
		case WM_DESTROY:
			KillTimer(hWnd,      // handle of window that installed timer
				timerID  // timer identifier
				);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


/*HAN*********************************************************
* Description:
*   Mesage handler for about box.
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

/*HAN*********************************************************
* Description :
*   Create a child window with graphical objects
0 = window
1 = text
2 = box
3 = group
3,0 = polyg1
3,1 = polyl1
3,2 = circle1
3,3 = polyl2
3,4 = polyg2
3,6 = polyl3
3,7 = polyg3
3,8 = polyg4
3,9 = circle2
3,10= polyl4 Spin
*  Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void CreateTheCWnd(HWND HWnd)
{
	POINT pArray[5]={{100, 100},{127, 127},{RGB(55,95,251), RGB(3,31,141)},{70,30},{0,0}};

	GraphTable[0][0] = GOCL_AddView(0, HWnd);
	GOCL_SetBounds(0, 0, 30, 200, 230);
	GOCL_SetBackgroundColor(0, 0x00E3351C); //0x00E3351C = RGB(28,53,227)
	GOCL_SetVisible(0, 1);
	hnumber++;
	GraphTable[1][0] = GOCL_AddGroup(0, 1);//create a group

//	GraphTable[0][2] = GOCL_AddBox(0, NO_GROUP, 2, &pArray[0], NULL);

	GraphTable[0][1]= GOCL_AddText(0, NO_GROUP, 3, "Text de Proba", 10, 10, 0, RGB(60,196,94), NULL);
	GOCL_SetTextFont(0, NO_GROUP, GraphTable[0][1], "arial", 21,ITALIC_F | UNDERLINE_F | STRIKEOUT_F | BOLD_F); //| BOLD_F

	//add the Polygon 1 to the new created group
	pArray[0].x=50; pArray[0].y=10; pArray[1].x=30; pArray[1].y=30; pArray[2].x=50; pArray[2].y=50;
	GOCL_AddPolygon( 0, 1, 0, &pArray[0], 4, 0x00ffffff, RGB(111,167,251), NULL);

	//add a polyline betwin the first polygon and the circle
	pArray[0].x=50; pArray[0].y=50; pArray[1].x=50; pArray[1].y=60; pArray[2].x=100; pArray[2].y=60; pArray[3].x=100; pArray[3].y=85;
	GOCL_AddPolyLine(0, 1, 1, &pArray[0], 4, RGB(111,167,251),NULL);

	//add a circle to the new created group
//	GOCL_AddCircle(0, 1, 2, 15, 100, 100, 0x00ffffff, RGB(111,167,251),NULL);

	//add a polyline betwin the circle and the second polygon
	pArray[0].x=100; pArray[0].y=115; pArray[1].x=100; pArray[1].y=150; pArray[2].x=25; pArray[2].y=150; pArray[3].x=25; pArray[3].y=170;
	GOCL_AddPolyLine(0, 1, 3, &pArray[0], 4, RGB(111,167,251),NULL);

	//add a Polygon to the new created group
	pArray[0].x=20; pArray[0].y=170; pArray[1].x=30; pArray[1].y=170; pArray[2].x=30; pArray[2].y=190; pArray[3].x=20; pArray[3].y=190;
	GOCL_AddPolygon( 0 , 1, 4, &pArray[0], 4, 0x00ffffff, RGB(111,167,251), NULL);

	//add a polyline betwin the circle and the third polygon
	pArray[0].x=25; pArray[0].y=190; pArray[1].x=25; pArray[1].y=210; pArray[2].x=40; pArray[2].y=210;
	GOCL_AddPolyLine(0, 1, 6, &pArray[0], 3, RGB(111,167,251),NULL);
//--- Valve

	//add a Polygon to the new created group
	pArray[0].x=40; pArray[0].y=205; pArray[1].x=40; pArray[1].y=215; pArray[2].x=50; pArray[2].y=210;
	GOCL_AddPolygon( 0, 1, 7, &pArray[0], 3, 0x00ffffff, RGB(111,167,251),NULL);

	//add a Polygon to the new created group
	pArray[0].x=64; pArray[0].y=205; pArray[1].x=64; pArray[1].y=215; pArray[2].x=54; pArray[2].y=210;
	GOCL_AddPolygon( 0, 1, 8, &pArray[0], 3, 0x00ffffff, RGB(111,167,251),NULL);

	//add a circle to the new created group
//	GOCL_AddCircle(0, 1, 9, 5, 52, 211, 0x00ffffff, RGB(111,167,251),NULL);
//--- End Valve

	//add a polyline betwin the circle and the second polygon
	pArray[0].x=64; pArray[0].y=210; pArray[1].x=120; pArray[1].y=210; pArray[2].x=120; pArray[2].y=5; pArray[3].x=50; pArray[3].y=5; pArray[4].x=50; pArray[4].y=10;
	GOCL_AddPolyLine(0, 1, 10, &pArray[0], 5, RGB(111,167,251),NULL);

	GOCL_Refresh(0);

}

/*HAN*********************************************************
* Description:
*   Start the animation, creating the timer
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void StartAnimation(HWND hwnd)
{
	sens=0;
	timerID = SetTimer(
		hwnd,              // handle of window for timer messages
		9999,          // timer identifier
		1,           // time-out value
		lpTimerProc   // address of timer procedure
	);
}

/*HAN*********************************************************
* Description:
*   Stop the animation killing the timer
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void StopAnimation(HWND hwnd)
{
	if(appADS == NULL)
		delete appADS;
	KillTimer(  hwnd, timerID /* timer identifier*/);
}

/*HAN*********************************************************
* Description:
*   Callback function for the timer
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
VOID CALLBACK lpTimerProc(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime ) //Test OK
{
/*	if(0 != -1)
	{*/
		if(sens == 2)//come back form out of screen
		{
			pVector.x = -pVector.x; pVector.y = -pVector.y;
			GOCL_GobjMove(0, 1, -1, pVector);
			sens = 1;
			pVector.x = -pVector.x; pVector.y = -pVector.y;
			return;
		}
		else if(sens == 1)//change direction
		{
			if(pVector.x == 1 && pVector.y == 1)
			{
				pVector.x =  0; pVector.y = -1;
/*				GOCL_GobjChgColors(0, 1, -1, RGB(0,167,0), RGB(255,0,0));
				GOCL_GobjChgColors(0, 1, 8, RGB(0,167,0), RGB(0,167,0));*/
			}
			else if(pVector.x ==  0 && pVector.y == -1)
			{
				pVector.x = -1; pVector.y =  1;
/*				GOCL_GobjChgColors(0, 1, -1, RGB(0,167,0), RGB(0,0,0));
				GOCL_GobjChgColors(0, 1, 8, 0x00ffffff, RGB(111,167,251));*/
			}
			else if(pVector.x == -1 && pVector.y ==  1)
			{
				pVector.x =  1; pVector.y =  0;
				//GOCL_GobjChgColors(0, 1, 8, RGB(0,167,0), RGB(0,167,0));
			}
			else if(pVector.x ==  1 && pVector.y ==  0)
			{
				pVector.x = -1; pVector.y = -1;
				//GOCL_GobjChgColors(0, 1, 8, 0x00ffffff, RGB(111,167,251));
			}
			else if(pVector.x == -1 && pVector.y == -1)
			{
				pVector.x =  0; pVector.y =  1;
				//GOCL_GobjChgColors(0, 1, 8, RGB(0,167,0), RGB(0,167,0));
			}
			else if(pVector.x ==  0 && pVector.y ==  1)
			{
				pVector.x =  1; pVector.y = -1;
				//GOCL_GobjChgColors(0, 1, 8, 0x00ffffff, RGB(111,167,251));
			}
			else if(pVector.x ==  1 && pVector.y == -1)
			{
				pVector.x = -1; pVector.y =  0;
				//GOCL_GobjChgColors(0, 1, 8, RGB(0,167,0), RGB(0,167,0));
			}
			else if(pVector.x == -1 && pVector.y ==  0)
			{
				pVector.x =  1; pVector.y =  1;
				//GOCL_GobjChgColors(0, 1, 8, 0x00ffffff, RGB(111,167,251));
			}
		}

 		if(GOCL_GobjMove(0, 1, -1, pVector)== -1) //if with current direction reach out of window.
			sens = 2;
		else
			sens = 0;
		GOCL_Refresh(0);
//	}
}
// lpTimerProc(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime )

/*HAN*********************************************************
* Description:
*   Callback function for the timer
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void DestrChildWindow()
{
	GOCL_CloseView(0);
}

/*HAN*********************************************************
* Description:
*   Callback function for the timer to test for memory leak
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
VOID CALLBACK lpTimerProc1(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime )//Test OK
{
		DestrChildWindow();
		CreateTheCWnd(hwnd);
}

void SaveAllObjects(HWND hwnd)
{
	OPENFILENAME        sfn;
	TCHAR	szFile[MAX_PATH] = "";
	static TCHAR        szFilter[80]=TEXT("ObjectScript Files (*.*)\0*.obs\0\0");
	ifstream src;

	memset(&sfn, 0, sizeof(OPENFILENAME));
	sfn.lStructSize      = sizeof(OPENFILENAME);
	sfn.hwndOwner        = hwnd;

	sfn.lpstrFilter      = szFilter;
	sfn.nFilterIndex     = 1L;

	sfn.lpstrTitle       = NULL;
	sfn.lpstrFile        = szFile;
	sfn.nMaxFile         = MAX_PATH;

	sfn.lpstrDefExt      = TEXT("*");
	sfn.Flags            = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	if(GetSaveFileName(&sfn) != 0)
		GOCL_SaveAllObjects(sfn.lpstrFile);
}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void LoadAllObjects(HWND hwnd)
{
	DestrChildWindow();
	OPENFILENAME        ofn;
	TCHAR	szFile[MAX_PATH] = "";
	static TCHAR        szFilter[80]=TEXT("ObjectScript Files (*.*)\0*.obs\0\0");
	ifstream src;

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize      = sizeof(OPENFILENAME);
	ofn.hwndOwner        = hwnd;

	ofn.lpstrFilter      = szFilter;
	ofn.nFilterIndex     = 1L;

	ofn.lpstrTitle       = NULL;
	ofn.lpstrFile        = szFile;
	ofn.nMaxFile         = MAX_PATH;

	ofn.lpstrDefExt      = TEXT("*");
	ofn.Flags            = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	if(GetOpenFileName(&ofn) != 0)
	{
//		src.open(ofn.lpstrFile);
		GOCL_LoadAllObjects(ofn.lpstrFile, hwnd);
//		src.close();
	}
}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void ConnectAdsSys(HWND hWnd)
{
	appADS = new ADScomm;
	timerID = SetTimer(
		hWnd,              // handle of window for timer messages
		9999,          // timer identifier
		5,           // time-out value
		lpTimerProc2   // address of timer procedure
	);
}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void TestMl(HWND hWnd)
{
	timerID = SetTimer(
		hWnd,              // handle of window for timer messages
		9999,          // timer identifier
		5,           // time-out value
		lpTimerProc1   // address of timer procedure
	);
}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
VOID CALLBACK lpTimerProc2(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime )
{
	BYTE data[500];
	appADS->adsGetArrayByPort(801,(LONG)&data[0],500,".COM_A_IO_Status");
	if(data[250] == 0)
		GOCL_GobjChgColors(0, 1, 8, 65280, 65280);
	else
		GOCL_GobjChgColors(0, 1, 8, 0, 65280);
	GOCL_Refresh(0);
}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-03-17 luci 1.0 New
**********************************************************************/
void CreateToolBar(HWND hWnd)
{
	HMENU hMenu = GetSubMenu(GetMenu(hWnd), 1);
	if(chwnd == 0)
	{
		TBBUTTON mybtns[10];
		memset(&mybtns[0], 0, sizeof(TBBUTTON)*10);
		mybtns[0].idCommand = ID_BOXCNEWO;
		for(int i = 0; i<10; i++)
		{
			mybtns[i].iBitmap = i;
			mybtns[i].iString = i;
			mybtns[i].fsState=TBSTATE_ENABLED;
			mybtns[i].idCommand = ID_BOXCNEWO;
		}
		chwnd = CreateToolbarEx(hWnd, WS_CHILD, IDR_MAINFRAME, 10, hInst, IDR_MAINFRAME,&mybtns[0],10,16,16,16,16,sizeof(TBBUTTON));
	}
	ShowHideTb(hMenu);

}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-03-17 luci 1.0 New
**********************************************************************/
void ShowHideTb(HMENU hMenu)
{
	if(btbrVisible)
	{
		CheckMenuItem(hMenu, ID_VIEW_TOOLBAR, MF_UNCHECKED);
		ShowWindow(chwnd,0); // hide tolbar
		btbrVisible = 0;
		GOCL_MoveClientW(0, 0, -16);
	}
	else{
		CheckMenuItem(hMenu, ID_VIEW_TOOLBAR, MF_CHECKED );
		ShowWindow(chwnd,1); // show tolbar
		btbrVisible = 1;
		GOCL_MoveClientW(0, 0, -16);
	}
}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-03-17 luci 1.0 New
**********************************************************************/
void ShowWCreateO(HWND hWnd, int button)
{
	DialogBox(hInst, (LPCTSTR)IDD_NCREATEOW, hWnd, (DLGPROC)CreateNewODlg);

}
/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-03-17 luci 1.0 New
**********************************************************************/
LRESULT CALLBACK CreateNewODlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

/*HAN*********************************************************
* Description:
*
* Revision:
* 2000-03-17 luci 1.0 New
**********************************************************************/
void MoveGroup(WPARAM wParam)
{
	char bset=0;
	switch(wParam){
	case 39:
		pVector.x =  1; pVector.y =  0;bset=1;break;
	case 40:
		pVector.x =  0; pVector.y =  1;bset=1;break;
	case 37:
		pVector.x =  -1; pVector.y = 0;bset=1;break;
	case 38:
		pVector.x =  0; pVector.y =  -1;bset=1;break;
	}
	if(bset)
		lpTimerProc(NULL, 0,0,0);
}