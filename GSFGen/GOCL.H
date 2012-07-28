//gocl.h

	BOOL APIENTRY GOCL_GetSelectedObjInfo(void *objInfoStruct);
	void APIENTRY GOCL_SetEditMode(UCHAR bEditMode);
	BOOL APIENTRY GOCL_AddMold(char *szOMName, char *moldName, POINT *data, LPSTR szCText);
	BOOL APIENTRY GOCL_MoveClientW(char * wId, LONG x, LONG y);
	BOOL APIENTRY GOCL_LoadAllObjects(LPSTR, HWND hparentWnd);
	BOOL APIENTRY GOCL_SaveAllObjects(LPSTR);
	LONG APIENTRY GOCL_AddView(char *wName, HWND hwndParent);
	BOOL APIENTRY GOCL_SetBounds(char *, LONG x, LONG y, LONG width, LONG height);
	BOOL APIENTRY GOCL_SetVisible(char *, BOOL bVisible);
	BOOL APIENTRY GOCL_DeleteGObject(char * );
	WORD APIENTRY GOCL_SetBackgroundColor(char *, LONG bkColor);
	LONG APIENTRY GOCL_AddText(char *szOMName, char *txtName, LPSTR szText, LONG x, LONG y, LONG color, LONG bcolor, LPSTR szCText);
	BOOL APIENTRY GOCL_Refresh(char * hidx);
	BOOL APIENTRY GOCL_SetTextFont(char * , char *, char *, int , int );
	BOOL APIENTRY GOCL_GobjMove(char *szOMName, char *goName, POINT mhlpoint);
	BOOL APIENTRY GOCL_GobjMoveTo(char * wndId, char *grpId, char *txtoId, POINT fpoint);
	LONG APIENTRY GOCL_AddBox(char *szOMName, char *boxName, POINT *params);
	LONG APIENTRY GOCL_AddCircle(char *szOMName, char *cirName, POINT *pointst);
	LONG APIENTRY GOCL_AddPolygon(char *szOMName, char *pgName, POINT *pointArray, int nofpct);
	LONG APIENTRY GOCL_AddGroup(char * wndId, char *gID);
	LONG APIENTRY GOCL_AddPolyLine(char *szOMName, char *plName, POINT *pointArray, int nofpct);
	BOOL APIENTRY GOCL_AddLogicalAnd(char *szOMName, char *lndName, POINT *params, LPSTR szCText);
	LONG APIENTRY GOCL_GobjChgColors(char * wID, char *grpId, char *objID, LONG bcolor, LONG color);
	LONG APIENTRY GOCL_AddTube(char *szOMName, char *tubeName, POINT *data, LPSTR szCText);
	BOOL APIENTRY GOCL_AddPress(char *szOMName, char *presName, POINT *data, LPSTR szCText);
	BOOL APIENTRY GOCL_IsObject(char *);

	BOOL APIENTRY GOCL_ChangeTxt(char *wndName, char *grpName, char *txtoName, LPSTR szText);
	BOOL APIENTRY GOCL_TakeNextCommentStr(char *wndName, char *grName, char *oName, LPSTR CommentStr);
