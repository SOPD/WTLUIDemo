// main.cpp:
#include "stdafx.h"
#include "AboutDialog.h"
CAppModule _Module;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	_Module.Init(NULL, hInstance);



	MSG msg;

	// Create the main window

		// Show the window

	
   AboutDialog dlg;
   
   dlg.DoModal();
     

	// Standard Win32 message loop

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		
		DispatchMessage(&msg);
	}

	_Module.Term();
	return msg.wParam;
}
