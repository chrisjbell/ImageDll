#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <iostream>

using namespace Gdiplus;
using std::runtime_error;

struct GdiplusInit
{
	GdiplusInit()
	{
		GdiplusStartupInput inp;
		GdiplusStartupOutput outp;
		if (Ok != GdiplusStartup(&token_, &inp, &outp))
			throw runtime_error("GdiplusStartup");
	}
	~GdiplusInit()
	{
		GdiplusShutdown(token_);
	}
private:
	ULONG_PTR token_;
};
