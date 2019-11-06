// MyWindow.h:
#include "stdafx.h"
#define  TT_MSG (WM_USER + 111)

class CMyWindow : public CFrameWindowImpl<CMyWindow>
{
public:
	DECLARE_FRAME_WND_CLASS(_T("First WTL window"), IDR_MAINFRAME);

	BEGIN_MSG_MAP(CMyWindow)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMyWindow>)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CREATE(creatMsg)
	    MSG_WM_TIMER(OnTimer)
		//MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MSG_WM_MOUSEMOVE(OnMouseMove)
	    MSG_WM_PAINT(OnPaint)
	
	END_MSG_MAP()

	CPoint currentPoint;
	
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam) {
		SetWindowText("test");
		return TRUE;
	}

	int creatMsg(LPCREATESTRUCT lpCreateStruct)
	{
		SetTimer(2, 100);

	//	SetMsgHandled(false);

		return 0;
	}



	void OnTimer(UINT_PTR wParamc)

	{

		//if (1 != wParamc)

		//	SetMsgHandled(false);

	//	else

			RedrawWindow();

	}

	LRESULT OnEraseBkgnd(HDC hdc)

	{

		CDCHandle  dc(hdc);

		CRect      rc;

		SYSTEMTIME st;

		CString    sTime;

		// Get our window's client area.

		GetClientRect(rc);

		// Build the string to show in the window.

		GetLocalTime(&st);

		sTime.Format(_T("The time is %d:%02d:%02d %d %d"),

		st.wHour, st.wMinute, st.wSecond,currentPoint.x,currentPoint.y);


		// Set up the DC and draw the text.

		dc.SaveDC();

	//	dc.SetBkColor(RGB(255, 153, 0));

		dc.SetTextColor(RGB(0, 0, 0));


		dc.ExtTextOut(0, 0, ETO_OPAQUE, rc, sTime,

		sTime.GetLength(), NULL);

		// Restore the DC.


		dc.RestoreDC(-1);

		return 1;    // We erased the background (ExtTextOut did it)

	}

	void OnDestory() {

	}
	//lResult = (LRESULT)func((HWND)wParam, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam))

	void OnMouseMove(UINT nFlags, CPoint point) {
	
		currentPoint = point;
	
	}

	void OnPaint(CDCHandle dc) {

		//CClientDC cdc(m_hWnd);

		CPaintDC cdc(m_hWnd);
		HBRUSH br = CreateSolidBrush(RGB(255, 0, 0));

		CRect rc;
		GetClientRect(&rc);
		cdc.FillRect(&rc, br);
		
		//pdc.SetBkColor(RGB(255, 100, 100));
	}
	
};


