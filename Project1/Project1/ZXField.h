#pragma once
#include "stdafx.h"
class ZXField : public CWindowImpl<ZXField,CEdit>
{
public:
	CString currentText;
	
	BEGIN_MSG_MAP(ZXField)

		REFLECTED_COMMAND_CODE_HANDLER(EN_CHANGE, OnTextChange)
		REFLECTED_COMMAND_CODE_HANDLER(EN_UPDATE, OnTextWillChange)

		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnTextChange(UINT code, UINT id, HWND hCtrl, BOOL &bHandled) {
		
		
		CString strone;

		GetWindowText(strone);
	
		currentStr = strone;

		return 0;
	}
	LRESULT OnTextWillChange(UINT code, UINT id, HWND hCtrl, BOOL &bHandled) {


		CString willInputStr;

		GetWindowText(willInputStr);

		if (isOnlyAscIICharacters(willInputStr))
		{
			MessageBox("°üº¬·Ç·¨×Ö·û");
			if (!isOnlyAscIICharacters(currentStr))
			{
				SetWindowText(currentStr);
			}
			else
			{
				SetWindowText("");
			}
			
		}
		return 0;
	}

private:
	CString currentStr;

	BOOL isOnlyAscIICharacters(CString inputStr){
	
		int   lens;
		lens = strlen(inputStr);
		unsigned   char   ch;

		for (int i = 0; i < lens; i++) {
			ch = inputStr[i];
			if (ch > 0x7f) {
				return true;
			}

		}
		return false;
	}

};

