#include <windowsx.h>
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>


#define WM_SYSICON          (WM_USER + 1)
using namespace std;

class Quote {
	Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR						gdiplusToken;
	Gdiplus::Graphics*				runGraphics;
	HWND							AppHandle;
	struct pack {
		wstring stt;
		wstring text;
		wstring author;
	};
	int nPack;
	vector<pack>data;
	vector<int>ran;
public:
	Quote();
	~Quote();
	void GDIP_Init();
	void SetAppHandle(HWND handle);
	void ReadFile();
	void Random();
	void SetbackgroundImage(int i);
	void GetTextQuote(int i);
	void GetTextAuthor(int i);
	void MadeBy();
	int GetPlace(int i);
	wstring GetText(int i);
	int GetNumPack();

};