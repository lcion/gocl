// GCircleO.cpp: implementation of the GCircleO class.
//
//////////////////////////////////////////////////////////////////////

#include "GCircleO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GCircleO::GCircleO(char *ObjName):SnglGObj(ObjName)
{

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GCircleO::~GCircleO()
{

}

/*********************************************************************
* Description:
*   pointst[0].x = the radius
*   pointst[0].y = the posx
*	pointst[1].x = the posy
*	pointst[1].y = the color
*	pointst[2].x = the bcolor1
*	pointst[2].y = the bcolor2
*	pointst[3].x = the the pointer to the text comment
*	pointst[3].y = not used
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GCircleO::Create(POINT *pointst)
{
	m_bgcolor2 = pointst[2].y;
	SnglGObj::Create(pointst[0].y - pointst[0].x, pointst[1].x - pointst[0].x, pointst[0].y + pointst[0].x, pointst[1].x + pointst[0].x, pointst[1].y, pointst[2].x, (LPSTR)pointst[3].x);
//	SnglGObj::Create(posx - radius, posy - radius, posx + radius, posy + radius, color, bcolor, szCText);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GCircleO::Redraw(HDC memHdc)
{
	COLORREF lastColor, lastBkColor;
	lastBkColor = GetBkColor( memHdc );
	SetBkColor(memHdc, m_lGOColor);
	lastColor = GetTextColor( memHdc );
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	HBRUSH crtBrush = CreateSolidBrush(m_lGOBkndCol);
	HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc, crtBrush);

	Ellipse( memHdc, m_objRect.left, m_objRect.top, m_objRect.right,
		m_objRect.bottom );
	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
	SelectObject(memHdc, oldBrush);
	DeleteObject(crtBrush);
	SetBkColor(memHdc,lastBkColor);
	SnglGObj::Redraw(memHdc);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-05-17 luci 1.0 New
**********************************************************************/
BOOL GCircleO::Save(ofstream *dst)
{
	LONG r = (m_objRect.right-m_objRect.left)/2;
	*dst << "CIR " << m_GOName <<" "<< r << " " << m_objRect.left + r << 
		" " << m_objRect.top + r << " " << m_lGOColor << " " << m_lGOBkndCol << " " << m_bgcolor2;
	return SnglGObj::Save(dst);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-05-17 luci 1.0 New
**********************************************************************/
BOOL GCircleO::TakeCmtS(char *grName, char *oName, LPSTR CommentStr)
{
	char buffer[SMALL_BUFF];
	_ltoa_s(m_lGOColor, buffer, SMALL_BUFF, 10);
	strcat_s(buffer, SMALL_BUFF, " ");
	strcpy_s(CommentStr, CMNT_BUFF, buffer);
	_ltoa_s(m_lGOBkndCol, buffer, SMALL_BUFF, 10);
	strcat_s(buffer, SMALL_BUFF, " ");
	strcat_s(CommentStr, CMNT_BUFF, buffer);
	_ltoa_s(m_bgcolor2, buffer, SMALL_BUFF, 10);
	strcat_s(buffer, SMALL_BUFF, " ");
	strcat_s(CommentStr, CMNT_BUFF, buffer);
	return SnglGObj::TakeCmtS(grName, oName, CommentStr);
}

BOOL GCircleO::GetSelectedObjInfo(void *objInfoStruct)
{
	if(!SnglGObj::GetSelectedObjInfo(objInfoStruct))
		return FALSE;
	OBJINFO *pObjInfo = (OBJINFO *)objInfoStruct;
	pObjInfo->objType = CIRCLEID;
	return TRUE;

}
