#pragma once
#include "stdafx.h"
#include "ZXTools.h"
#include "ViewLayoutExtension.h"
class TableViewCell :public CWindowImpl<TableViewCell, CWindow>, public CDoubleBufferImpl<TableViewCell>
{
public:
	BEGIN_MSG_MAP(TableViewCell)
		MSG_WM_PAINT(OnPaint)
		CHAIN_MSG_MAP(CDoubleBufferImpl<TableViewCell>)
	END_MSG_MAP()
	CString text = "";
	CString cellId = "";
	CString reuseId = "";

	void OnPaint(CDCHandle)
	{
	
	
		CPaintDC dc(m_hWnd);
		DoPaint(dc.m_hDC);

	}

	void DoPaint(CDCHandle  cdc) {

		HBRUSH br = CreateSolidBrush(RGB(0, 255, 255));
		CRect rc;
		GetClientRect(&rc);
		cdc.FillRect(&rc, br);
		CString text;
		text.Format("cell resueId %s Line %s Line cellIndex %s", reuseId, this->text,this->cellId);
		cdc.SetTextColor(RGB(0, 0, 0));
		cdc.ExtTextOut(10, 10, ETO_OPAQUE, rectExtension::ZXRectCreatWith(10, 10, rc.Width() - 20, rc.Height() - 20), text,
			text.GetLength(), NULL);
	}
	void setText(CString text) {
		this->text = text;
	}
	void setCellId(CString text) {

		this->cellId = text;

	}
};