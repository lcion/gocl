/* NewObjectDlg.cpp *******************************************************
*	 Description: implementation of the NewObjectDlg .
*
*	Functions:
*		ShowWCreateO
*		CreateNewODlg
*		CreateNewObject
*		InitDialog
*		CreateChildWindow
*		DestroyChildWindow
*		CreateTxtObject
*		CreateTubeObject
*		CreatePrsObject
*		CreatePolyLineObj
*		CreatePolyGoneObj
*		CreateLogAndObj
*		CreateCircleObj
*		CreateBoxObj
*		CreateMldObject
*		ChooseColorDlg
*		InitDialogHWnds
*		ChooseFontDlg
*		EditGObjectOK
*		SelectEditGrObj
*		StartRecPoints
*		InitDialogTxt
*		OnDlgLButtonUp
*		OnDlgRButtonUp
*		PasteGrObject
*		
*		
*		
*	Revision:
*		
**********************************************************************/

#include "stdafx.h"
#include "NewObjectDlg.h"

LONG	f_buttonID;	//button ID
LONG	f_EColorID;
HWND	f_parentWnd;
int		f_noOfPtsToRec;
POINT	f_prevPct;
OBJINFO *f_pOISt;

HWND hWndCol;
HWND hWndBCol;
HWND hWndBCol1;
HWND hWndColBtn;
HWND hWndFntBtn;
HWND hWndStartRP;
/*CONTINENTAL*********************************************************
* Description:
*
* Revision:
* 2000-03-17 luci 1.0 New
**********************************************************************/
void ShowWCreateO(HINSTANCE hInst, HWND hWnd, LONG buttonID, OBJINFO *pOISt)
{
	f_buttonID = buttonID;
	f_parentWnd = hWnd;
	f_pOISt = pOISt;
	DialogBox(hInst, (LPCTSTR)IDD_NCREATEOW, hWnd, (DLGPROC)CreateNewODlg);
}

/*CONTINENTAL*********************************************************
* Description:
*
* Revision:
* 2000-03-17 luci 1.0 New
**********************************************************************/
LRESULT CALLBACK CreateNewODlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			InitDialog(hDlg);
			return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				if((LOWORD(wParam) == IDOK && CreateNewObject(hDlg)) || LOWORD(wParam) == IDCANCEL)
					EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if((HWND)lParam == hWndColBtn)
				ChooseColorDlg(hDlg);//change Color
			else if((HWND)lParam == hWndCol)
				f_EColorID = IDC_ECOLOR;
			else if((HWND)lParam == hWndBCol)
				f_EColorID = IDC_EBCOLOR;
			else if((HWND)lParam == hWndBCol1)
				f_EColorID = IDC_EBCOLOR1;
			else if((HWND)lParam == hWndFntBtn)
				ChooseFontDlg(hDlg);//change font
			else if((HWND)lParam == hWndStartRP)
				StartRecPoints(hDlg);//Start Recording Points
			break;
		case WM_LBUTTONUP:
			OnDlgLButtonUp(hDlg, wParam, lParam);
			break;
		case WM_RBUTTONUP:
			OnDlgRButtonUp(hDlg, wParam, lParam);
			break;

		case IDC_BCOLORS:
			break;
	}
    return FALSE;
}

/*CONTINENTAL*********************************************************
* Description: Check and Create a Valid GObj;
*
* Revision:
* 2000-09-06 luci 1.0 New
**********************************************************************/
UCHAR CreateNewObject(HWND hDlg)
{
	switch(f_buttonID){
	case ID_BOXCNEWO:
		return CreateBoxObj(hDlg);
	case ID_CIRCNEWO:
		return CreateCircleObj(hDlg);
	case ID_LNDCNEWO:
		return CreateLogAndObj(hDlg);
	case ID_POGCNEWO:
		return CreatePolyGoneObj(hDlg);
	case ID_POLCNEWO:
		return CreatePolyLineObj(hDlg);
	case ID_PRSCNEWO:
		return CreatePrsObject(hDlg);
	case ID_TUBCNEWO:
		return CreateTubeObject(hDlg);
	case ID_TXTCNEWO:
		return CreateTxtObject(hDlg);
	case ID_MLDCNEWO:
		return CreateMldObject(hDlg);
	case ID_GRPCNEWO:
		return CreateGrpObject(hDlg);
	case ID_DELWO:
		return DestroyChildWindow(hDlg);
	case ID_WNDCNEWO:
		return CreateChildWindow(hDlg);
	case ID_EDITGO:
		return EditGObjectOK(hDlg);
	case ID_PASTEGO:
	return PasteGrObject(hDlg);
	}
	return 0;
}

/*CONTINENTAL*********************************************************
* Description: Initialize the dialog;
*
* Revision:
* 2000-09-06 luci 1.0 New
**********************************************************************/
void InitDialog(HWND hDlg)
{
HWND hWndObjName;
	InitDialogHWnds(hDlg);

//	hWndObjName = GetDlgItem(  hDlg, IDC_STARTRP);
//	EnableWindow(hWndStartRP, FALSE);

	ShowWindow(hWndFntBtn, SW_HIDE);

	switch(f_buttonID){
	case ID_BOXCNEWO:
		SetWindowText(hDlg, "Create New Box");
//		EnableWindow(hWndStartRP, TRUE);

		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "Box1");

		SetWindowText(hWndCol, "65280");

		SetWindowText(hWndBCol, "65280");

		SetWindowText(hWndBCol1, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, "30");

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, "40");

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		SetWindowText(hWndObjName, "50");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		SetWindowText(hWndObjName, "50");
		break;
	case ID_CIRCNEWO:
		SetWindowText(hDlg, "Create New Circle");
//5 110 410 65280 65280 65280
		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "Circle1");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "65280");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		SetWindowText(hWndBCol, "65280");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		SetWindowText(hWndBCol1, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, "110");

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, "210");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		SetWindowText(hWndObjName, "20");//radius

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);
		break;
	case ID_LNDCNEWO:
		SetWindowText(hDlg, "Create New Logical And");
//230 175 235 195 65280 0
		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "LogicAnd1");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "65280");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, "230");

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, "175");

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		SetWindowText(hWndObjName, "235");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		SetWindowText(hWndObjName, "195");
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		EnableWindow(hWndBCol, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		EnableWindow(hWndBCol1, FALSE);
		break;
	case ID_POGCNEWO:
		SetWindowText(hDlg, "Create New Polygon");

		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "PolyGone1");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "15461355");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		SetWindowText(hWndBCol, "0");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		SetWindowText(hWndBCol1, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, "10 90 255 100 255 100 275 95 275 95 255 95 265 110 265 95 265 95 275 90 275");
		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);
		break;
	case ID_POLCNEWO:
		SetWindowText(hDlg, "Create New Polyline");

		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "PolyLine1");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "15461355");

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, "9 110 170 110 80 110 100 200 100 200 120 200 100 350 100 350 180 350 170");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		EnableWindow(hWndBCol, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		EnableWindow(hWndBCol1, FALSE);
		break;
	case ID_PRSCNEWO:
		SetWindowText(hDlg, "Create New Press");

		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "Press1");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "15461355");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		SetWindowText(hWndObjName, "40");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		SetWindowText(hWndBCol, "0");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		SetWindowText(hWndBCol1, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, "10");

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		SetWindowText(hWndObjName, "100");
		break;

	case ID_TUBCNEWO:
		SetWindowText(hDlg, "Create New Tube");

		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "Tube1");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "15461355");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		SetWindowText(hWndObjName, "100");

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		SetWindowText(hWndObjName, "100");

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, "10");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		EnableWindow(hWndBCol, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		EnableWindow(hWndBCol1, FALSE);
		break;

	case ID_TXTCNEWO:
		InitDialogTxt(hDlg);
 		break;

	case ID_MLDCNEWO:
		SetWindowText(hDlg, "Create New Molder");
//MLD 95 130 135 275 165 10 10 65280 0

		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "Molder1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, "130");

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, "135");

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		SetWindowText(hWndObjName, "275");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		SetWindowText(hWndObjName, "165");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "65280");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		SetWindowText(hWndBCol, "0");

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		SetWindowText(hWndBCol1, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, "10 10");
		break;

	case ID_DELWO:
		SetWindowText(hDlg, "Delete Object");

		EnableWindow(hWndStartRP, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);
		EnableWindow(hWndCol, FALSE);
		EnableWindow(hWndBCol, FALSE);
		EnableWindow(hWndBCol1, FALSE);
		EnableWindow(hWndColBtn, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		EnableWindow(hWndObjName, FALSE);
		break;
	case ID_GRPCNEWO:
		SetWindowText(hDlg, "Create New Group");

		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "Group1");

		EnableWindow(hWndStartRP, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);
		EnableWindow(hWndColBtn, FALSE);
		EnableWindow(hWndCol, FALSE);
		EnableWindow(hWndBCol, FALSE);
		EnableWindow(hWndBCol1, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		EnableWindow(hWndObjName, FALSE);
		break;

	case ID_WNDCNEWO:
		SetWindowText(hDlg, "Create New Window");

		hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
		SetWindowText(hWndObjName, "Window1");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, "0");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		SetWindowText(hWndObjName, "360");

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		SetWindowText(hWndObjName, "590");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		SetWindowText(hWndCol, "0");
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		EnableWindow(hWndBCol, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		EnableWindow(hWndBCol1, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
		EnableWindow(hWndObjName, FALSE);
		break;
	case ID_EDITGO:
	case ID_PASTEGO:
		SelectEditGrObj(hDlg);
		break;
	}
	f_EColorID = IDC_ECOLOR;//set the default edit control to change color
}

/*CONTINENTAL*********************************************************
* Description: Select Graphival Object to edit in the window
*
* Revision:
* 2000-10-04 luci 1.1 New
**********************************************************************/
UCHAR SelectEditGrObj(HWND hDlg)
{

HWND hWndObjName;
char szTitleDlg[40], buffer[256], cnvrtBuf[40];
POINT *trP;
int i;

	strcpy(szTitleDlg, "Edit ");
	switch(f_pOISt->objType)
	{
	case BOXID:
		strcat(szTitleDlg, "Box");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		ltoa(f_pOISt->GOBColor,buffer,10);
		SetWindowText(hWndBCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		ltoa(f_pOISt->GOBColor1,buffer,10);
		SetWindowText(hWndBCol1, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		ltoa(f_pOISt->objRect->left,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		ltoa(f_pOISt->objRect->top,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		ltoa(f_pOISt->objRect->right,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		ltoa(f_pOISt->objRect->bottom,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, f_pOISt->strComment);
		break;
	case TXTID:
		strcat(szTitleDlg, "Text");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		ltoa(f_pOISt->GOBColor,buffer,10);
		SetWindowText(hWndBCol, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		ltoa(f_pOISt->objRect->left,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		ltoa(f_pOISt->objRect->top,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, (LPSTR)f_pOISt->vpObjData);
//change controls for text comment and font
	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);//comment
	RECT vRect;
	GetWindowRect(  hWndObjName, &vRect );
	MapWindowPoints(NULL, hDlg, (POINT *)&vRect, 2);
	MoveWindow(hWndObjName, vRect.left-71, vRect.top, vRect.right-vRect.left+71, vRect.bottom - vRect.top, FALSE);
	SetWindowText(hWndObjName,f_pOISt->strComment);

	hWndObjName = GetDlgItem(  hDlg, IDC_BOTTOMLBL);
	SetWindowText(hWndObjName,"C");

	hWndObjName = GetDlgItem(  hDlg, IDC_RIGHTLBL);
	ShowWindow(hWndObjName, SW_HIDE);

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1); //font
	//buffer[256], cnvrtBuf
	strcpy(buffer,f_pOISt->fntName);
	ltoa(f_pOISt->dNoOfPoints, cnvrtBuf, 10);
	strcat(buffer, " ");strcat(buffer, cnvrtBuf);
	ltoa(f_pOISt->GOBColor1, cnvrtBuf, 10);
	strcat(buffer, " ");strcat(buffer, cnvrtBuf);

	SetWindowText(hWndBCol1,buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_BAKGROUND1LBL);
	SetWindowText(hWndObjName,"Fn");

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		EnableWindow(hWndObjName, FALSE);
		break;
	case CIRCLEID:
		strcat(szTitleDlg, "Circle");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		ltoa(f_pOISt->GOBColor,buffer,10);
		SetWindowText(hWndBCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		ltoa(f_pOISt->GOBColor1,buffer,10);
		SetWindowText(hWndBCol1, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		ltoa((f_pOISt->objRect->right+f_pOISt->objRect->left)/2,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		ltoa((f_pOISt->objRect->bottom+f_pOISt->objRect->top)/2,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		ltoa((f_pOISt->objRect->bottom-f_pOISt->objRect->top)/2,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, f_pOISt->strComment);

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);
		break;
	case POLYGID:
		strcat(szTitleDlg, "Polygone");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		ltoa(f_pOISt->GOBColor,buffer,10);
		SetWindowText(hWndBCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		ltoa(f_pOISt->GOBColor1,buffer,10);
		SetWindowText(hWndBCol1, buffer);

		trP = (POINT*)(f_pOISt->vpObjData);

		ltoa(f_pOISt->dNoOfPoints, buffer, 10);
		for(i = 0; i < f_pOISt->dNoOfPoints; i++){
			ltoa(trP[i].x,cnvrtBuf,10);
			strcat(buffer, " ");strcat(buffer, cnvrtBuf);
			ltoa(trP[i].y,cnvrtBuf,10);
			strcat(buffer, " ");strcat(buffer, cnvrtBuf);
		}
		if(f_pOISt->strComment){
			strcat(buffer, " ");
			strcat(buffer, f_pOISt->strComment);
		}
		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);

		break;
	case POLYLID:

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

		trP = (POINT*)(f_pOISt->vpObjData);

		ltoa(f_pOISt->dNoOfPoints, buffer, 10);

		for(i = 0; i < f_pOISt->dNoOfPoints; i++){
			ltoa(trP[i].x,cnvrtBuf,10);
			strcat(buffer, " ");strcat(buffer, cnvrtBuf);
			ltoa(trP[i].y,cnvrtBuf,10);
			strcat(buffer, " ");strcat(buffer, cnvrtBuf);
		}
		if(f_pOISt->strComment){
			strcat(buffer, " ");
			strcat(buffer, f_pOISt->strComment);
		}
		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, buffer);

		strcat(szTitleDlg, "Polyline");
		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		EnableWindow(hWndObjName, FALSE);
		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		EnableWindow(hWndObjName, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		EnableWindow(hWndBCol, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		EnableWindow(hWndBCol1, FALSE);
		break;
	case TUBID:
		strcat(szTitleDlg, "Tube");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		ltoa(f_pOISt->objRect->left,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		ltoa(f_pOISt->objRect->top,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		ltoa(f_pOISt->objRect->right,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		ltoa(f_pOISt->objRect->bottom,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		ltoa(*(LONG*)f_pOISt->vpObjData,buffer,10);
		if(f_pOISt->strComment){
			strcat(buffer, " ");
			strcat(buffer, f_pOISt->strComment);
		}
		SetWindowText(hWndObjName, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		EnableWindow(hWndBCol, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		EnableWindow(hWndBCol1, FALSE);
		break;
	case PRESID:
		strcat(szTitleDlg, "Press");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		ltoa(f_pOISt->GOBColor,buffer,10);
		SetWindowText(hWndBCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		ltoa(f_pOISt->GOBColor1,buffer,10);
		SetWindowText(hWndBCol1, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		ltoa(f_pOISt->objRect->left,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		ltoa(f_pOISt->objRect->top,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		ltoa(f_pOISt->objRect->right,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		ltoa(f_pOISt->objRect->bottom,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		ltoa(*(LONG*)f_pOISt->vpObjData,buffer,10);
		if(f_pOISt->strComment){
			strcat(buffer, " ");
			strcat(buffer, f_pOISt->strComment);
		}
		SetWindowText(hWndObjName, buffer);
		break;
	case MOLDID:
		strcat(szTitleDlg, "Molder");

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		ltoa(f_pOISt->objRect->left,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		ltoa(f_pOISt->objRect->top,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		ltoa(f_pOISt->objRect->right,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		ltoa(f_pOISt->objRect->bottom,buffer,10);
		SetWindowText(hWndObjName, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		ltoa(f_pOISt->GOBColor,buffer,10);
		SetWindowText(hWndBCol, buffer);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		ltoa(f_pOISt->GOBColor1,buffer,10);
		SetWindowText(hWndBCol1, buffer);

		trP = (POINT*)(f_pOISt->vpObjData);
		ltoa(trP->x,buffer,10);
		ltoa(trP->y,cnvrtBuf,10);
		strcat(buffer, " ");strcat(buffer, cnvrtBuf);
		if(f_pOISt->strComment){
			strcat(buffer, " ");
			strcat(buffer, f_pOISt->strComment);
		}
		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, buffer);
		break;
	case LNDID:
		strcat(szTitleDlg, "LogicalAnd");

//		hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
		ltoa(f_pOISt->GOColor,buffer,10);
		SetWindowText(hWndCol, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		ltoa(f_pOISt->objRect->left,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		ltoa(f_pOISt->objRect->top,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
		ltoa(f_pOISt->objRect->right,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
		ltoa(f_pOISt->objRect->bottom,buffer,10);
		SetWindowText(hWndObjName, buffer);

		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, f_pOISt->strComment);

//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
		EnableWindow(hWndBCol, FALSE);
//		hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
		EnableWindow(hWndBCol1, FALSE);

		break;
	}
	strcat(szTitleDlg, " Graphical Object");
	SetWindowText(hDlg, szTitleDlg);

	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	SetWindowText(hWndObjName, f_pOISt->strOMName);

	hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
	SetWindowText(hWndObjName, f_pOISt->strGOName);
	return 0;
}

/*CONTINENTAL*********************************************************
* Description: Create a child window with information from dialog
*
* Revision:
* 2000-09-09 luci 1.1 New
**********************************************************************/
UCHAR CreateChildWindow(HWND hDlg){

	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[20], objName[20];
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	GOCL_AddView(objName, f_parentWnd);

	LONG x, y, lx, ly, color;
	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,20);
	x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,20);
	y = atoi(buffer) + 25;

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName,buffer,20);
	lx = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,20);
	ly = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	color = atoi(buffer);

	GOCL_SetBounds(objName, x, y, lx, ly);

	GOCL_SetBackgroundColor(objName, color); //0x00E3351C = RGB(28,53,227)
	GOCL_SetVisible(objName, 1);
	GOCL_Refresh(objName);
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Destroy a child window with name from the dialog
*
* Revision:
* 2000-09-25 luci 1.1 New
**********************************************************************/
UCHAR DestroyChildWindow(HWND hDlg){

	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char objName[20];

	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		GOCL_DeleteGObject(objName);
		GOCL_Refresh("0");
		return 1;
	}
	MessageBox(hDlg, "The object does not exist!", "The object does not exist!", MB_OK);
	return 0;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Text" Graphival Object in the window
*
* Revision:
* 2000-09-25 luci 1.1 New
**********************************************************************/
UCHAR CreateTxtObject(HWND hDlg){
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[256], strComment[256], objName[20], szOMName[20];
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	LONG x, y, lx, ly, color, bcolor;
	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,256);
	x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,256);
	y = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName,buffer,256);
	lx = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,256);
	ly = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,256);
	color = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	GetWindowText(hWndBCol,buffer,256);
	bcolor = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName,buffer,256);

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName, strComment,256);

	GOCL_AddText(szOMName, objName, buffer, x, y, color, bcolor, strComment);

	int fSize, fAttrib;
	char *pbBuff, *peBuff;

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);//font String
	GetWindowText(hWndBCol1,buffer,256);

	pbBuff = buffer;
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		MessageBox(hDlg, "Not enough parameters in Font String!", "Text Object was created with default font!", MB_OK);
		GOCL_Refresh("0");
		return 1;
	}
	else{
		*peBuff = '\0';
		pbBuff = peBuff+1;
	}
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		fSize = atol(pbBuff);//font attributes
		fAttrib = 0;
	}
	else{
		*peBuff = '\0';
		fSize = atol(pbBuff);//font attributes
		pbBuff = peBuff+1;
		fAttrib = atol(pbBuff);//font attributes
	}

	GOCL_SetTextFont(szOMName, objName, buffer, fSize, fAttrib);
	GOCL_Refresh("0");
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Tube" Graphival Object in the window
*
* Revision:
* 2000-09-25 luci 1.1 New
**********************************************************************/
UCHAR CreateTubeObject(HWND hDlg)
{
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[256], objName[20], szOMName[20], *pbBuff, *peBuff;
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	POINT data[3];
	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,20);
	data[1].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,20);
	data[1].y = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName,buffer,20);
	data[2].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,20);
	data[2].y = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	data[0].y = atoi(buffer);//color 

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName,buffer,256);
//	data[0].x = atoi(buffer);//number of turns

	pbBuff = buffer;
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		data[0].x = atol(pbBuff);//number of turns
		pbBuff = NULL;	//commentStr
	}
	else{
		*peBuff = '\0';
		data[0].x = atol(pbBuff);//number of turns
		pbBuff = peBuff+1;
	}

	GOCL_AddTube(szOMName, objName, &data[0], pbBuff);
	GOCL_Refresh("0");
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Press" Graphival Object in the window
*
* Revision:
* 2000-09-25 luci 1.1 New
**********************************************************************/
UCHAR CreatePrsObject(HWND hDlg)
{
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[256], objName[20], szOMName[20], *pbBuff, *peBuff;
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	POINT data[4];
	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,20);
	data[1].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,20);
	data[1].y = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName,buffer,20);
	data[2].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,20);
	data[2].y = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	data[3].x = atoi(buffer);//color 

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	GetWindowText(hWndBCol,buffer,20);
	data[3].y = atoi(buffer);//Bcolor 

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName,buffer,256);

	pbBuff = buffer;
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		data[0].x = atol(pbBuff);//number of turns
		pbBuff = NULL;	//commentStr
	}
	else{
		*peBuff = '\0';
		data[0].x = atol(pbBuff);//number of turns
		pbBuff = peBuff+1;
	}

	GOCL_AddPress(szOMName, objName, &data[0], pbBuff);
	GOCL_Refresh("0");
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Poly Line" Graphival Object in the window
*
* Revision:
* 2000-09-25 luci 1.1 New
**********************************************************************/
UCHAR CreatePolyLineObj(HWND hDlg)
{
	POINT *data;
	int dPoints;
	char buffer[256], objName[20], szOMName[20], *pbBuff, *peBuff;

	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName, buffer,256);
	//5 200 350 200 370 200 360 250 360 250 370
	pbBuff = buffer;
	peBuff = strchr(pbBuff, ' ');
	*peBuff = '\0';
	dPoints = atoi(pbBuff);

	data = new POINT[dPoints+1];
	for(int i = 0; i < dPoints-1; i++)
	{
		pbBuff = peBuff+1;
		peBuff = strchr(pbBuff, ' ');
		*peBuff = '\0';
		data[i].x = atol(pbBuff);

		pbBuff = peBuff+1;
		peBuff = strchr(pbBuff, ' ');
		*peBuff = '\0';
		data[i].y = atol(pbBuff);
	}
	pbBuff = peBuff+1;
	peBuff = strchr(pbBuff, ' ');
	*peBuff = '\0';
	data[i].x = atol(pbBuff);

	pbBuff = peBuff+1;
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		data[i++].y = atol(pbBuff);
		data[i].y = NULL;	//commentStr
	}
	else{
		*peBuff = '\0';
		data[i++].y = atol(pbBuff);
		pbBuff = peBuff+1;
		data[i].y = (long)pbBuff;	//commentStr
	}

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	data[i].x = atoi(buffer);//color

	GOCL_AddPolyLine(szOMName, objName, &data[0], dPoints);
	GOCL_Refresh("0");

	delete data;

	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Polygone" Graphival Object in the window
*
* Revision:
* 2000-09-26 luci 1.1 New
**********************************************************************/
UCHAR CreatePolyGoneObj(HWND hDlg)
{
	POINT *data;
	int dPoints;
	char buffer[256], objName[20], szOMName[20], *pbBuff, *peBuff;

	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName, buffer,256);
	//10 90 255 100 255 100 275 95 275 95 255 95 265 110 265 95 265 95 275 90 275
	pbBuff = buffer;
	peBuff = strchr(pbBuff, ' ');
	*peBuff = '\0';
	dPoints = atoi(pbBuff);

	data = new POINT[dPoints+2];
	for(int i = 0; i < dPoints-1; i++)
	{
		pbBuff = peBuff+1;
		peBuff = strchr(pbBuff, ' ');
		*peBuff = '\0';
		data[i].x = atol(pbBuff);

		pbBuff = peBuff+1;
		peBuff = strchr(pbBuff, ' ');
		*peBuff = '\0';
		data[i].y = atol(pbBuff);
	}
	pbBuff = peBuff+1;
	peBuff = strchr(pbBuff, ' ');
	*peBuff = '\0';
	data[i].x = atol(pbBuff);

	pbBuff = peBuff+1;
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		data[i++].y = atol(pbBuff);
		data[i+1].y = NULL;	//commentStr
	}
	else{
		*peBuff = '\0';
		data[i++].y = atol(pbBuff);
		pbBuff = peBuff+1;
		data[i+1].y = (long)pbBuff;	//commentStr
	}
//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	data[i].x = atoi(buffer);//color

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	GetWindowText(hWndBCol,buffer,20);
	data[i++].y = atoi(buffer); //bcolor1

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
	GetWindowText(hWndBCol1,buffer,20);
	data[i].x = atoi(buffer);//bcolor2

	GOCL_AddPolygon(szOMName, objName, &data[0], dPoints);
	GOCL_Refresh("0");

	delete data;
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "LogicalAnd" Graphival Object in the window
*
* Revision:
* 2000-09-26 luci 1.1 New
**********************************************************************/
UCHAR CreateLogAndObj(HWND hDlg)
{
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[256], objName[20], szOMName[20];
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	POINT data[3];
	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,20);
	data[0].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,20);
	data[0].y = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName,buffer,20);
	data[1].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,20);
	data[1].y = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	data[2].x = atoi(buffer);//color

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	GetWindowText(hWndBCol,buffer,20);
	data[2].y = atoi(buffer);//bcolor

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName,buffer,256);

	GOCL_AddLogicalAnd(szOMName, objName, &data[0], buffer);
	GOCL_Refresh("0");
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Circle" Graphival Object in the window
*
* Revision:
* 2000-09-26 luci 1.1 New
**********************************************************************/
UCHAR CreateCircleObj(HWND hDlg)
{
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[256], objName[20], szOMName[20];
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}
//5 110 410 65280 65280 65280
	POINT data[4];

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,20);
	data[0].x = atoi(buffer);//radius

	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,20);
	data[0].y = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,20);
	data[1].x = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	data[1].y = atoi(buffer);//color

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	GetWindowText(hWndBCol,buffer,20);
	data[2].x = atoi(buffer);//bcolor

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
	GetWindowText(hWndBCol1,buffer,20);
	data[2].y = atoi(buffer);//bcolor2

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName,buffer,256);
	data[3].x = (long)buffer;	//comment

	GOCL_AddCircle(szOMName, objName, &data[0]);
	GOCL_Refresh("0");
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Box" Graphival Object in the window
*
* Revision:
* 2000-09-26 luci 1.1 New
**********************************************************************/
UCHAR CreateBoxObj(HWND hDlg)
{
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[256], objName[20], szOMName[20];
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	POINT data[4];
	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,20);
	data[0].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,20);
	data[0].y = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName,buffer,20);
	data[1].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,20);
	data[1].y = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol,buffer,20);
	data[2].x = atoi(buffer);//color

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	GetWindowText(hWndBCol,buffer,20);
	data[2].y = atoi(buffer);//bcolor1

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1);
	GetWindowText(hWndBCol1,buffer,20);
	data[3].x = atoi(buffer);//bcolor2

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName,buffer,256);
	data[3].y = (long)buffer;//comment

	GOCL_AddBox(szOMName, objName, &data[0]);
	GOCL_Refresh("0");
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Choose a color from the colorDialog
*
* Revision:
* 2000-09-26 luci 1.1 New
**********************************************************************/
UCHAR ChooseColorDlg(HWND hDlg)
{
	HWND hWndObjName;
	char buffer[20];
	CHOOSECOLOR vColorChStruct;
	unsigned long defaultCol = 0;

	switch(f_EColorID){//set the default color
	case IDC_ECOLOR:
		hWndObjName = hWndCol;
		break;
	case IDC_EBCOLOR:
		hWndObjName = hWndBCol;
		break;
	case IDC_EBCOLOR1:
		hWndObjName = hWndBCol1;
		break;
	}
	GetWindowText(hWndObjName,buffer,20);
	defaultCol = atol(buffer);

	memset(&vColorChStruct, 0, sizeof(CHOOSECOLOR));

	vColorChStruct.lStructSize = sizeof(CHOOSECOLOR);
	vColorChStruct.hwndOwner = hDlg;

	vColorChStruct.hInstance = (HWND)1;
	vColorChStruct.lpCustColors = &defaultCol;

	if(!ChooseColor(&vColorChStruct))
		return 0;

	ltoa(vColorChStruct.rgbResult, buffer, 10);
	SetWindowText(hWndObjName,buffer);
	return 1;
}

//IDC_FONTB
/*CONTINENTAL*********************************************************
* Description: Take the hwnd from the Dialog used controls
*
* Revision:
* 2000-10-02 luci 1.1 New
**********************************************************************/
UCHAR InitDialogHWnds(HWND hDlg)
{
	hWndCol = GetDlgItem(  hDlg, IDC_ECOLOR);
	hWndBCol = GetDlgItem(  hDlg, IDC_EBCOLOR);
	hWndBCol1 = GetDlgItem(  hDlg, IDC_EBCOLOR1);
	hWndColBtn = GetDlgItem(  hDlg, IDC_BCOLORS);
	hWndFntBtn = GetDlgItem(  hDlg, IDC_FONTB);
	hWndStartRP = GetDlgItem(  hDlg, IDC_STARTRP);
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Choose a Font from the FontDialog
*
* Revision:
* 2000-10-02 luci 1.1 New
**********************************************************************/
UCHAR ChooseFontDlg(HWND hDlg)
{
	CHOOSEFONT	vFontChStruct;
//	LOGFONT		lf;

	memset(&vFontChStruct, 0, sizeof(CHOOSEFONT));

	vFontChStruct.lStructSize = sizeof(CHOOSEFONT);
	vFontChStruct.hwndOwner = hDlg;
	vFontChStruct.rgbColors = 16777215;
	vFontChStruct.nFontType = REGULAR_FONTTYPE;
	vFontChStruct.iPointSize = 10;
	vFontChStruct.Flags = CF_EFFECTS | CF_TTONLY;

//	vFontChStruct. = &defaultCol;*/

/*	if(!ChooseFont(&vFontChStruct))
		return 0;
*/
	ChooseFont(&vFontChStruct);
	switch(CommDlgExtendedError()){
	case CDERR_FINDRESFAILURE:
		break;
	case CDERR_NOHINSTANCE:
		break;
	case CDERR_INITIALIZATION :
		break;
	case CDERR_NOHOOK :
		break;
	case CDERR_LOCKRESFAILURE :
		break;
	case CDERR_NOTEMPLATE :
		break;
	case CDERR_LOADRESFAILURE :
		break;
	case CDERR_STRUCTSIZE :
		break;
	case CDERR_LOADSTRFAILURE :
		break;
	case CFERR_MAXLESSTHANMIN :
		break;
	case CDERR_MEMALLOCFAILURE :
		break;
	case CFERR_NOFONTS :
		break;
	case CDERR_MEMLOCKFAILURE :
		break;
	}
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Create a "Molder" Graphival Object in the window
*
* Revision:
* 2000-10-04 luci 1.1 New
**********************************************************************/
UCHAR CreateMldObject(HWND hDlg)
{
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char buffer[256], objName[20], szOMName[20], *pbBuff, *peBuff;
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	POINT data[4];
	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	GetWindowText(hWndObjName,buffer,20);
	data[0].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	GetWindowText(hWndObjName,buffer,20);
	data[0].y = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);
	GetWindowText(hWndObjName,buffer,20);
	data[1].x = atoi(buffer);

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	GetWindowText(hWndObjName,buffer,20);
	data[1].y = atoi(buffer);

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	GetWindowText(hWndCol, buffer,20);
	data[3].x = atoi(buffer);//color 

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	GetWindowText(hWndBCol,buffer,20);
	data[3].y = atoi(buffer);//Bcolor 

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	GetWindowText(hWndObjName,buffer,256);

	pbBuff = buffer;
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		MessageBox(hDlg, "Not enough parameters in FreeText Edit Box!", "Not enough parameters!", MB_OK);
		return 0;
	}
	else{
		*peBuff = '\0';
		data[2].x = atol(pbBuff);//elipse parameter 1
		pbBuff = peBuff+1;
	}
	if((peBuff = strchr(pbBuff, ' ')) == NULL){
		data[2].y = atol(pbBuff);//elipse parameter 2
		pbBuff = NULL;	//commentStr
	}
	else{
		*peBuff = '\0';
		data[2].y = atol(pbBuff);//elipse parameter 2
		pbBuff = peBuff+1;
	}

	GOCL_AddMold(szOMName, objName, &data[0], pbBuff);
	GOCL_Refresh("0");
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Select Graphival Object to edit in the window
*
* Revision:
* 2000-10-04 luci 1.1 New
**********************************************************************/
UCHAR EditGObjectOK(HWND hDlg)
{
	switch(f_pOISt->objType)
	{
	case BOXID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreateBoxObj(hDlg);
	case TXTID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreateTxtObject(hDlg);
	case CIRCLEID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreateCircleObj(hDlg);
	case POLYGID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreatePolyGoneObj(hDlg);
	case POLYLID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreatePolyLineObj(hDlg);
	case GROUPID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
	case TUBID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreateTubeObject(hDlg);
	case PRESID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreatePrsObject(hDlg);
	case MOLDID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreateMldObject(hDlg);
	case LNDID:
		GOCL_DeleteGObject(f_pOISt->strGOName);
		return CreateLogAndObj(hDlg);
	}
	return 0;
}

/*CONTINENTAL*********************************************************
* Description: set the initial values to create a normal text object
*
* Revision:
* 2000-10-04 luci 1.1 New
**********************************************************************/
void InitDialogTxt(HWND hDlg)
{
HWND hWndObjName;
	SetWindowText(hDlg, "Create New Text");
	ShowWindow(hWndFntBtn, SW_SHOW);

	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	SetWindowText(hWndObjName, "Window1");

	hWndObjName = GetDlgItem(  hDlg, IDC_ONAME);
	SetWindowText(hWndObjName, "Text1");

	hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
	SetWindowText(hWndObjName, "0");

	hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
	SetWindowText(hWndObjName, "0");

	hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
	SetWindowText(hWndObjName, "IAmATextObject");

//	hWndObjName = GetDlgItem(  hDlg, IDC_ECOLOR);
	SetWindowText(hWndCol, "15461355");

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR);
	SetWindowText(hWndBCol, "0");

	hWndObjName = GetDlgItem(  hDlg, IDC_ERIGHT);//comment
	RECT vRect;
	GetWindowRect(  hWndObjName, &vRect );
	MapWindowPoints(NULL, hDlg, (POINT *)&vRect, 2);
	MoveWindow(hWndObjName, vRect.left-71, vRect.top, vRect.right-vRect.left+71, vRect.bottom - vRect.top, FALSE);
	SetWindowText(hWndObjName,"Insert Comment here");

	hWndObjName = GetDlgItem(  hDlg, IDC_BOTTOMLBL);
	SetWindowText(hWndObjName,"C");

	hWndObjName = GetDlgItem(  hDlg, IDC_RIGHTLBL);
	ShowWindow(hWndObjName, SW_HIDE);

//	hWndObjName = GetDlgItem(  hDlg, IDC_EBCOLOR1); //font
	SetWindowText(hWndBCol1,"arial 18 8");

	hWndObjName = GetDlgItem(  hDlg, IDC_BAKGROUND1LBL);
	SetWindowText(hWndObjName,"Fn");

	hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
	EnableWindow(hWndObjName, FALSE);
}

/*CONTINENTAL*********************************************************
* Description: Record one or more points using mouse
*
* Revision:
* 2000-10-02 luci 1.1 New
**********************************************************************/
UCHAR StartRecPoints(HWND hDlg)
{
	SetCapture(  hDlg );
	EnableWindow(hWndStartRP, FALSE);
//	ShowWindow(hDlg, FALSE);
	if(f_buttonID == ID_POGCNEWO || f_buttonID == ID_POLCNEWO || (f_buttonID == ID_EDITGO && (f_pOISt->objType == POLYGID || f_pOISt->objType == POLYLID))){
		f_noOfPtsToRec = 0;//number of points recorded
		HWND hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);
		SetWindowText(hWndObjName, "");
	}
	else if(f_buttonID >= ID_BOXCNEWO && f_buttonID <=ID_WNDCNEWO || (f_buttonID == ID_EDITGO && f_pOISt->objType >= TXTID && f_pOISt->objType <= LNDID))
		f_noOfPtsToRec = 2;
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Process Left Button Up message on dialog
*
*	fwKeys - key flags 
*	xPos = LOWORD(yxPos);  // horizontal position of cursor 
*	yPos = HIWORD(yxPos);  // vertical position of cursor
*
* Revision:
* 2000-10-02 luci 1.1 New
**********************************************************************/
UCHAR OnDlgLButtonUp(HWND hDlg, WPARAM fwKeys, LPARAM yxPos)
{
	if(hDlg != GetCapture())
		return 0;

	char buffer[20];
	HWND hWndObjName;
	if(f_buttonID == ID_POGCNEWO || f_buttonID == ID_POLCNEWO || (f_buttonID == ID_EDITGO && (f_pOISt->objType == POLYGID || f_pOISt->objType == POLYLID)))
	{
		f_noOfPtsToRec++;
		hWndObjName = GetDlgItem(  hDlg, IDC_FREETEXT);

		char strResult[512] = "", strOld[512], *strPtr;

		itoa(f_noOfPtsToRec, strResult, 10);
		strcat(strResult, " ");

		if(f_noOfPtsToRec > 1){
			GetWindowText(hWndObjName, strOld, 512);
			strPtr = strchr(strOld, ' ');
			strcat(strResult, strPtr+1);
			strcat(strResult, " ");
		}
		itoa(LOWORD(yxPos), buffer, 10);
		strcat(strResult, buffer);
		strcat(strResult, " ");

		itoa(HIWORD(yxPos), buffer, 10);
		strcat(strResult, buffer);
		SetWindowText(hWndObjName, strResult);
	}
	else if(f_buttonID == ID_TXTCNEWO || (f_buttonID == ID_EDITGO && f_pOISt->objType == TXTID))
	{
		itoa(LOWORD(yxPos), buffer, 10);
		hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
		SetWindowText(hWndObjName, buffer);

		itoa(HIWORD(yxPos), buffer, 10);
		hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
		SetWindowText(hWndObjName, buffer);

		ReleaseCapture();
		EnableWindow(hWndStartRP, TRUE);
	}
	else if(f_buttonID == ID_CIRCNEWO || (f_buttonID == ID_EDITGO && f_pOISt->objType == CIRCLEID)){
		f_noOfPtsToRec--;
		if(f_noOfPtsToRec > 0){
			//set the first point in the box
			itoa(LOWORD(yxPos), buffer, 10);
			hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
			SetWindowText(hWndObjName, buffer);

			itoa(HIWORD(yxPos), buffer, 10);
			hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
			SetWindowText(hWndObjName, buffer);
			f_prevPct.x = LOWORD(yxPos);
			f_prevPct.y = HIWORD(yxPos);
		}
		else{
			f_prevPct.y -= HIWORD(yxPos);
			f_prevPct.x -= LOWORD(yxPos);
			f_prevPct.y = f_prevPct.y < 0?-f_prevPct.y: f_prevPct.y;
			f_prevPct.x = f_prevPct.x < 0?-f_prevPct.x: f_prevPct.x;
			itoa(f_prevPct.x < f_prevPct.y?f_prevPct.y:f_prevPct.x, buffer, 10);
			hWndObjName = GetDlgItem(  hDlg, IDC_EBOTTOM);
			SetWindowText(hWndObjName, buffer);

			ReleaseCapture();
			EnableWindow(hWndStartRP, TRUE);
		}
	}
	else if((f_buttonID >= ID_BOXCNEWO && f_buttonID <=ID_WNDCNEWO) || (f_buttonID == ID_EDITGO && f_pOISt->objType >= TXTID && f_pOISt->objType <= LNDID))
	{
		f_noOfPtsToRec--;
		if(f_noOfPtsToRec > 0){
			//set the first point in the box
			itoa(LOWORD(yxPos), buffer, 10);
			hWndObjName = GetDlgItem(  hDlg, IDC_ELEFT);
			SetWindowText(hWndObjName, buffer);

			itoa(HIWORD(yxPos), buffer, 10);
			hWndObjName = GetDlgItem(  hDlg, IDC_ETOP);
			SetWindowText(hWndObjName, buffer);
		}
		else{
			itoa(LOWORD(yxPos), buffer, 10);
			hWndObjName = GetDlgItem( hDlg, IDC_ERIGHT);
			SetWindowText(hWndObjName, buffer);

			itoa(HIWORD(yxPos), buffer, 10);
			hWndObjName = GetDlgItem( hDlg, IDC_EBOTTOM);
			SetWindowText(hWndObjName, buffer);

			ReleaseCapture();
			EnableWindow(hWndStartRP, TRUE);
		}
	}
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Process Left Button Up message on dialog
*		Force End capture for dialog
*	fwKeys - key flags 
*	xPos = LOWORD(yxPos);  // horizontal position of cursor 
*	yPos = HIWORD(yxPos);  // vertical position of cursor
*
* Revision:
* 2000-10-02 luci 1.1 New
**********************************************************************/
UCHAR OnDlgRButtonUp(HWND hDlg, WPARAM fwKeys, LPARAM yxPos)
{
	if(hDlg != GetCapture())
		return 0;

	ReleaseCapture();
	EnableWindow(hWndStartRP, TRUE);
	return 1;
}

/*CONTINENTAL*********************************************************
* Description: Select Graphival Object to edit in the window
*
* Revision:
* 2000-10-04 luci 1.1 New
**********************************************************************/
UCHAR PasteGrObject(HWND hDlg)
{
	switch(f_pOISt->objType)
	{
	case BOXID:
		return CreateBoxObj(hDlg);
	case TXTID:
		return CreateTxtObject(hDlg);
	case CIRCLEID:
		return CreateCircleObj(hDlg);
	case POLYGID:
		return CreatePolyGoneObj(hDlg);
	case POLYLID:
		return CreatePolyLineObj(hDlg);
	case GROUPID:
		break;
	case TUBID:
		return CreateTubeObject(hDlg);
	case PRESID:
		return CreatePrsObject(hDlg);
	case MOLDID:
		return CreateMldObject(hDlg);
	case LNDID:
		return CreateLogAndObj(hDlg);
	}
	return 0;
}

/*CONTINENTAL*********************************************************
* Description: Creat a Group Graphival Object to edit in the window
*
* Revision:
* 2000-10-04 luci 1.1 New
**********************************************************************/
UCHAR CreateGrpObject(HWND hDlg)
{
	HWND hWndObjName = GetDlgItem( hDlg, IDC_ONAME);
	char objName[20], szOMName[20];
	GetWindowText(hWndObjName,objName,20);
	if(GOCL_IsObject(objName)){
		MessageBox(hDlg, "Object with the specified name already exist!", "Choose a different name for the new Object!", MB_OK);
		return 0;
	}
	hWndObjName = GetDlgItem(  hDlg, IDC_OMNAME);
	GetWindowText(hWndObjName,szOMName,20);
	if(!GOCL_IsObject(szOMName)){
		MessageBox(hDlg, "The specified Object Manager Name does NOT Exist!", "Choose a different name for the Object Manager!", MB_OK);
		return 0;
	}

	GOCL_AddGroup(szOMName, objName);
	MessageBox(hDlg, "The Group was succesfuly created !", "The Group was succesfuly created !", MB_OK);
	return 1;
}