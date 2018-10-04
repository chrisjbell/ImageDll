// ImageDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ScreenshotImage.h"
#include "ImageDll.h"

#include <iostream>


char* WINAPI LoadScreenshot(HBITMAP* bmp)
{
	std::cout << "we are here now " << std::endl;
	ScreenshotImage si;
	if (si.TakeScreenshot())
	{
		std::cout << " now we got shot!" << std::endl;
		//RectF* r = si.GetScreenRect()->Clone();

		//HBITMAP hbmp = NULL;
		//std::cout << "we got a rect " << r->GetTop() << ", " << r->GetLeft() << ", " << r->GetBottom() << ", " << r->GetRight() << std::endl;
		//si.AsBitmap()->GetHBITMAP(Color::Transparent, &hbmp);     //si.AsBitmap()->GetHBITMAP(0, &bmp); // ->Clone(*r, PixelFormatDontCare);
		*bmp = si.GetHBITMAP();
		std::cout << " hbitmap is " << (void *)bmp << std::endl;
		return (char*)"2";
	}

	return (char*)"3";
}


