// GTxtO.h: interface for the GTxtO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GTXTO_H__23D5A350_D8BB_11D3_ACAB_00500449492C__INCLUDED_)
#define AFX_GTXTO_H__23D5A350_D8BB_11D3_ACAB_00500449492C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ITALIC_F	1
#define UNDERLINE_F 2
#define STRIKEOUT_F 4
#define BOLD_F		8
#include "SnglGObj.h"

class GTxtO : public SnglGObj  
{
public:
	void ChangeTxt(HWND m_clsWnd, LPSTR szText);
	BOOL Save(ofstream *dst, LONG nID);
	void SetFont(char *fname, int size, int attrib);
	void Create(HWND m_clsWnd, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	void Redraw(HDC memHdc);
	GTxtO(int ObjId);
	virtual ~GTxtO();

private:
	int m_dfattr;
	int m_dfsize;
	char *m_fname;
};

#endif // !defined(AFX_GTXTO_H__23D5A350_D8BB_11D3_ACAB_00500449492C__INCLUDED_)
