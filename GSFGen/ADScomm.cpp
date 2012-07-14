/* 
* Description:	ADS communication class
* File:			ADScomm.cpp
* Autor:		Luci
*/
#include "stdafx.h"
#include "ADScomm.h"

/* Function:	ADScomm::ADScomm
*  Description:	Constructor
*
*  Autor:		Luci
*/

ADScomm::ADScomm()
{
	hInstLAdsCrs = LoadLibrary("ADS_CRS.DLL");
	(FARPROC &)lpADS_GetWordByPort = GetProcAddress(hInstLAdsCrs, "ADS_GetWordByPort");
	(FARPROC &)lpADS_GetArrayByPort = GetProcAddress(hInstLAdsCrs, "ADS_GetArrayByPort");
}

/* Function:		ADScomm::~ADScomm
*  Description:	Destructor
*
*  Autor:		Luci
*/

ADScomm::~ADScomm()
{
	FreeLibrary(hInstLAdsCrs);
}
/*function ADS_GetWordByPort(port:word;var w:Word;name:pchar):integer;stdcall;
function ADS_GetArrayByPort(port:word;feld:longint;bytes:longint;name:pchar):integer;stdcall;

ADSError:=ADS_GetArrayByPort(adsport,longint(@feld),MAX*5*4,'.COM_A_Actual');
ADSError:= ADSError or ADS_GetArrayByPort(adsport,longint(@feld1),MAX*5*4,'HT_Cycle_Recording.COM_AR_Actual_1');
*/

LONG ADScomm::adsGetWordByPort(WORD port, LONG feld, LONG bytes, char *name)
{
	return lpADS_GetWordByPort(port, feld, bytes, name);
}

int ADScomm::adsGetArrayByPort(WORD port, LONG feld, LONG bytes, char *name)
{
	return lpADS_GetArrayByPort(port, feld, bytes, name);
}
