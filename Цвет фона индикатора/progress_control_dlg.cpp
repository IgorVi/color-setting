#include "progress_control_dlg.h"

#define MIN 0
#define MAX 255

ProgressControlDlg* ProgressControlDlg::ptr = NULL;

ProgressControlDlg::ProgressControlDlg(void)
{
	ptr = this;
}

void ProgressControlDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL ProgressControlDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	
	hRedSlider = GetDlgItem(hDialog, IDC_SLIDER1);
	SendMessage(hRedSlider, TBM_SETRANGE, 0, MAKELPARAM(MIN, MAX));

	hGreenSlider = GetDlgItem(hDialog, IDC_SLIDER2);
	SendMessage(hGreenSlider, TBM_SETRANGE, 0, MAKELPARAM(MIN, MAX));

	hBlueSlider = GetDlgItem(hDialog, IDC_SLIDER3);
	SendMessage(hBlueSlider, TBM_SETRANGE, 0, MAKELPARAM(MIN, MAX));


	hProgress = GetDlgItem(hDialog, IDC_PROGRESS1);
	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 1)); // Установка интервала для индикатора 
	SendMessage(hProgress, PBM_SETSTEP, 1, 0); // Установка шага приращения  индикатора 
	SendMessage(hProgress, PBM_SETPOS, 1, 0); // Установка текущей позиции индикатора
	SendMessage(hProgress, PBM_SETBKCOLOR, 0, LPARAM(RGB(255, 255, 255))); // Установка цвета фона индикатора
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 0, 0))); // Установка цвета заполняемых прямоугольников

	SetWindowText(hDialog, TEXT("Red: 0   Green: 0   Blue: 0"));
		
	SetClassLong(hwnd, GCL_HICON, LONG(LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1))));
	
	return TRUE;
}

void ProgressControlDlg::Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	static TCHAR str[50];
	static int PositionRed = 0;
	static int PositionGreen = 0;
	static int PositionBlue = 0;

	if (hwndCtl == hRedSlider)
		PositionRed = SendMessage(hwndCtl, TBM_GETPOS, TRUE, MAKELPARAM(MIN, MAX));
	else if (hwndCtl == hGreenSlider)
		PositionGreen = SendMessage(hwndCtl, TBM_GETPOS, TRUE, MAKELPARAM(MIN, MAX));
	else if (hwndCtl == hBlueSlider)
		PositionBlue = SendMessage(hwndCtl, TBM_GETPOS, TRUE, MAKELPARAM(MIN, MAX));
		
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(PositionRed, PositionGreen, PositionBlue))); // Установка цвета заполняемых прямоугольников

	wsprintf(str, TEXT("Red: %d   Green: %d   Blue: %d"), PositionRed, PositionGreen, PositionBlue);
	SetWindowText(hDialog, str);
}

BOOL CALLBACK ProgressControlDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_HSCROLL, ptr->Cls_OnHScroll);
	}
	return FALSE;
}