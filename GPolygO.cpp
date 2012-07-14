// GPolygO.cpp: implementation of the GPolygO class.
//
//////////////////////////////////////////////////////////////////////

#include "GPolygO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GPolygO::GPolygO(int ObjId):SnglGObj(ObjId)
{
	m_nofPct = 0;
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
GPolygO::~GPolygO()
{

}

/*********************************************************************
* Description:
*   pointst[0..nofPt-1] = the polygone points
*	pointst[nofPt].x = the foreground color
*	pointst[nofPt].y = the first background color
*	pointst[nofPt+1].x = the second background color
*	pointst[nofPt+1].y = the pointer to the text comment
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GPolygO::Create(POINT *pointst, int nofPt) //, LONG color, LONG bcolor1, LONG bcolor2, LPSTR szCText
{
	RECT orct;
	m_vpobjData = (char *)malloc(sizeof(POINT)*nofPt);
	memcpy(m_vpobjData, pointst, sizeof(POINT)*nofPt); //the last long is not used = pointer to the text
	m_nofPct = nofPt;
	m_bgcolor2 = pointst[nofPt+1].x;
	SetLimitis(&orct);
	SnglGObj::Create(orct.left, orct.top, orct.right, orct.bottom, pointst[nofPt].x, pointst[nofPt].y, (LPSTR)pointst[nofPt+1].y);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GPolygO::Redraw(HDC memHdc)
{
	COLORREF  lastBkColor;
	lastBkColor = GetBkColor( memHdc );
	SetBkColor(memHdc, m_lGOColor);
	HPEN crtPen = CreatePen( PS_SOLID ,	1, m_lGOColor);
	HPEN oldPen = (HPEN)SelectObject(memHdc, crtPen);
	HBRUSH crtBrush = CreateSolidBrush(m_lGOBkndCol);
	HBRUSH oldBrush = (HBRUSH)SelectObject(memHdc, crtBrush);

	Polygon(  memHdc, (POINT *)m_vpobjData, m_nofPct);

	SelectObject(memHdc, oldPen);
	DeleteObject(crtPen);
	SelectObject(memHdc, oldBrush);
	DeleteObject(crtBrush);
	SetBkColor(memHdc,lastBkColor);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GPolygO::AdjustGmove()
{
	RECT oldRect;
	SetLimitis(&oldRect);
	if(oldRect.left != m_objRect.left || oldRect.top != m_objRect.top )
	{//the object was moved
		oldRect.left -= m_objRect.left;
		oldRect.top -= m_objRect.top;
		POINT *pPoliPct = (POINT *)m_vpobjData;
		for(int i = 0; i < m_nofPct; i++)
		{
			pPoliPct[i].x -= oldRect.left;
			pPoliPct[i].y -= oldRect.top;
		}
	}
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-02-23 luci 1.0 New
**********************************************************************/
void GPolygO::SetLimitis(RECT *pRect)
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
int GPolygO::Move(HWND hWnd, POINT mhlPoint)
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
* 2000-05-17 luci 1.0 New
**********************************************************************/
BOOL GPolygO::Save(ofstream *dst, LONG nID)
{

	POINT *pPoliPct = (POINT *)m_vpobjData;
	*dst << "POG " << nID << " "<< m_nofPct << " ";
	for(int i = 0; i < m_nofPct; i++)
		*dst << pPoliPct[i].x << " " << pPoliPct[i].y << " ";
	*dst <<	m_lGOColor << " " << m_lGOBkndCol << " " << pPoliPct[m_nofPct+1].x;
	return SnglGObj::Save(dst, nID);
}

/*********************************************************************
* Description:
*   
* Revision:
* 2000-05-17 luci 1.0 New
**********************************************************************/
BOOL GPolygO::TakeCmtS(LONG *grid, LONG *oid, LPSTR CommentStr)
{
	char buffer[20];
	_ltoa(m_lGOColor, buffer, 10);				strcat(buffer, " ");
	strcpy(CommentStr, buffer);
	_ltoa(m_lGOBkndCol, buffer, 10);			strcat(buffer, " ");
	strcat(CommentStr, buffer);
	_ltoa(m_bgcolor2, buffer, 10);	strcat(buffer, " ");
	strcat(CommentStr, buffer);
	return SnglGObj::TakeCmtS(grid, oid, CommentStr);
}
