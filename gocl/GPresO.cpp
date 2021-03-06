// GPresO.cpp: implementation of the GPresO class.
//
//////////////////////////////////////////////////////////////////////

#include "GPresO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPresO::GPresO(char *ObjName):SnglGObj(ObjName)
{

}

GPresO::~GPresO()
{

}

void GPresO::Create(POINT *data, LPSTR szCText)
{
	m_vpobjData = (char *)new LONG;
	LONG *thick = (LONG*)m_vpobjData;
	*thick = data[0].x;
	SnglGObj::Create(data[1].x, data[1].y, data[2].x, data[2].y, data[3].x, data[3].y, szCText);

}

void GPresO::Redraw(HDC memHdc)
{
	LONG lpn;
	lpn = *(LONG*) m_vpobjData;
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	HBRUSH crtBrush = CreateSolidBrush(m_lGOBkndCol);
	HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc, crtBrush);
	if((m_objRect.right - m_objRect.left) > (m_objRect.bottom - m_objRect.top))
	{//horisontal object acos
		Ellipse( memHdc, m_objRect.left, m_objRect.top, m_objRect.left+ (m_objRect.bottom-m_objRect.top),
			m_objRect.bottom );
		Ellipse( memHdc, m_objRect.right - (m_objRect.bottom-m_objRect.top), m_objRect.top, m_objRect.right,
			m_objRect.bottom );

		SelectObject(memHdc, oldPen);
		DeleteObject(crtPen);
		crtPen = CreatePen( PS_SOLID ,	1, m_lGOBkndCol);
		oldPen = (HPEN)SelectObject(memHdc, crtPen);

		Rectangle(  memHdc, m_objRect.left + ((m_objRect.bottom-m_objRect.top) >> 1), 
			m_objRect.top + lpn,
			m_objRect.right - ((m_objRect.bottom-m_objRect.top) >> 1),
			m_objRect.bottom - lpn);

		SelectObject(memHdc, oldPen);
		DeleteObject(crtPen);
		crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
		oldPen = (HPEN)SelectObject(memHdc, crtPen);

		LONG x, y, r, x0, y0;
		r = (m_objRect.bottom-m_objRect.top) >> 1;
		x0 = m_objRect.left + r;
		y = m_objRect.top + lpn;
		y0 = r - lpn;
		x =  (LONG)sqrt(double(r*r - y0*y0)) + x0;
		MoveToEx( memHdc, x, y, NULL );
		x = x - x0;
		x0 = m_objRect.right - r;
		x = x0 - x;
		LineTo( memHdc, x, y);
		//lower line of the press;
		y =  m_objRect.bottom - lpn;
		x = x0-x;
		x0 = m_objRect.left + r;
		x = x + x0;
		MoveToEx( memHdc, x, y, NULL );
		x = x - x0;
		x0 = m_objRect.right - r;
		x = x0 - x;
		LineTo( memHdc, x, y);
	}
	else
	{//vertical object
		Ellipse( memHdc, m_objRect.left, m_objRect.top, m_objRect.left+ (m_objRect.bottom-m_objRect.top),
			m_objRect.bottom );
		Ellipse( memHdc, m_objRect.right - (m_objRect.bottom-m_objRect.top), m_objRect.top, m_objRect.right,
			m_objRect.bottom );
	}
	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
	SelectObject(memHdc, oldBrush);
	DeleteObject(crtBrush);
	SnglGObj::Redraw(memHdc);
}

BOOL GPresO::Save(ofstream *dst)
{
	LONG *redu = (LONG*)m_vpobjData;
	*dst << "PRS " << m_GOName <<" "<< *redu << " " << m_objRect.left << " "
		<< m_objRect.top << " " << m_objRect.right << " "
		<< m_objRect.bottom << " " << m_lGOColor << " " << m_lGOBkndCol ;
	return SnglGObj::Save(dst);
}

BOOL GPresO::GetSelectedObjInfo(void *objInfoStruct)
{
	if(!SnglGObj::GetSelectedObjInfo(objInfoStruct))
		return FALSE;
	OBJINFO *pObjInfo = (OBJINFO *)objInfoStruct;
	pObjInfo->objType = PRESID;
	pObjInfo->vpObjData = m_vpobjData;
	return TRUE;
}
