// SnglGObj.cpp: implementation of the SnglGObj class.
//
//////////////////////////////////////////////////////////////////////

#include "SnglGObj.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
SnglGObj::SnglGObj(char *ObjName)
{
	m_lGOBkndCol = 0;
	m_bSelected = 0;
	m_lGOColor = 0x00ffffff;
	m_vpobjData = NULL;
	m_strComment = NULL;
	m_GOName = new char[strlen(ObjName)+1];
	strcpy_s(m_GOName, strlen(ObjName)+1, ObjName);

}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
SnglGObj::~SnglGObj()
{
	delete m_vpobjData;
	delete m_GOName;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglGObj::Create(LONG left, LONG top, LONG right, LONG bottom, LONG color, LONG bcolor, LPSTR szText)
{
	m_objRect.left = left;
	m_objRect.top = top;
	m_objRect.right = right;
	m_objRect.bottom = bottom;
	m_lGOBkndCol = bcolor;
	m_lGOColor = color;
	if(isInfo(szText))
	{
		m_strComment = new char[strlen(szText)+1];
		strcpy_s(m_strComment, strlen(szText)+1, szText);
	}
	return 1;
}

/*********************************************************************
* Description:
*	overloaded function
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void SnglGObj::Redraw(HDC memHdc)
{
	if(!m_bSelected)
		return;
	HPEN crtPen = CreatePen( PS_DOT ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	MoveToEx( memHdc, m_objRect.left-1, m_objRect.top-1, NULL );
	LineTo( memHdc, m_objRect.right, m_objRect.top-1);
	LineTo( memHdc, m_objRect.right, m_objRect.bottom);
	LineTo( memHdc, m_objRect.left-1, m_objRect.bottom);
	LineTo( memHdc, m_objRect.left-1, m_objRect.top-1);
	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglGObj::Move(HWND hWnd, POINT mhlPoint)
{
	RECT tmpr;
	GetWindowRect( hWnd, &tmpr );
	m_objRect.left += mhlPoint.x;
	m_objRect.right += mhlPoint.x;
	m_objRect.top += mhlPoint.y;
	m_objRect.bottom += mhlPoint.y;
	if(m_objRect.left >= 0 && tmpr.right - tmpr.left >= m_objRect.right && m_objRect.top >= 0 && tmpr.bottom - tmpr.top >= m_objRect.bottom )
		return 1;
	return -1;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int SnglGObj::MoveTo(HWND hWnd, POINT fPoint)
{
	RECT tmpr;
	GetWindowRect( hWnd, &tmpr );
	m_objRect.bottom += fPoint.y - m_objRect.top;
	m_objRect.right += fPoint.x - m_objRect.left;
	m_objRect.left = fPoint.x;
	m_objRect.top = fPoint.y;
	if(m_objRect.left >= 0 && tmpr.right - tmpr.left >= m_objRect.right && m_objRect.top >= 0 && tmpr.bottom - tmpr.top >= m_objRect.bottom )
		return 1;
	return -1;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
LONG SnglGObj::GobjChgColors(LONG bcolor, LONG color)
{
	m_lGOBkndCol = bcolor;
	m_lGOColor = color;
	return 1;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL SnglGObj::Save(ofstream *dst)
{
	if(m_strComment)
		*dst << " " << m_strComment;
	*dst << endl;
	return true;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL SnglGObj::isInfo(LPSTR str)
{
	if(NULL == str)
		return false;
	while(*str == ' ' || *str == '\t')str++;
	if(0 == *str)
		return false;
	return true;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-03-21 luci 1.0 New
**********************************************************************/
BOOL SnglGObj::TakeCmtS(char *grid, char *oid, LPSTR CommentStr)
{
	if(m_strComment)
	{
		strcat_s(CommentStr, CMNT_BUFF, m_strComment);
		return true;
	}
	return false;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-09-15 luci 1.0 New
**********************************************************************/
BOOL SnglGObj::IsObject(char *objName)
{
	if(strcmp(objName, m_GOName) == 0)
		return TRUE;
	return FALSE;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
BOOL SnglGObj::DeleteGObject(char *objName)
{
	return FALSE;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-10-05 luci 1.0 New
**********************************************************************/
BOOL SnglGObj::SelectGObject(UINT x, UINT y)
{
	if(	m_bSelected == 1){
		m_bSelected = 0;
		return FALSE;
	}
	if(m_objRect.left < m_objRect.right && m_objRect.top < m_objRect.bottom)
		if(m_objRect.left < (long)x && m_objRect.right > (long)x && m_objRect.top < (long)y && m_objRect.bottom > (long)y){
			m_bSelected = 1;
			return TRUE;
		}
	if(m_objRect.left < m_objRect.right && m_objRect.top > m_objRect.bottom)
		if(m_objRect.left < (long)x && m_objRect.right > (long)x && m_objRect.top > (long)y && m_objRect.bottom < (long)y){
			m_bSelected = 1;
			return TRUE;
		}
	if(m_objRect.left > m_objRect.right && m_objRect.top < m_objRect.bottom)
		if(m_objRect.left > (long)x && m_objRect.right < (long)x && m_objRect.top < (long)y && m_objRect.bottom > (long)y){
			m_bSelected = 1;
			return TRUE;
		}
	if(m_objRect.left > m_objRect.right && m_objRect.top > m_objRect.bottom)
		if(m_objRect.left > (long)x && m_objRect.right < (long)x && m_objRect.top > (long)y && m_objRect.bottom < (long)y){
			m_bSelected = 1;
			return TRUE;
		}
	m_bSelected = 0;
		return FALSE;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-10-06 luci 1.0 New
**********************************************************************/
BOOL SnglGObj::GetSelectedObjInfo(void *objInfoStruct)
{
	if(!m_bSelected)
		return FALSE;
	OBJINFO *pObjInfo = (OBJINFO *)objInfoStruct;
	pObjInfo->strComment = m_strComment;
	pObjInfo->objRect = &m_objRect;
	pObjInfo->strGOName = m_GOName;
	pObjInfo->GOBColor = m_lGOBkndCol;
	pObjInfo->GOColor = m_lGOColor;
	return TRUE;
}
