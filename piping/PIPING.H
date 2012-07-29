#include <fstream>
using namespace std;
#include "stdio.h"
#include <malloc.h>
#include <stdlib.h>

#define IDM_EXIT                        105

#include "ADScomm.h"
LONG hnumber;
ADScomm *appADS;
TCHAR szTitle[MAX_PATH];	// The title bar text
TCHAR szcmdprm[MAX_PATH];
TCHAR szWindowClass[20];								// The title bar text
POINT windowSize;
UINT timerID;
BYTE data[500];

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
VOID CALLBACK lpTimerProc(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime );
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void InitializeLibADS(HWND hWnd);
void CreateLinksTable();

	LONG APIENTRY GOCL_GobjChgColors(char *wndName, char *grpName, char *objName, LONG bcolor, LONG color);
	BOOL APIENTRY GOCL_Refresh(char *);
	BOOL APIENTRY GOCL_LoadAllObjects(LPSTR, HWND hparentWnd);
	BOOL APIENTRY GOCL_ChangeTxt(char *wndName, char *grpName, char *txtoName, LPSTR szText);
	BOOL APIENTRY GOCL_TakeNextCommentStr(char *wndName, char *grName, char *oName, LPSTR CommentStr);

typedef struct
	{
		LONG color;
		LONG bcolor1;
		LONG bcolor2;
		char *wName;
		char *gName;
		char *oName;
		LONG index;
		unsigned char nBytes;
		char *varName;
		char *strUm;
	}LINKDATA;

LINKDATA **lDataTable;
