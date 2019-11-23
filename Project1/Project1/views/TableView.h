#pragma once
#include "stdafx.h"
#include "TableViewDelegate.h"
#include "TableViewCell.h"
#include <vector>
#include <tuple>
#include "ZXTools.h"
#include <chrono>   

using namespace std;

using namespace chrono;
typedef CWinTraits<WS_CHILDWINDOW | WS_CLIPCHILDREN  , WS_EX_APPWINDOW > CTableViewTraits;
class TableView :public CWindowImpl<TableView,CWindow , CTableViewTraits>, public CDoubleBufferImpl<TableView>
{
public:
	
	BEGIN_MSG_MAP(TableView)
	MSG_WM_CREATE(OnCreate)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(CDoubleBufferImpl<TableView>)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_VSCROLL(OnVScroll)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
	END_MSG_MAP ()

	TableViewProtocol *delegate;

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

	void OnSize(UINT nType, CSize size) {
		CRect windowRect;
		GetClientRect(windowRect);
		scroller.MoveWindow(rectExtension::ZXRectCreatWith(0, 0, 30, windowRect.Height()));
	}

	int OnCreate(LPCREATESTRUCT lpCreateStruct) {
		offset = 0;
		scroller.Create(m_hWnd, rectExtension::ZXRectCreatWith(0, 0, 30, 500), NULL, SBS_VERT | WS_CHILD | WS_VISIBLE, NULL, ID_SCROLLER_MAINLEFT, NULL);

		SCROLLINFO info;

		scroller.GetScrollInfo(&info);
		info.nPage = 10;


		scroller.SetScrollInfo(&info, false);
		scroller.SetScrollRange(0, 1000);
		scroller.SetScrollPos(0, TRUE);
		return 0;

	}

	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar pScrollBar) {


		switch (nSBCode)
		{
		case SB_THUMBTRACK://ÍÏ¶¯»¬¿é

			break;

		case SB_LINEUP:
			if (pos <= 1000 && pos >= 0)
			{
				pos -= 1;
			}
			break;
		case SB_LINEDOWN:
			if (pos <= 1000 && pos >= 0)
			{
				pos += 1;
			}
			break;
		case SB_PAGEUP:
			if (pos <= 1000 && pos >= 0)
			{
				pos -= 10;
			}
			break;
		case SB_PAGEDOWN:
			if (pos <= 1000 && pos >= 0)
			{
				pos += 10;
			}
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
			if (pos <= 1000 && pos >= 0)
			{
				scroller.SetScrollPos(pos);

				OnLeftScrollerScrol(nPos);
			}
	     
			break;
		default:
			pos = scroller.GetScrollPos();
			break;
		}
	}

	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {

		pos = scroller.GetScrollPos() - (zDelta / abs(zDelta)) * 5;
		scroller.SetScrollPos(pos);
		OnLeftScrollerScrol(scroller.GetScrollPos());

		return true;
	}

	void OnLeftScrollerScrol(int posotion) {

		static	auto start = system_clock::now();


		auto end = system_clock::now();


		auto duration = duration_cast<microseconds>(end - start);

		if (double(duration.count()) * microseconds::period::num / microseconds::period::den > 0.05)
		{
			CRect windowRect;
			GetClientRect(windowRect);
			float unit = ((float)(cellMaps[cellMaps.size() - 1].location)  - windowRect.Height()) / 1000;
			loadDataWithOffset(pos * unit);
			start = system_clock::now();
		}

	}


	void realoadData();
	TableViewCell * findCellsFromCache(CString reuseId);
private:
	struct cellMap { int location;
	TableViewCell* cell;
	};
	
	void loadDataWithOffset(int offset);
	std::vector<TableViewCell *> unUsedCells;
	std::vector<TableViewCell *> allCells;
	std::vector<TableViewCell *> usedCells;
	std::vector<TableViewCell *> visiableCells;
	std::vector<int> cellLocations;
	std::vector<cellMap> cellMaps;
	int offset;
	int pos;
	CScrollBar scroller;
};
