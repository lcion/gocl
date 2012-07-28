
#if !defined(AFX_GSFGEN_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_)
#define AFX_GSFGEN_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "ADSconnect.h"
#include "commctrl.h"
#include <fstream>
using namespace std;
#include "commdlg.h"
#include "gocl.h"
//PROJECT FILES

#define MAX_LOADSTRING 100
#define	MAXW		10
#define MAXO		10
#define NO_GROUP	-1

#define MS_TBRVISIBLE	1
#define MS_ANIMATION	2
#define MS_TSTCHLDWND	4
#define MS_GOCLTEST		8
#define MS_ADSCONNECT	16
#define MS_GOCLEDITMODE	32

// Global Variables:
UCHAR sens;
UINT menuState;
//UCHAR btbrVisible;		//=1 if the application ToolBar is visible
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
UINT timerID;
POINT pVector;
LONG hnumber;
LONG GraphTable[MAXW][MAXO];
ADSconnect *appADS;
HWND chwnd; // toolbar
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
void	CreateToolBar(HWND hWnd);
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

	BOOL MoveSelectedObj();
	void ConDisAdsSys(HWND hWnd);
	void TestMemoryLeak(HWND hWnd);
	void CreateDestrChildW(HWND hWnd);
	void SetEditMode(HWND hWnd);
	void StartSopAnimationCmd(HWND hWnd);
	BOOL DeleteSelectedObj();
	void KeyAction(WPARAM wParam);
	void StopAnimation(HWND hwnd);
	void DestrChildWindow();
	void StartAnimation(HWND hwnd);
	void CreateTheCWnd(HWND HWnd);
	void SaveAllObjects(HWND hwnd);
	void LoadAllObjects(HWND hwnd);
	void TestMl(HWND hWnd);
	void ConnectAdsSys(HWND hWnd);
#endif // !defined(AFX_GSFGEN_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_)
