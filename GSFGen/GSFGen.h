
#if !defined(AFX_GSFGEN_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_)
#define AFX_GSFGEN_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "ADScomm.h"
#include "commctrl.h"
#include <fstream>
using namespace std;
#include "commdlg.h"
#define MAX_LOADSTRING 100
#define	MAXW		10
#define MAXO		10
#define NO_GROUP	-1

// Global Variables:
UCHAR sens;
UCHAR btbrVisible;		//=1 if the application ToolBar is visible
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
UINT timerID;
POINT pVector;
LONG hnumber;
LONG GraphTable[MAXW][MAXO];
ADScomm *appADS;
HWND chwnd; // toolbar
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
void	CreateToolBar(HWND hWnd);
void	ShowWCreateO(HWND hWnd, int button);
void	ShowHideTb(HMENU hMenu);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	CreateNewODlg(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK lpTimerProc(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime );
VOID CALLBACK lpTimerProc1(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime );
VOID CALLBACK lpTimerProc2(  HWND hwnd,  UINT uMsg, UINT uMsg1, DWORD dwTime );

#define ITALIC_F 1
#define UNDERLINE_F 2
#define STRIKEOUT_F 4
#define BOLD_F		8

	void MoveGroup(WPARAM wParam);
	void StopAnimation(HWND hwnd);
	void DestrChildWindow();
	void StartAnimation(HWND hwnd);
	void CreateTheCWnd(HWND HWnd);
	void SaveAllObjects(HWND hwnd);
	void LoadAllObjects(HWND hwnd);
	void TestMl(HWND hWnd);
	void ConnectAdsSys(HWND hWnd);
	BOOL APIENTRY GOCL_MoveClientW(LONG wId, LONG x, LONG y);
	BOOL APIENTRY GOCL_LoadAllObjects(LPSTR, HWND hparentWnd);
	BOOL APIENTRY GOCL_SaveAllObjects(LPSTR);
	LONG APIENTRY GOCL_AddView(LONG wID, HWND hwndParent);
	BOOL APIENTRY GOCL_SetBounds(LONG hidx, LONG x, LONG y, LONG width, LONG height);
	BOOL APIENTRY GOCL_SetVisible(LONG , BOOL);
	BOOL APIENTRY GOCL_CloseView(LONG );
	WORD APIENTRY GOCL_SetBackgroundColor(LONG , LONG);
	LONG APIENTRY GOCL_AddText(LONG wndId, LONG grpId, LONG txtID, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR);
	BOOL APIENTRY GOCL_Refresh(LONG hidx);
	BOOL APIENTRY GOCL_SetTextFont(LONG , LONG, LONG , LPSTR , int , int );
	BOOL APIENTRY GOCL_GobjMove(LONG wndId, LONG grpId, LONG txtoId, POINT mhlpoint);
	BOOL APIENTRY GOCL_GobjMoveTo(LONG wndId, LONG grpId, LONG txtoId, POINT fpoint);
	LONG APIENTRY GOCL_AddBox(LONG wndId, LONG grpId, LONG boxID, POINT *, LPSTR);
	LONG APIENTRY GOCL_AddCircle(LONG wndId, LONG grpId, LONG cirID, LONG radius, LONG x, LONG y, LONG color, LONG bcolor, LPSTR);
	LONG APIENTRY GOCL_AddPolygon(LONG wID, LONG grpId, LONG pgID, POINT *pointArray, int nofpct, LONG color, LONG bcolor, LPSTR);
	LONG APIENTRY GOCL_AddGroup(LONG wndId, LONG gID);
	LONG APIENTRY GOCL_AddPolyLine(LONG wID, LONG grpId, LONG plID, POINT *pointArray, int nofpct, LONG color, LPSTR);
	LONG APIENTRY GOCL_GobjChgColors(LONG wID, LONG grpId, LONG objID, LONG bcolor, LONG color);
#endif // !defined(AFX_GSFGEN_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_)
