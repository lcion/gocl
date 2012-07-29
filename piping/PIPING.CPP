/*********************************************************************
* Description:	Defines the entry point for the application.
* File:			piping.cpp
*	piping functions:
*		WinMain
*		MyRegisterClass
*		InitInstance
*		WndProc
*		lpTimerProc
*		ConnectAdsSys
*		InitializeLibADS
*		CreateLinksTable
*
* Autor:		Luci
* Date:			2000-03-21
**********************************************************************/

#include "stdafx.h"
#include "piping.h"



/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;
	hnumber = 0;
	appADS = NULL;
	// Initialize global strings

//	strcpy(szTitle, "Piping");
	strcpy_s(szWindowClass, 20, "PIPINGPRG");
	MyRegisterClass(hInstance);
	strcpy_s(szcmdprm, 260, lpCmdLine);
	windowSize.x = 640;
	windowSize.y = 480;

	ifstream dst;
	BOOL rvalue = false;
	dst.open(szcmdprm);

	if(dst.is_open()){
		dst >> szTitle;
		for(int i=0;i<4;i++) dst >> windowSize.x;
		dst >> windowSize.y;
	}
	dst.close();
	szTitle[0]=0;


	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	hAccelTable = NULL;

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

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
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
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;//Cursor
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
//   hInst = hInstance; // Store instance handle in our global variable
	CreateMutex(NULL,true,"PIPINGMUTEX");
	if (GetLastError()==ERROR_ALREADY_EXISTS ){
	SetForegroundWindow(FindWindow("PIPINGPRG",szTitle));
	return FALSE;
	}

	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE | WS_POPUP ,
	  0, 0, windowSize.x, windowSize.y, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_CREATE:
			InitializeLibADS(hWnd);
			break;
		case WM_KEYUP:
			if(wParam != 27)
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

VOID CALLBACK lpTimerProc(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime )
{
	unsigned char vrdd=0;
	char szText[20];
	for(int i=0; lDataTable[i] != NULL;i++)
	{
		if(vrdd == 0 || strcmp(lDataTable[i]->varName,lDataTable[i-1]->varName) != 0 )
		{
			appADS->adsGetArrayByPort(801,(LONG)&data[0],500,lDataTable[i]->varName);
			vrdd = 1;
		}
		if(lDataTable[i]->nBytes == 4)
		{
			float *fdata = (float*)&data[0];
			if(lDataTable[i]->strUm)
				sprintf_s(szText, 20, "%2.2f%s", fdata[lDataTable[i]->index-1], lDataTable[i]->strUm);
			else
				sprintf_s(szText, 20, "%2.2f", fdata[lDataTable[i]->index-1]);
			GOCL_ChangeTxt(lDataTable[i]->wName, lDataTable[i]->gName, lDataTable[i]->oName, szText);
		}
		else if(lDataTable[i]->nBytes == 1)
		{//boolean value
			if(data[lDataTable[i]->index-1] != 0)
				GOCL_GobjChgColors(lDataTable[i]->wName, lDataTable[i]->gName, lDataTable[i]->oName, lDataTable[i]->bcolor2, lDataTable[i]->color); //65535, 65280
			else
				GOCL_GobjChgColors(lDataTable[i]->wName, lDataTable[i]->gName, lDataTable[i]->oName, lDataTable[i]->bcolor1, lDataTable[i]->color); //0, 65280);
		}
	}
	GOCL_Refresh("0");
}
/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
void ConnectAdsSys(HWND hWnd)
{
	CreateLinksTable();
	appADS = new ADScomm;
	timerID = SetTimer(
		hWnd,              // handle of window for timer messages
		9999,          // timer identifier
		500,           // time-out value
		lpTimerProc   // address of timer procedure
	);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
void InitializeLibADS(HWND hWnd)
{
	if(strlen(szcmdprm) < 4)
		strcpy_s(szcmdprm, 260, "..\\Data\\PipingMMPA2.obs");
	if(GOCL_LoadAllObjects(szcmdprm, hWnd) == FALSE)
	{
		MessageBox(NULL,"ScriptFile NOT Found!","ScriptFile NOT Found!",MB_OK);
		PostQuitMessage(0);
		return;
	}
	ConnectAdsSys(hWnd);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/

void CreateLinksTable()
{
//	LONG wid=-1, grid=-1, oid=-1;
	char CommentStr[MAX_PATH] = "", wName[MAX_PATH] = "", grName[MAX_PATH] = "", oName[MAX_PATH] = "";
	lDataTable = NULL;
	lDataTable = (LINKDATA**)malloc(sizeof(LINKDATA*)*50);
	int i=0;
	while(GOCL_TakeNextCommentStr(wName, grName, oName, CommentStr))
	{
		char *pcs1=CommentStr, *pcs2, buffer[20];
		lDataTable[i] = NULL;
		if(pcs1[0] >= '0' && pcs1[0] <= '9' )	//if comment string contains colors
		{													// then take the color, bcolor1 and bcolor2
			lDataTable[i] = (LINKDATA*)malloc(sizeof(LINKDATA));
			for(pcs2 = buffer; *pcs1 >= '0' && *pcs1 <= '9' ;*pcs2 = *pcs1, pcs1++, pcs2++);
			buffer[pcs2-buffer]='\0';pcs1++;
			lDataTable[i]->color = atol(buffer);
			for(pcs2 = buffer; *pcs1 >= '0' && *pcs1 <= '9' ;*pcs2++ = *pcs1++);
			buffer[pcs2-buffer]='\0';pcs1++;
			lDataTable[i]->bcolor1 = atol(buffer);
			for(pcs2 = buffer; *pcs1 >= '0' && *pcs1 <= '9' ;*pcs2++ = *pcs1++);
			buffer[pcs2-buffer]='\0';pcs1++;
			lDataTable[i]->bcolor2 = atol(buffer);
		}

		pcs1 = strchr(pcs1,'"');
		if(NULL == pcs1)
			continue;
		pcs2 = strchr(pcs1+1,'"');
		if(lDataTable[i]==NULL){
			lDataTable[i] = (LINKDATA*)malloc(sizeof(LINKDATA));
			lDataTable[i]->color = 1;
		}
		lDataTable[i]->varName = (char*) malloc(pcs2-pcs1);
		memcpy(lDataTable[i]->varName, pcs1+1, pcs2-pcs1);
		lDataTable[i]->varName[pcs2-pcs1-1] = 0;

		pcs2++;
		while(*pcs2 == ' ' || *pcs2 == '\t')pcs2++;
		for(pcs1 = buffer; *pcs2 >= '0' && *pcs2 <= '9';*pcs1=*pcs2, pcs1++, pcs2++);
		*pcs1=0;
		lDataTable[i]->index = atoi(buffer);

		pcs2++;
		while(*pcs2 == ' ' || *pcs2 == '\t')pcs2++;
		for(pcs1 = buffer; (*pcs2 >= 'a' && *pcs2 <= 'z') || (*pcs2 >= 'A' && *pcs2 <= 'Z');*pcs1=*pcs2, pcs1++, pcs2++);
		*pcs1=0;
		if(strcmp(buffer, "BOOL") == 0)
			lDataTable[i]->nBytes = 1;
		else if(strcmp(buffer, "SINT") == 0)
			lDataTable[i]->nBytes = 1;
		else if(strcmp(buffer, "INT") == 0)
			lDataTable[i]->nBytes = 2;
		else if(strcmp(buffer, "DINT") == 0)
			lDataTable[i]->nBytes = 4;
		else if(strcmp(buffer, "REAL") == 0)
			lDataTable[i]->nBytes = 4;
		else if(strcmp(buffer, "LREAL") == 0)
			lDataTable[i]->nBytes = 8;
		while(*pcs2 == ' ' || *pcs2 == '\t')pcs2++;
		for(pcs1 = buffer; *pcs2 != '\0' && *pcs2 != ' ' && *pcs2 != '\t' && *pcs2 != '/' ;*pcs1=*pcs2, pcs1++, pcs2++);
		*pcs1=0;//strUm
		if(pcs1 != buffer)
		{
			lDataTable[i]->strUm = (char *)malloc(pcs1-buffer+1);
			strcpy_s(lDataTable[i]->strUm, pcs1-buffer+1, buffer);
		}
		else
			lDataTable[i]->strUm = NULL;
		lDataTable[i]->wName = new char[strlen(wName)+1];
		strcpy_s(lDataTable[i]->wName, strlen(wName)+1, wName);
		lDataTable[i]->gName = new char[strlen(grName)+1];
		strcpy_s(lDataTable[i]->gName, strlen(grName)+1, grName);
		lDataTable[i]->oName = new char[strlen(oName)+1];
		strcpy_s(lDataTable[i]->oName, strlen(oName)+1, oName);
		i++;
		CommentStr[0] = '\0';
	}
	lDataTable[i] = NULL;
}

