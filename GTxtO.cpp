// GTxtO.cpp: implementation of the GTxtO class.
//
//////////////////////////////////////////////////////////////////////

#include "GTxtO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GTxtO::GTxtO(int ObjId):SnglGObj(ObjId)
{
	m_fname = NULL;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GTxtO::~GTxtO()
{
	if(m_fname)
		free(m_fname);
	m_fname = NULL;
}

/*********************************************************************
* Description:
*   Draw a text object
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GTxtO::Redraw(HDC memHdc)
{
//cf
	HFONT oldFont, hFont;
	if(m_fname){
		BOOL bItalic , bUnderline , bStrikeOut ;
		SIZE SizeT;
		LONG lWeight = FW_NORMAL;

		bItalic = bUnderline = bStrikeOut = false;
		if(m_dfattr & ITALIC_F) bItalic = true;
		if(m_dfattr & UNDERLINE_F) bUnderline = true;
		if(m_dfattr & STRIKEOUT_F) bStrikeOut = true;
		if(m_dfattr & BOLD_F) lWeight = FW_BOLD;

		hFont = CreateFont(m_dfsize, 0, 0, 0, lWeight, bItalic, bUnderline,
			bStrikeOut, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, m_fname);

		oldFont = (HFONT)SelectObject(memHdc, hFont);

		GetTextExtentPoint(memHdc, (char*)m_vpobjData, strlen((char*)m_vpobjData), &SizeT);
		m_objRect.bottom = m_objRect.top + SizeT.cy;
		m_objRect.right = m_objRect.left + SizeT.cx;
	}
//ecf

	COLORREF lastColor, lastBkColor;
	lastBkColor = GetBkColor( memHdc );
	lastColor = GetTextColor( memHdc );
	SetBkColor(memHdc, m_lGOBkndCol);
	SetTextColor(memHdc, m_lGOColor);

	DrawText(memHdc, (char*)m_vpobjData, strlen((char*)m_vpobjData), &m_objRect, DT_CENTER);

	if(hFont){
		SelectObject(memHdc, oldFont);
		DeleteObject(hFont);
	}
	SetBkColor(memHdc, lastBkColor);
	SetTextColor(memHdc, lastColor);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GTxtO::Create(HWND m_clsWnd, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText)
{
	SIZE SizeT;
	HDC hdc = GetDC(m_clsWnd);
	RECT rt;

	GetClientRect(m_clsWnd, &rt);
	rt.top = rt.top + y;
	rt.left = rt.left + x;

	GetTextExtentPoint(hdc, szText, strlen(szText), &SizeT);
	rt.bottom = rt.top + SizeT.cy;
	rt.right = rt.left + SizeT.cx;

	SnglGObj::Create(rt.left, rt.top, rt.right, rt.bottom, color, bcolor, szCText);

	m_vpobjData = (char*)malloc(strlen(szText) + 1);
	strcpy_s(m_vpobjData, strlen(szText) + 1, szText);
	ReleaseDC(m_clsWnd, hdc);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GTxtO::SetFont(char *fname, int size, int attrib)
{
	m_fname = (char*)malloc(strlen(fname)+1);
	strcpy_s(m_fname, strlen(fname)+1, fname);
	m_dfsize = size;
	m_dfattr = attrib;
}

/*********************************************************************
* Description:
*   Save the text object in a file
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL GTxtO::Save(ofstream *dst, LONG nID)
{
	*dst << "TXT " << nID <<" "<< strlen(m_vpobjData) << " " << m_vpobjData << " " <<
		m_objRect.left << " " << m_objRect.top << " " <<	m_lGOColor <<
		" " << m_lGOBkndCol;
	if(m_fname)
		*dst << " " << strlen(m_fname) << " " << m_fname << " " << m_dfsize << " " << m_dfattr;
	else
		*dst << " 0";

	return SnglGObj::Save(dst, nID);
}

void GTxtO::ChangeTxt(HWND m_clsWnd, LPSTR szText)// ChangeTxt(LONG txtoId, LPSTR szText)
{
	SIZE SizeT;
	HDC hdc = GetDC(m_clsWnd);
	RECT rt;

	memcpy(&rt, &m_objRect, sizeof(RECT));

	GetTextExtentPoint(hdc, szText, strlen(szText), &SizeT);

	rt.bottom = rt.top + SizeT.cy;
	rt.right = rt.left + SizeT.cx;

	memcpy(&m_objRect, &rt, sizeof(RECT));
	free(m_vpobjData);
	m_vpobjData = (char*)malloc(strlen(szText) + 1);
	strcpy_s(m_vpobjData, strlen(szText) + 1, szText);
	ReleaseDC(m_clsWnd, hdc);
}
