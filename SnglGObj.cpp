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
SnglGObj::SnglGObj(int ObjId)
{
	m_objId = ObjId;
	m_lGOBkndCol = 0;
	m_lGOColor = 0x00ffffff;
	m_vpobjData = NULL;
	m_strComment = NULL;
}

/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
SnglGObj::~SnglGObj()
{
	free(m_vpobjData);
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
		m_strComment = (char*)malloc(strlen(szText)+1);
		strcpy_s(m_strComment, strlen(szText)+1, szText);
	}
	return 1;
}
//overloaded function
/*********************************************************************
* Description:
*
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void SnglGObj::Redraw(HDC memHdc)
{

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
BOOL SnglGObj::Save(ofstream *dst, LONG nID)
{
	if(m_strComment)
		*dst << m_strComment;
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
BOOL SnglGObj::TakeCmtS(LONG *grid, LONG *oid, LPSTR CommentStr)
{
	if(m_strComment)
	{
		strcat(CommentStr, m_strComment);
		return true;
	}
	return false;
}
