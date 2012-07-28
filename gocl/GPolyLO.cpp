// GPolyLO.cpp: implementation of the GPolyLOine class.
//
//////////////////////////////////////////////////////////////////////

#include "GPolyLO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GPolyLO::GPolyLO(char *ObjName):SnglGObj(ObjName)
{
	m_nofPct = 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GPolyLO::~GPolyLO()
{

}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GPolyLO::Create(POINT *pointst, int nofPt)
{
	RECT orct;
	m_vpobjData = (char*)new POINT[nofPt];
	memcpy(m_vpobjData, pointst, sizeof(POINT)*nofPt);
	m_nofPct = nofPt;
	SetLimitis(&orct);

	SnglGObj::Create(orct.left, orct.top, orct.right, orct.bottom, pointst[nofPt].x, 0, (LPSTR)pointst[nofPt].y);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GPolyLO::Redraw(HDC memHdc)
{
	COLORREF lastColor, lastBkColor;
	lastBkColor = GetBkColor( memHdc );
	lastColor = GetTextColor( memHdc );
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);

	Polyline(  memHdc, (POINT *)m_vpobjData, m_nofPct);

	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
	SnglGObj::Redraw(memHdc);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GPolyLO::SetLimitis(RECT *pRect)
{
	POINT *pPoliPct = (POINT *)m_vpobjData;
	pRect->left = pRect->right = pPoliPct[0].x;
	pRect->bottom = pRect->top = pPoliPct[0].y;
	for(int i = 0; i < m_nofPct; i++)
	{
		pRect->left = pRect->left > pPoliPct[i].x ? pPoliPct[i].x : pRect->left;//minX
		pRect->right = pRect->right < pPoliPct[i].x ? pPoliPct[i].x : pRect->right;//maxX
		pRect->bottom = pRect->bottom < pPoliPct[i].y ? pPoliPct[i].y : pRect->bottom;//minY
		pRect->top = pRect->top > pPoliPct[i].y ? pPoliPct[i].y : pRect->top;//maxY
	}
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
int GPolyLO::Move(HWND hWnd, POINT mhlPoint)
{
	POINT *pPoliPct = (POINT *)m_vpobjData;
	for(int i = 0; i < m_nofPct; i++)
	{
		pPoliPct[i].x += mhlPoint.x;
		pPoliPct[i].y += mhlPoint.y;
	}
	return SnglGObj::Move(hWnd,mhlPoint);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-03-02 luci 1.0 New
**********************************************************************/
BOOL GPolyLO::Save(ofstream *dst)
{
	POINT *pPoliPct = (POINT *)m_vpobjData;
	*dst << "POL " << m_GOName <<" "<< m_nofPct << " ";
	for(int i = 0; i < m_nofPct; i++)
		*dst << pPoliPct[i].x << " " << pPoliPct[i].y << " ";
	*dst <<	m_lGOColor ;
	return SnglGObj::Save(dst);
}

BOOL GPolyLO::GetSelectedObjInfo(void *objInfoStruct)
{
	if(!SnglGObj::GetSelectedObjInfo(objInfoStruct))
		return FALSE;
	OBJINFO *pObjInfo = (OBJINFO *)objInfoStruct;
	pObjInfo->objType = POLYLID;
	pObjInfo->dNoOfPoints = m_nofPct;
	pObjInfo->vpObjData = m_vpobjData;
	return TRUE;
}
