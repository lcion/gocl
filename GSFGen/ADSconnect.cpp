// ADSconnect.cpp: implementation of the ADSconnect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "GSFGen.h"
#include "ADSconnect.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADSconnect::ADSconnect()
{
	m_appADS = new ADScomm;
}

ADSconnect::~ADSconnect()
{
	delete m_appADS;
	if(lDataTable)
	for(int i=0; lDataTable[i] != NULL;i++)
	{
		free(lDataTable[i]->varName);
		free(lDataTable[i]->strUm);
		delete lDataTable[i]->wName;
		delete lDataTable[i]->gName;
		delete lDataTable[i]->oName;
		free(lDataTable[i]);
	}
	free(lDataTable);
}

void ADSconnect::UpdateWindow()
{
	unsigned char vrdd=0;
	char szText[20];
	for(int i=0; lDataTable[i] != NULL;i++)
	{
		if(vrdd == 0 || strcmp(lDataTable[i]->varName,lDataTable[i-1]->varName) != 0 )
		{
			m_appADS->adsGetArrayByPort(801,(LONG)&data[0],500,lDataTable[i]->varName);
			vrdd = 1;
		}
		if(lDataTable[i]->nBytes == 4)
		{
			float *fdata = (float*)&data[0];
			if(lDataTable[i]->strUm)
				sprintf_s(szText, 20, "%2.2f%s", fdata[lDataTable[i]->index-1], lDataTable[i]->strUm);
			else
				sprintf_s(szText, 20, "%2.2f", fdata[lDataTable[i]->index-1]);
			GOCL_ChangeTxt(lDataTable[i]->wName, lDataTable[i]->gName, lDataTable[i]->oName, szText);
		}
		else if(lDataTable[i]->nBytes == 1)
		{//boolean value
			if(data[lDataTable[i]->index-1] != 0)
				GOCL_GobjChgColors(lDataTable[i]->wName, lDataTable[i]->gName, lDataTable[i]->oName, lDataTable[i]->bcolor2, lDataTable[i]->color); //65535, 65280
			else
				GOCL_GobjChgColors(lDataTable[i]->wName, lDataTable[i]->gName, lDataTable[i]->oName, lDataTable[i]->bcolor1, lDataTable[i]->color); //0, 65280);
		}
	}
	GOCL_Refresh("0");
}

void ADSconnect::CreateLinksTable()
{
	char CommentStr[MAX_PATH] = "", wName[MAX_PATH] = "", grName[MAX_PATH] = "", oName[MAX_PATH] = "";
	lDataTable = NULL;
	lDataTable = (LINKDATA**)malloc(sizeof(LINKDATA*)*50);
	int i=0;
	while(GOCL_TakeNextCommentStr(wName, grName, oName, CommentStr))
	{
		char *pcs1=CommentStr, *pcs2, buffer[20];
		lDataTable[i] = NULL;
		if(pcs1[0] >= '0' && pcs1[0] <= '9' )	//if comment string contains colors
		{													// then take the color, bcolor1 and bcolor2
			lDataTable[i] = (LINKDATA*)malloc(sizeof(LINKDATA));
			for(pcs2 = buffer; *pcs1 >= '0' && *pcs1 <= '9' ;*pcs2 = *pcs1, pcs1++, pcs2++);
			buffer[pcs2-buffer]='\0';pcs1++;
			lDataTable[i]->color = atol(buffer);
			for(pcs2 = buffer; *pcs1 >= '0' && *pcs1 <= '9' ;*pcs2++ = *pcs1++);
			buffer[pcs2-buffer]='\0';pcs1++;
			lDataTable[i]->bcolor1 = atol(buffer);
			for(pcs2 = buffer; *pcs1 >= '0' && *pcs1 <= '9' ;*pcs2++ = *pcs1++);
			buffer[pcs2-buffer]='\0';pcs1++;
			lDataTable[i]->bcolor2 = atol(buffer);
		}

		pcs1 = strchr(pcs1,'"');
		if(NULL == pcs1)
			continue;
		pcs2 = strchr(pcs1+1,'"');
		if(lDataTable[i]==NULL){
			lDataTable[i] = (LINKDATA*)malloc(sizeof(LINKDATA));
			lDataTable[i]->color = 1;
		}
		lDataTable[i]->varName = (char*) malloc(pcs2-pcs1);
		memcpy(lDataTable[i]->varName, pcs1+1, pcs2-pcs1);
		lDataTable[i]->varName[pcs2-pcs1-1] = 0;

		pcs2++;
		while(*pcs2 == ' ' || *pcs2 == '\t')pcs2++;
		for(pcs1 = buffer; *pcs2 >= '0' && *pcs2 <= '9';*pcs1=*pcs2, pcs1++, pcs2++);
		*pcs1=0;
		lDataTable[i]->index = atoi(buffer);

		pcs2++;
		while(*pcs2 == ' ' || *pcs2 == '\t')pcs2++;
		for(pcs1 = buffer; (*pcs2 >= 'a' && *pcs2 <= 'z') || (*pcs2 >= 'A' && *pcs2 <= 'Z');*pcs1=*pcs2, pcs1++, pcs2++);
		*pcs1=0;
		if(strcmp(buffer, "BOOL") == 0)
			lDataTable[i]->nBytes = 1;
		else if(strcmp(buffer, "SINT") == 0)
			lDataTable[i]->nBytes = 1;
		else if(strcmp(buffer, "INT") == 0)
			lDataTable[i]->nBytes = 2;
		else if(strcmp(buffer, "DINT") == 0)
			lDataTable[i]->nBytes = 4;
		else if(strcmp(buffer, "REAL") == 0)
			lDataTable[i]->nBytes = 4;
		else if(strcmp(buffer, "LREAL") == 0)
			lDataTable[i]->nBytes = 8;
		while(*pcs2 == ' ' || *pcs2 == '\t')pcs2++;
		for(pcs1 = buffer; *pcs2 != '\0' && *pcs2 != ' ' && *pcs2 != '\t' && *pcs2 != '/' ;*pcs1=*pcs2, pcs1++, pcs2++);
		*pcs1=0;//strUm
		if(pcs1 != buffer)
		{
			lDataTable[i]->strUm = (char *)malloc(pcs1-buffer+1);
			strcpy_s(lDataTable[i]->strUm, pcs1-buffer+1, buffer);
		}
		else
			lDataTable[i]->strUm = NULL;
		lDataTable[i]->wName = new char[strlen(wName)+1];
		strcpy_s(lDataTable[i]->wName, strlen(wName)+1, wName);
		lDataTable[i]->gName = new char[strlen(grName)+1];
		strcpy_s(lDataTable[i]->gName, strlen(grName)+1, grName);
		lDataTable[i]->oName = new char[strlen(oName)+1];
		strcpy_s(lDataTable[i]->oName, strlen(oName)+1, oName);
		i++;
		CommentStr[0] = '\0';
	}
	lDataTable[i] = NULL;

}
