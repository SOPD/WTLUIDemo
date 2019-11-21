#pragma once
#include "stdafx.h"

class ContentView : public CWindowImpl<ContentView, CWindow>, public CDoubleBufferImpl<ContentView>
{
public:

	BEGIN_MSG_MAP(ContentView)
		DEFAULT_REFLECTION_HANDLER()
		CHAIN_MSG_MAP(CDoubleBufferImpl<ContentView>)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CREATE(OnCreate)

	END_MSG_MAP()

	int OnCreate(LPCREATESTRUCT lpCreateStruct){
	
	
		return 0;
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




};

