#pragma once
#include "stdafx.h"
#include "ZXTools.h"
#include "ContentView.h"
#include "ZXKeyboardWindow.h"
#include "views/TableView.h"
#include <chrono>   


using namespace std;

using namespace chrono;
typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN , WS_EX_APPWINDOW> CMyWindowTraits;
class TestView :public CWindowImpl<TestView, CWindow,CMyWindowTraits> ,public CDoubleBufferImpl<TestView> ,public TableViewProtocol
{
	
public:

	DECLARE_WND_CLASS(_T("TestView"))

	BEGIN_MSG_MAP(TestView)

		MSG_WM_CREATE(OnCreate)
	    CHAIN_MSG_MAP(CDoubleBufferImpl<TestView>)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_SIZE(OnSize)
		COMMAND_ID_HANDLER(ID_MENU1_SHOWABOUT, OnMenuClick)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_VSCROLL(OnVScroll)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		

	END_MSG_MAP()




	void OnSize(UINT nType, CSize size) {

	if (scroller)
	{
		CRect windowRect;
		GetClientRect(windowRect);
		CRect scrollerRect;
		scrollerRect.top = 0;
		scrollerRect.bottom = windowRect.Height();
		scrollerRect.left = 0;
		scrollerRect.right = 30;

		scroller.MoveWindow(scrollerRect);
		OnLeftScrollerScrol(scroller.GetScrollPos());
	
	}
	if (keyboardWindow)
	{
		CRect windowRect;
		GetClientRect(windowRect);
		CRect scrollerRect;
		scrollerRect.top = 0;
		scrollerRect.bottom = windowRect.Height();
		scrollerRect.left = 320;
		scrollerRect.right = windowRect.right;
		keyboardWindow.MoveWindow(scrollerRect);
	}


	}

	void OnPaint(CDCHandle)
	{

		CPaintDC dc(m_hWnd);

		DoPaint(dc.m_hDC);

	}

	void DoPaint(CDCHandle  cdc) {


			HBRUSH br = CreateSolidBrush(RGB(0, 255, 0));

			CRect rc;
			GetClientRect(&rc);
			cdc.FillRect(&rc, br);

	}


	int OnCreate(LPCREATESTRUCT lpCreateStruct) {
		 HMENU hmenu = LoadMenu ( _Module.GetResourceInstance(),  
                             MAKEINTRESOURCE(IDR_MENU1) );  

        SetMenu ( hmenu );  

		creatContent();

	//	refershScrollerParm();
		
		return 0;
	}

	//HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled
	LRESULT OnMenuClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CString ID;

		ID.Format(("id %d"), wID);

		SetWindowText(ID);

		return 0;

	}



	void creatContent(){
		
		
		//content.Create(NULL, m_hWnd, rectExtension::ZXRectCreatWith(0, 10, 200, 1000),NULL, WS_CHILD | WS_VISIBLE, WS_CHILD | WS_VISIBLE,0U,NULL);
		content.Create(m_hWnd, rectExtension::ZXRectCreatWith(30, 0, 200, 300000), "", WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN |WS_CLIPSIBLINGS, NULL, 0U, NULL);

	 //   table.Create(m_hWnd, rectExtension::ZXRectCreatWith(240, 50, 500, 500), "", WS_CHILD | WS_VISIBLE, NULL, 0U, NULL);
	//	table.delegate = this;
		CRect windowRect;
		GetWindowRect(windowRect);
	
		
		for (int i = 0 ; i < 5000 ;i++)
		{
			CString title;
		    title.Format(("listBtn%d"), i);
			CButton btn1;
			btn1.Create(content, rectExtension::ZXRectCreatWith(10, 60 * i , 180, 50), title , WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, NULL, 0U, NULL);
		}

		scroller.Create(m_hWnd, rectExtension::ZXRectCreatWith(0, 0, 30, 500), NULL, SBS_VERT | WS_CHILD | WS_VISIBLE , NULL, ID_SCROLLER_MAINLEFT, NULL);
		
		SCROLLINFO info;
		
		scroller.GetScrollInfo(&info);
		info.nPage = 10;

		
		scroller.SetScrollInfo(&info,false);
		scroller.SetScrollRange(0, 1000);
		scroller.SetScrollPos(0,TRUE);


		tableView.Create(m_hWnd, rectExtension::ZXRectCreatWith(240, 50, 500, 500), NULL,  WS_CHILD | WS_VISIBLE, NULL, 0U, NULL);
		tableView.delegate = this;
		tableView.realoadData();
		
	}

	int numberOfLines() {
		return 10000;
	}
	int heightOfRow(int row) {
		return 50;
	}
	TableViewCell * cellOfRow(int row) {
		static int index = 0;

		TableViewCell * cell = tableView.findCellsFromCache("reuseId");
		if (cell == nullptr)
		{

			cell = new TableViewCell;
			cell->reuseId = "reuseId";
			CString text;
			text.Format("%d", index);
			cell->setCellId(text);
			index++;

		}
		CString text;
		text.Format("%d", row);
		cell->setText(text);
		return cell;
	}



	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar pScrollBar) {
	
		
		switch (nSBCode)
		{
		case SB_THUMBTRACK://ÍÏ¶¯»¬¿é
		
			OnLeftScrollerScrol(nPos);
			break;

		case SB_LINEUP:
			pos -= 1;
		
			break;
		case SB_LINEDOWN:
			pos += 1;
	
			break;
		case SB_PAGEUP:
			pos -= 10;

			break;
		case SB_PAGEDOWN:
			pos += 10;
	
			break;
		case SB_TOP:
			pos = 0;
	
			break;
		case SB_BOTTOM:
			pos = 1000;
		
			break;
		case SB_THUMBPOSITION:
		    pos = nPos;
		
		 	break;
		case SB_ENDSCROLL:
			scroller.SetScrollPos(pos);
			OnLeftScrollerScrol(pos);
			break;
		default:
			pos = scroller.GetScrollPos();
			break;
		}
	
		//scroller.SetScrollPos(pos);
		//std::cout << "cout test ";
		//printf("test print");
	    //scanf();
	}


	void OnLeftScrollerScrol(int posotion) {

		static	auto start = system_clock::now();


		auto end = system_clock::now();


		auto duration = duration_cast<microseconds>(end - start);

		if (double(duration.count()) * microseconds::period::num / microseconds::period::den > 0.05)
		{
			CRect contentRect;
			content.GetClientRect(contentRect);
			CRect windwoRect;
			GetClientRect(windwoRect);

			content.MoveWindow(rectExtension::ZXRectCreatWith(35, -(((float)contentRect.Height() - windwoRect.Height()) / 1000) * posotion, contentRect.Width(), contentRect.Height()));

			start = system_clock::now();
		}

	}

	void OnMouseMove(UINT nFlags, CPoint point) {
	//	if (isBtnMoveEnable)
		//{
		//	CRect contentRect;
		//	content.GetWindowRect(contentRect);
		//	content.MoveWindow(rectExtension::ZXRectCreatWith(point.x + 10, point.y + 10, contentRect.Width(), contentRect.Height()));

			//RedrawWindow();
			
		//}

	}
	void OnLButtonDown(UINT nFlags, CPoint point) {
		
		//if (point.x > mouseArea.left && point.x < mouseArea.right && point.y > mouseArea.top && point.y < mouseArea.bottom)
		//{
		//	isBtnMoveEnable = true;
		//}
	}

	void OnLButtonUp(UINT nFlags, CPoint point) {
	//	isBtnMoveEnable = false;

	}

	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	 
		pos = scroller.GetScrollPos() - (zDelta / abs(zDelta)) * 5;
		scroller.SetScrollPos(pos);
		OnLeftScrollerScrol(scroller.GetScrollPos());

		return true;
	}


	float scale;

	int pos;

	CScrollBar scroller;
	
	ContentView content;
	

	KeyBoardWindow keyboardWindow;

	TableView tableView;

};

