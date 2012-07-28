// NewObjDlg.h: interface for the NewObjDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWOBJDLG_H__3CBE6084_BA26_11D4_ACBF_F820C6B3A930__INCLUDED_)
#define AFX_NEWOBJDLG_H__3CBE6084_BA26_11D4_ACBF_F820C6B3A930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct {
	UCHAR objType;
	char *strGOName;
	char *strComment;
	char *strOMName;
	char *fntName;
	RECT *objRect;
	long GOColor;
	long GOBColor;
	long GOBColor1;
	UCHAR dNoOfPoints;
	void *vpObjData;
}OBJINFO;

#define TXTID			0
#define BOXID			1
#define CIRCLEID		2
#define POLYGID			3
#define POLYLID			4
#define GROUPID			5
#define TUBID			6
#define PRESID			7
#define MOLDID			8
#define LNDID			9

class NewObjDlg  
{
public:
	UCHAR PasteGrObject(HWND hDlg);
	UCHAR EditGObjectOK(HWND hDlg);
	UCHAR CreateChildWindow(HWND hDlg);
	UCHAR DestroyChildWindow(HWND hDlg);
	UCHAR CreateGrpObject(HWND hDlg);
	UCHAR CreateMldObject(HWND hDlg);
	UCHAR CreateTxtObject(HWND hDlg);
	UCHAR CreateTubeObject(HWND hDlg);
	UCHAR CreatePrsObject(HWND hDlg);
	UCHAR CreatePolyLineObj(HWND hDlg);
	UCHAR CreatePolyGoneObj(HWND hDlg);
	UCHAR CreateLogAndObj(HWND hDlg);
	UCHAR CreateCircleObj(HWND hDlg);
	UCHAR CreateBoxObj(HWND hDlg);
	UCHAR SelectEditGrObj(HWND hDlg);
	void InitDialogTxt(HWND hDlg);
	UCHAR InitDialogHWnds(HWND hDlg);
	UCHAR OnDlgRButtonUp(HWND hDlg, WPARAM fwKeys, LPARAM yxPos);
	UCHAR OnDlgLButtonUp(HWND hDlg, WPARAM fwKeys, LPARAM yxPos);
	UCHAR StartRecPoints(HWND hDlg);
	UCHAR ChooseFontDlg(HWND hDlg);
	UCHAR ChooseColorDlg(HWND hDlg);
	UCHAR CreateNewObject(HWND hDlg);
	void InitDialog(HWND hDlg);

	LONG f_buttonID;
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

	static LRESULT CALLBACK CreateNewODlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void ShowWCreateO(HINSTANCE hInst, HWND hWnd, LONG buttonID, OBJINFO *pOISt);
	NewObjDlg();
	virtual ~NewObjDlg();

};

#endif // !defined(AFX_NEWOBJDLG_H__3CBE6084_BA26_11D4_ACBF_F820C6B3A930__INCLUDED_)
