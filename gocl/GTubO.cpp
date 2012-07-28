/* GTubO.cpp *******************************************************
*	 Description: implementation of the GTubO class.
*
*	Functions:
*		GTubO::GTubO
*		GTubO::~GTubO
*		GTubO::Create
*		GTubO::Redraw
*		GTubO::Save
*
*	Revision:
*		2000.10.05
**********************************************************************/

#include "GTubO.h"


/*********************************************************************
* Description: Constructor
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
GTubO::GTubO(char *ObjName):SnglGObj(ObjName)
{

}

/*********************************************************************
* Description: Destructor
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
GTubO::~GTubO()
{

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
void GTubO::Create(POINT *pointst, LPSTR szCText)
{
	SnglGObj::Create(pointst[1].x, pointst[1].y, pointst[2].x, pointst[2].y, pointst[0].y, 0, szCText);

	m_vpobjData = (char *)new LONG;
	LONG *nofL = (LONG*)m_vpobjData;
	*nofL = pointst[0].x;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
void GTubO::Redraw(HDC memHdc)
{
	POINT *ptab;
	LONG lpn;
	double frgmnt;
	lpn = *(LONG*) m_vpobjData;
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	ptab = new POINT[lpn];
	if((m_objRect.right - m_objRect.left) > (m_objRect.bottom - m_objRect.top))
	{//draw a horizontal ressistance
		MoveToEx( memHdc, m_objRect.left, m_objRect.top, NULL );
		LineTo( memHdc, m_objRect.left, m_objRect.bottom);

		MoveToEx( memHdc, m_objRect.right, m_objRect.top, NULL );
		LineTo( memHdc, m_objRect.right, m_objRect.bottom);

		ptab[0].x = m_objRect.left;
		ptab[0].y = (m_objRect.bottom + m_objRect.top) >> 1;
		frgmnt = (m_objRect.right - m_objRect.left);
		frgmnt /= (lpn-1);
		for(int i = 1; i < lpn-1 ; i++)
		{
			ptab[i].x = m_objRect.left + (LONG)(i*frgmnt);
			ptab[i].y = i%2 ? m_objRect.top: m_objRect.bottom;
		}
		ptab[lpn-1].x = m_objRect.right;
		ptab[lpn-1].y = ptab[0].y;
	}
	else
	{
		MoveToEx( memHdc, m_objRect.left, m_objRect.top, NULL );
		LineTo( memHdc, m_objRect.right, m_objRect.top);

		MoveToEx( memHdc, m_objRect.left, m_objRect.bottom, NULL );
		LineTo( memHdc, m_objRect.right, m_objRect.bottom);

		ptab[0].x = (m_objRect.left + m_objRect.right) >> 1;
		ptab[0].y = m_objRect.top;
		frgmnt = (m_objRect.bottom - m_objRect.top);
		frgmnt /= (lpn-1);
		for(int i = 1; i < lpn-1 ; i++)
		{
			ptab[i].x = i%2 ? m_objRect.left: m_objRect.right;
			ptab[i].y = m_objRect.top + (LONG)(i*frgmnt); //ptab[i-1].y + frgmnt;
		}
		ptab[lpn-1].x = ptab[0].x;
		ptab[lpn-1].y = m_objRect.bottom;
	}
	Polyline( memHdc, ptab, lpn);
	delete ptab;
	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
	SnglGObj::Redraw(memHdc);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-7 luci 1.0 New
**********************************************************************/
BOOL GTubO::Save(ofstream *dst)
{
	LONG *nofL = (LONG*)m_vpobjData;
	*dst << "TUB " << m_GOName <<" "<< *nofL << " " << m_objRect.left << " "
		<< m_objRect.top << " " << m_objRect.right << " "
		<< m_objRect.bottom << " " << m_lGOColor ;
	return SnglGObj::Save(dst);
}

BOOL GTubO::GetSelectedObjInfo(void *objInfoStruct)
{
	if(!SnglGObj::GetSelectedObjInfo(objInfoStruct))
		return FALSE;
	OBJINFO *pObjInfo = (OBJINFO *)objInfoStruct;
	pObjInfo->objType = TUBID;
	pObjInfo->vpObjData = m_vpobjData;
	return TRUE;
}
