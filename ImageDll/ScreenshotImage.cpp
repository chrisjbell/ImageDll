#include "stdafx.h"
#include "ScreenshotImage.h"

#include "GdiplusInit.h"


ScreenshotImage::ScreenshotImage()
{
}


ScreenshotImage::~ScreenshotImage()
{
	//if (pBitmap) delete pBitmap;
}


int ScreenshotImage::TakeScreenshot()
{
	GdiplusInit gpi;

	HDC scrdc, memdc;
	HBITMAP membit;
	scrdc = ::GetDC(0);
	int Height = GetSystemMetrics(SM_CYSCREEN);
	int Width = GetSystemMetrics(SM_CXSCREEN);
	memdc = CreateCompatibleDC(scrdc);
	membit = CreateCompatibleBitmap(scrdc, Width, Height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
	BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

	pBitmap = new Bitmap(membit, NULL);

	SaveScreenshot("output2.bmp");

	SelectObject(memdc, hOldBitmap);
	DeleteObject(memdc);
	DeleteObject(membit);
	::ReleaseDC(0, scrdc);

	return 1;
}

HBITMAP ScreenshotImage::GetHBITMAP() 
{
		HBITMAP hbmp = NULL;
		Status s =  pBitmap->GetHBITMAP(Color::Transparent, &hbmp);

		return hbmp;
}

//Bitmap* ScreenshotImage::AsBitmap()
//{
//	// TODO: Add your implementation code here.
//	return nullptr;
//}

bool ScreenshotImage::SaveScreenshot(std::string filename)
{
	if (pBitmap != nullptr)
	{
		CLSID pngClsid;
		GetEncoderClsid(L"image/png", &pngClsid);

		filename = (filename.find(".BMP") || filename.find(".bmp")) ?
			filename : filename + ".bmp";
		std::wstring w = s2ws(filename);
		pBitmap->Save(w.c_str(), &pngClsid, NULL);
		return true;
	}

	return false;
}


int ScreenshotImage::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}


std::wstring ScreenshotImage::s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}