#pragma once
#include "stdafx.h"
#include "ZXField.h"
#include "ZXTools.h"
#include "TestView.h"

class AboutDialog : public  CDialogImpl<AboutDialog>{
public:
	TestView test;
	
	enum 
	{
		IDD = IDD_FIRSTDIALOG
	};
	BEGIN_MSG_MAP(AboutDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_PAINT(OnPaint)
		COMMAND_ID_HANDLER(IDCANCEL,OnCancle)
		COMMAND_ID_HANDLER(IDOK,OnOK )
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam) {
	
		
		
	    fieldAccount.Create(m_hWnd, rectExtension::ZXRectCreatWith(100,20,100,20), _T("admin"), 0, 0, 0U, NULL);

		fieldPWD.Create(m_hWnd, rectExtension::ZXRectCreatWith(100, 80, 100, 20), _T("123456"), 0, 0, 0U, NULL);
		fieldPWD.SetPasswordChar('*');

		return true;
	}



	void OnPaint(CDCHandle dc) {

		CPaintDC cdc(m_hWnd);

		CString acc;
		acc = "账号：";
		CString pwd;
		pwd = "密码：";
		cdc.SetTextColor(RGB(0, 0, 0));

		cdc.ExtTextOut(20, 20, ETO_OPAQUE, rectExtension::ZXRectCreatWith(20, 20, 50, 20), acc,

			acc.GetLength(), NULL);

		cdc.SetTextColor(RGB(0, 0, 0));

		cdc.ExtTextOut(20, 80, ETO_OPAQUE, rectExtension::ZXRectCreatWith(20, 80, 50, 20), pwd,

			pwd.GetLength(), NULL);




	}
	LRESULT OnCancle(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{

		EndDialog(wID);
		return 0;

	}
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		
	

		// 然后可以使用 ifstream file; 这样声明一个文件输入对象
		CString acc;
		fieldAccount.GetWindowText(acc);
		CString pwd;
		fieldPWD.GetWindowText(pwd);
		if (strlen(acc) < 4 || strlen(pwd) < 6)
		{
			MessageBox("账号或密码格式不对");
			return 0;
		}


		if (fileTool::readElementWithKey("ACC") != acc)
		{
			MessageBox("账号错误");
		}else if (fileTool::readElementWithKey("PWD") != pwd)
		{
			MessageBox("密码错误");
		}
		else {
			EndDialog(wID);
			if (NULL == test.Create(NULL, CWindow::rcDefault,
				_T("My First ATL Window"),WS_CLIPCHILDREN))
				return 1;       // Window creation failed

			

			test.ShowWindow(1);
			test.UpdateWindow();

		}

		
		return 0;

	}

	CButton btn;
	ZXField fieldPWD;
	ZXField fieldAccount;


};

