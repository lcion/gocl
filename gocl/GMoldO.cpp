// GMoldO.cpp: implementation of the GMoldO class.
//
//////////////////////////////////////////////////////////////////////

#include "GMoldO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   Constructor
* Revision:
* 2000-03-16 luci 1.0 New
**********************************************************************/
GMoldO::GMoldO(int ObjId):SnglGObj(ObjId)
{

}

/*********************************************************************
* Description:
*   Destructor
* Revision:
* 2000-03-24 luci 1.0 New
**********************************************************************/
GMoldO::~GMoldO()
{

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-24 luci 1.0 New
**********************************************************************/
BOOL GMoldO::Save(ofstream *dst, LONG nID)
{
	*dst << "MLD " << nID <<" "<< m_objRect.left << " " << m_objRect.top  << " " 
		<< m_objRect.right << " " << m_objRect.bottom << " " << m_lGOColor 
		<< " " << m_lGOBkndCol;
	return SnglGObj::Save(dst, nID);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-24 luci 1.0 New
**********************************************************************/
void GMoldO::Redraw(HDC memHdc)
{
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	HPEN bPen = CreatePen( PS_SOLID ,	1, m_lGOBkndCol);
	HBRUSH crtBrush = CreateSolidBrush(m_lGOBkndCol);
	HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc, crtBrush);

	POINT drPcts[4],*lpArcPr = (POINT *)m_vpobjData; //lpArcPr->x // offset,  lpArcPr->y depth
	Rectangle(  memHdc, m_objRect.left, m_objRect.top, m_objRect.right,
		m_objRect.bottom );
	if( lpArcPr->y > 0 ){
		drPcts[0].x = m_objRect.left + lpArcPr->x;		// x-coord of rectangle's upper-left corner
		drPcts[0].y = m_objRect.top - lpArcPr->y;		// y-coord of rectangle's upper-left corner
		drPcts[1].x = m_objRect.right - lpArcPr->x;  // x-coord of rectangle's lower-right corner
		drPcts[1].y = m_objRect.top + lpArcPr->y;		// y-coord of rectangle's lower-right corner
		drPcts[2].x = m_objRect.left + lpArcPr->x;		// x-coord of first radial ending point
		drPcts[2].y = m_objRect.top;		// y-coord of first radial ending point
		drPcts[3].x = m_objRect.right - lpArcPr->x;		// x-coord of second radial ending point
		drPcts[3].y = m_objRect.top;		// y-coord of second radial ending point
	}
	else
	{
		drPcts[0].x = m_objRect.left + lpArcPr->x;		// x-coord of rectangle's upper-left corner
		drPcts[0].y = m_objRect.bottom + lpArcPr->y;		// y-coord of rectangle's upper-left corner
		drPcts[1].x = m_objRect.right - lpArcPr->x;  // x-coord of rectangle's lower-right corner
		drPcts[1].y = m_objRect.bottom - lpArcPr->y;		// y-coord of rectangle's lower-right corner
		drPcts[3].x = m_objRect.left + lpArcPr->x;		// x-coord of first radial ending point
		drPcts[3].y = m_objRect.bottom-1;		// y-coord of first radial ending point
		drPcts[2].x = m_objRect.right - lpArcPr->x;		// x-coord of second radial ending point
		drPcts[2].y = m_objRect.bottom-1;		// y-coord of second radial ending point
	}
	Arc(memHdc, drPcts[0].x, drPcts[0].y, drPcts[1].x, drPcts[1].y, drPcts[2].x, drPcts[2].y, drPcts[3].x, drPcts[3].y);

	DeleteObject(crtPen = (HPEN)SelectObject(memHdc, bPen));

	MoveToEx( memHdc, drPcts[2].x, drPcts[2].y, NULL );
	LineTo( memHdc, drPcts[3].x, drPcts[3].y);

	SelectObject(memHdc, oldPen);
	DeleteObject(bPen);
	SelectObject(memHdc, oldBrush);
	DeleteObject(crtBrush);
}

/*********************************************************************
* Description:
*	Create a mold object
*   params[0] upper left point
*   params[1] bottom down point
*   params[2] depth of the internal elipse and starting distance
*   params[3] colors
* Revision:
* 2000-03-24 luci 1.0 New
**********************************************************************/
void GMoldO::Create(POINT *params, LPSTR szCText)
{
	SnglGObj::Create(params[0].x, params[0].y, params[1].x, params[1].y, params[3].x, params[3].y, szCText);

	m_vpobjData = (char *)malloc(sizeof(POINT));
	POINT *nofL = (POINT*)m_vpobjData;
	nofL->x = params[2].x;
	nofL->y = params[2].y;
}
