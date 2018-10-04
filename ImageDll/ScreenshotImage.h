#pragma once
#include <string>

class ScreenshotImage 
{
private:
	Bitmap* pBitmap = nullptr;
	RectF rect;

	//GdiplusStartupInput gdiplusStartupInput;
	//ULONG_PTR gdiplusToken;

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	std::wstring s2ws(const std::string& str);

public:
	ScreenshotImage();
	~ScreenshotImage();
	int TakeScreenshot();
	Bitmap* AsBitmap() { return pBitmap == nullptr ? nullptr : pBitmap; }
	RectF* GetScreenRect() { return &rect; }

	HBITMAP GetHBITMAP();

	bool SaveScreenshot(std::string filename);
};

