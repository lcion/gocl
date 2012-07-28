// ADSconnect.h: interface for the ADSconnect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADSCONNECT_H__9EBC4923_AC25_11D4_AD06_8CD9B90AC141__INCLUDED_)
#define AFX_ADSCONNECT_H__9EBC4923_AC25_11D4_AD06_8CD9B90AC141__INCLUDED_

#include "ADScomm.h"	// Added by ClassView
#include "gocl.h"
#include "stdio.h"
#include <fstream>
using namespace std;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
	{
		LONG color;
		LONG bcolor1;
		LONG bcolor2;
		char *wName;
		char *gName;
		char *oName;
		LONG index;
		unsigned char nBytes;
		char *varName;
		char *strUm;
	}LINKDATA;

class ADSconnect  
{
public:
	void CreateLinksTable();
	void UpdateWindow();
	LINKDATA **lDataTable;
	BYTE data[500];
	UINT timerID;
	POINT windowSize;
	ADScomm *m_appADS;
	LONG hnumber;

	void InitializeLibADS(HWND hWnd);
	void ConnectAdsSys(HWND hWnd);
	ADSconnect();
	virtual ~ADSconnect();
	LONG m_pAdsCls;

private:
};

#endif // !defined(AFX_ADSCONNECT_H__9EBC4923_AC25_11D4_AD06_8CD9B90AC141__INCLUDED_)
