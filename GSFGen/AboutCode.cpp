// AboutCode.cpp: implementation of the AboutCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "AboutCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AboutCode::AboutCode(HINSTANCE hInst, HWND hWnd)
{
	m_hInst = hInst;
	m_hWnd = hWnd;
}

AboutCode::~AboutCode()
{

}

void AboutCode::showModalWindow()
{
	DialogBox(m_hInst, (LPCTSTR)IDD_ABOUTBOX, m_hWnd, (DLGPROC)About);
}

/*********************************************************************
* Description:
*   Mesage handler for about box.
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LRESULT CALLBACK AboutCode::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
