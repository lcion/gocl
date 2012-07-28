// AboutCode.h: interface for the AboutCode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTCODE_H__3CBE6083_BA26_11D4_ACBF_F820C6B3A930__INCLUDED_)
#define AFX_ABOUTCODE_H__3CBE6083_BA26_11D4_ACBF_F820C6B3A930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AboutCode  
{
public:
	static LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	HWND m_hWnd;
	HINSTANCE m_hInst;
	void showModalWindow();
	AboutCode(HINSTANCE hInst, HWND hWnd);
	virtual ~AboutCode();

};

#endif // !defined(AFX_ABOUTCODE_H__3CBE6083_BA26_11D4_ACBF_F820C6B3A930__INCLUDED_)
