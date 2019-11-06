#pragma once
#include "stdafx.h"
#include <fstream>
#include <iostream>
class rectExtension
{
public:

	static CRect ZXRectCreatWith(long x, long y, long witdh, long height)
	{
		CRect rc;
		rc.left = x;
		rc.top = y;
		rc.right = x + witdh;
		rc.bottom = y + height;
		return rc;
	}

};
class fileTool
{
public:
	static	CString readElementWithKey(CString key) {

		using namespace std;
		CString result = "´íÎó";
		ifstream fin("UserDefault.txt");
		const int LINE_LENGTH = 100;
		char str[LINE_LENGTH];

		while (fin.getline(str, LINE_LENGTH))
		{
			CString cstr = str;
			if (cstr.Left(3) == key)
			{
				return cstr.Right(strlen(cstr) - 4);
			}
		}
		return result;
	}
	

};