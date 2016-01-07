#include <windows.h>
#include <windowsX.h>
#include <ctime>
#include <CommCtrl.h>

#include <commctrl.h> // описание сообщений вроде PBM_SETBARCOLOR

#include "resource.h"

class ProgressControlDlg
{
public:
	ProgressControlDlg(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ProgressControlDlg* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
	void Cls_OnClose(HWND hwnd);
	HWND hDialog, hProgress, hRedSlider, hGreenSlider, hBlueSlider;
};
