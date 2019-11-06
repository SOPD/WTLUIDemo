#pragma once
#include "stdafx.h"
#include <vector>


class KeyBoardWindow : public CWindowImpl<KeyBoardWindow, CWindow>
{
public:

	BEGIN_MSG_MAP(KeyBoardWindow)
	//	DEFAULT_REFLECTION_HANDLER()
		COMMAND_ID_HANDLER(ID_NUM_BTN, OnBtnClick)

		MSG_WM_CREATE(OnCreate)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_SIZE(OnSize)
	END_MSG_MAP()
	void OnPaint(CDCHandle) {
		

			CPaintDC cdc(m_hWnd);
		  HBRUSH br = CreateSolidBrush(RGB(0, 255, 0));

			CRect rc;
		GetClientRect(&rc);
		cdc.FillRect(&rc, br);
		

	
	}

	void OnSize(UINT nType, CSize size) {

		if (btns.size())
		{
			CRect windowRect;
			GetClientRect(windowRect);
			int w = windowRect.Width();
			int h = windowRect.Height() - 50;
		
			for (int i = 0; i < btns.size(); i++)
			{

				CButton *btn = btns[i];
				 
				btn->MoveWindow(rectExtension::ZXRectCreatWith((i % 3) * (w / 3), (i / 3) * (h / 4) + 50, w / 3, h / 4));
			
				//(btns[i])->MoveWindow(CRect(0, 0, 50,50), true);
			}
			editer.MoveWindow(rectExtension::ZXRectCreatWith(0, 0, w, 50));
		}
	
	
	}
	int OnCreate(LPCREATESTRUCT lpCreateStruct) {

		editer.Create(m_hWnd, rectExtension::ZXRectCreatWith(0, 0, 0, 0), "", WS_CHILD | WS_VISIBLE, NULL, 0U, NULL);
		 CFont *font = new CFont;
	
		font->CreatePointFont(300, _T(""));
		editer.SetFont(*font);
	

   
		


		std::vector<CString> list{ "1","2" ,"3" ,"4" ,"5" ,"6" ,"7" ,"8" ,"9" ,".","0" ,"<" };
		for (int i = 0; i < list.size(); i++)
		{
			CString title = list[i];
			
			CButton *btn1 = new CButton;
			btn1->Create(m_hWnd, rectExtension::ZXRectCreatWith(0, 0,0,50), title, WS_CHILD | WS_VISIBLE, NULL, ID_NUM_BTN, NULL);
			btns.push_back(btn1);
		}

		return 0;
	}


	LRESULT OnBtnClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{

		CButton btn = hWndCtl;
		CString btnStr;
		btn.GetWindowText(btnStr);
	
		if (btnStr == "<")
		{
			CString currentStr;

			editer.GetWindowText(currentStr);
			CString destStr = currentStr.Left(currentStr.GetLength() - 1);

			editer.SetWindowText(destStr);
		}
		else if (btnStr == ".")
		{
			CString currentStr;

			editer.GetWindowText(currentStr);
			if (currentStr.Find(".") == -1)
			{
				editer.AppendText(btnStr);
			}
		}else {
			if (btnStr != ".")
			{
				CString currentStr;

				editer.GetWindowText(currentStr);
				if (currentStr.Find(".") == -1)
				{
					if (currentStr.GetLength() > 7)
					{
						return 0;
					}
				}
				else
				{
					CString left;
					CString rigth;
					left = currentStr.Left(currentStr.Find("."));
					rigth = currentStr.Right(currentStr.GetLength() - currentStr.Find("."));
					if (left.GetLength() > 7 || rigth.GetLength() > 4)
					{
						return 0;
					}

				}
			}
			editer.AppendText(btnStr);
		}
		

		return 0;

	}

private:
	std::vector<CButton *> btns;

	CEdit editer;

};

