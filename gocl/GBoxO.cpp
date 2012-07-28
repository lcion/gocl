// GBoxO.cpp: implementation of the GBoxO class.
//
//////////////////////////////////////////////////////////////////////

#include "GBoxO.h"


/*********************************************************************
* Description:Construction
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GBoxO::GBoxO(char *ObjName):SnglGObj(ObjName)
{

}

/*********************************************************************
* Description:Destruction
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GBoxO::~GBoxO()
{

}

/*********************************************************************
* Description:
*   params[0] = first point
*   params[1] = second point
*   params[2] = colors:color, bcolor1
*   params[3] = bcolor2, LPSTRcomment
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GBoxO::Create(POINT *params)
{
	m_bgcolor2 = params[3].x;
	SnglGObj::Create(params[0].x, params[0].y, params[1].x, params[1].y, params[2].x, params[2].y, (LPSTR)params[3].y);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GBoxO::Redraw(HDC memHdc)
{
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	HBRUSH crtBrush = CreateSolidBrush(m_lGOBkndCol);
	HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc, crtBrush);

	Rectangle(  memHdc, m_objRect.left, m_objRect.top, m_objRect.right,
		m_objRect.bottom );
	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
	SelectObject(memHdc, oldBrush);
	DeleteObject(crtBrush);
	SnglGObj::Redraw(memHdc);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
BOOL GBoxO::Save(ofstream *dst)
{
	*dst << "BOX " << m_GOName <<" "<< m_objRect.left << " " << m_objRect.top  << " "
		<< m_objRect.right << " " << m_objRect.bottom << " " << m_lGOColor 
		<< " " << m_lGOBkndCol << " " << m_bgcolor2;
	return SnglGObj::Save(dst);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-05-17 luci 1.0 New
**********************************************************************/
BOOL GBoxO::TakeCmtS(char *grName, char *oName, LPSTR CommentStr)
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

/*********************************************************************
* Description:
*   
* Revision:
* 2000-10-07 luci 1.0 New
**********************************************************************/
BOOL GBoxO::GetSelectedObjInfo(void *objInfoStruct)
{
	if(!SnglGObj::GetSelectedObjInfo(objInfoStruct))
		return FALSE;
	OBJINFO *pObjInfo = (OBJINFO *)objInfoStruct;
	pObjInfo->objType = BOXID;
	pObjInfo->GOBColor1 = m_bgcolor2;
	return TRUE;
}
