
/* 
* Description:	ADS communication class
* File:			ADScomm.h
* Autor:		Luci
*/
#if !defined(ADScomm_Luci_Personal_Classes_)
#define ADScomm_Luci_Personal_Classes_

#include "stdafx.h"

class ADScomm
{
public:
	int adsGetArrayByPort(WORD port, LONG feld, LONG bytes, char* name);
	LONG adsGetWordByPort(WORD port, LONG feld, LONG bytes, char* name);
	ADScomm();
	~ADScomm();
private:
	HINSTANCE hInstLAdsCrs;
	long (FAR STDAPICALLTYPE * lpADS_GetWordByPort)(WORD port, LONG feld, LONG bytes, char* name);
	int (FAR STDAPICALLTYPE * lpADS_GetArrayByPort)(WORD port, LONG feld, LONG bytes, char* name);
};

#endif // ADScomm_Luci_Personal_Classes_
