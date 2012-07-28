/* GLndO.cpp *******************************************************
*	 Description: implementation of the GLndO class.
*
*	Functions:
*		GLndO::GLndO
*		GLndO::GLndO~
*		GLndO::Save
*		GLndO::Redraw
*		GLndO::Create
*
*	Revision:
*		2000-02-23 luci 1.0 New
**********************************************************************/


#include "GLndO.h"


/*********************************************************************
* Description:
*   Constructor
* Revision:
* 2000-03-16 luci 1.0 New
**********************************************************************/
GLndO::GLndO(int ObjId):SnglGObj(ObjId)
{
	
}

/*********************************************************************
* Description:
*   Destructor
* Revision:
* 2000-03-16 luci 1.0 New
**********************************************************************/
GLndO::~GLndO()
{

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-16 luci 1.0 New
**********************************************************************/
BOOL GLndO::Save(ofstream *dst, LONG nID)
{
	*dst << "LND " <<nID<<" "<< m_objRect.left << " " << m_objRect.top  << " " 
		<< m_objRect.right<< " " << m_objRect.bottom<< " " << m_lGOColor 
		<< " " << m_lGOBkndCol ;
	return SnglGObj::Save(dst, nID);
}

/*********************************************************************
* Description:
*	The Logical and object is defined using 2 points
*   drPcts[0]
*   drPcts[1]
*   drPcts[2]
*   drPcts[3]
* Revision:
* 2000-03-16 luci 1.0 New
**********************************************************************/
void GLndO::Redraw(HDC memHdc)
{
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	HBRUSH crtBrush = CreateSolidBrush(m_lGOBkndCol);
	HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc, crtBrush);
	POINT drPcts[4];
	if(m_objRect.left - m_objRect.right > 0)
	{
		drPcts[0].x = m_objRect.left;		// x-coord of rectangle's upper-left corner
		drPcts[0].y = m_objRect.top;		// y-coord of rectangle's upper-left corner
		drPcts[1].x = (m_objRect.right << 1) - m_objRect.left;  // x-coord of rectangle's lower-right corner
		drPcts[1].y = m_objRect.bottom;		// y-coord of rectangle's lower-right corner
		drPcts[2].x = m_objRect.right;		// x-coord of first radial ending point
		drPcts[2].y = m_objRect.top;		// y-coord of first radial ending point
		drPcts[3].x = m_objRect.right;		// x-coord of second radial ending point
		drPcts[3].y = m_objRect.bottom;		// y-coord of second radial ending point
	}
	else
	{
		drPcts[0].x = m_objRect.left;		// x-coord of rectangle's upper-left corner
		drPcts[0].y = m_objRect.top;		// y-coord of rectangle's upper-left corner
		drPcts[1].x = (m_objRect.right << 1) - m_objRect.left;  // x-coord of rectangle's lower-right corner
		drPcts[1].y = m_objRect.bottom;		// y-coord of rectangle's lower-right corner
		drPcts[2].x = m_objRect.right;		// x-coord of first radial ending point
		drPcts[2].y = m_objRect.top;		// y-coord of first radial ending point
		drPcts[3].x = m_objRect.right;		// x-coord of second radial ending point
		drPcts[3].y = m_objRect.bottom;		// y-coord of second radial ending point
	}
	Arc(memHdc, drPcts[0].x, drPcts[0].y, drPcts[1].x, drPcts[1].y, drPcts[2].x, drPcts[2].y, drPcts[3].x, drPcts[3].y);
	MoveToEx( memHdc, drPcts[2].x, drPcts[2].y, NULL );
	LineTo( memHdc, drPcts[3].x, drPcts[3].y);

	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
	SelectObject(memHdc, oldBrush);
	DeleteObject(crtBrush);
}

/*********************************************************************
* Description:
*   params[0] = first point
*   params[1] = second point
*   params[2] = colors:color, bcolor
* Revision:
* 2000-03-16 luci 1.0 New
**********************************************************************/
void GLndO::Create(POINT *params, LPSTR szCText)
{
	SnglGObj::Create(params[0].x, params[0].y, params[1].x, params[1].y, params[2].x, params[2].y, szCText);
}
