//NewObjectDlg.h 
//#include "GSFGen.h"
#include "resource.h"
#include "gocl.h"
#include "commdlg.h"
#include "cderr.h"

#if !defined(AFX_NEWOBJECTDLG_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_)
#define AFX_GSFGEN_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_

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

UCHAR PasteGrObject(HWND hDlg);
UCHAR OnDlgRButtonUp(HWND hDlg, WPARAM fwKeys, LPARAM yxPos);
UCHAR OnDlgLButtonUp(HWND hDlg, WPARAM fwKeys, LPARAM yxPos);
UCHAR StartRecPoints(HWND hDlg);
void InitDialogTxt(HWND hDlg);
UCHAR EditGObjectOK(HWND hDlg);
UCHAR SelectEditGrObj(HWND hDlg);
UCHAR CreateGrpObject(HWND hDlg);
UCHAR CreateMldObject(HWND hDlg);
UCHAR ChooseFontDlg(HWND hDlg);
UCHAR InitDialogHWnds(HWND hDlg);
UCHAR ChooseColorDlg(HWND hDlg);
UCHAR CreateBoxObj(HWND hDlg);
UCHAR CreateCircleObj(HWND hDlg);
UCHAR CreateLogAndObj(HWND hDlg);
UCHAR CreatePolyGoneObj(HWND hDlg);
UCHAR CreatePolyLineObj(HWND hDlg);
UCHAR CreatePrsObject(HWND hDlg);
UCHAR CreateTubeObject(HWND hDlg);
UCHAR CreateTxtObject(HWND hDlg);
UCHAR DestroyChildWindow(HWND hDlg);
UCHAR CreateChildWindow(HWND hDlg);
void InitDialog(HWND hDlg);
UCHAR CreateNewObject(HWND hDlg);
void ShowWCreateO(HINSTANCE hInst, HWND hWnd, LONG buttonID, OBJINFO *pOISt = NULL);
LRESULT CALLBACK CreateNewODlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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

#endif // !defined(AFX_NEWOBJECTDLG_H__7E3A6CF8_CCCC_11D3_ACAF_00500449492C__INCLUDED_)
