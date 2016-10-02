

#include "Quote.h"


//constructor
Quote::Quote() {
	nPack = 0;
	runGraphics = NULL;
}

//destructor
Quote::~Quote() {
	delete runGraphics;
}
//init gdi to draw
void Quote::GDIP_Init()
{
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	runGraphics = new Gdiplus::Graphics(GetDC(AppHandle));
}
//set handle
void Quote::SetAppHandle(HWND handle)
{
	AppHandle = handle;
}

void Quote::SetbackgroundImage(int i) {
	Gdiplus::Bitmap* bitmap;
	//load picture map
	if(i==1)
		bitmap = Gdiplus::Bitmap::FromFile(L".\\DataImage\\1.jpg", false);
	else if(i==2)
		bitmap = Gdiplus::Bitmap::FromFile(L".\\DataImage\\2.jpg", false);
	else
		bitmap = Gdiplus::Bitmap::FromFile(L".\\DataImage\\3.jpg", false);
	runGraphics->DrawImage(bitmap, 0, 0, 850, 401);

	MadeBy();
}

void Quote::GetTextQuote(int i) {
	Gdiplus::SolidBrush  brush4(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::FontFamily  fontFamily(L"Lucida Calligraphy");
	Gdiplus::Font        font(&fontFamily, 35, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::PointF      pointF(60.0f, 25.0f);
	runGraphics->DrawString(data[ran[i]].text.c_str(), -1, &font, pointF, &brush4);
}
void Quote::GetTextAuthor(int i) {

	Gdiplus::SolidBrush  brush4(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::FontFamily  fontFamily(L"Blackadder ITC");
	Gdiplus::Font        font(&fontFamily, 35, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::PointF      pointF(455.0f, 300.0f);
	runGraphics->DrawString(data[ran[i]].author.c_str(), -1, &font, pointF, &brush4);
}
void Quote::MadeBy() {
	//set background title
	Gdiplus::SolidBrush  brushRe(Gdiplus::Color(255, 41, 128, 185));
	runGraphics->FillRectangle(&brushRe, 0, 400, 682, 41);

	Gdiplus::FontFamily  fontFamily(L"Segoe UI");

	//title id name
	Gdiplus::SolidBrush  brushID(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::Font        fontId(&fontFamily, 21, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::PointF      pointId(0.0, 409.0f);
	runGraphics->DrawString(L" Made by: Trần Hoàng Lâm - ID: 1412280", -1, &fontId, pointId, &brushID);
}

void Quote::ReadFile() {
	wfstream input("DataBase.txt", ios::in);
	int i = 0;
	if (!input.is_open())return;
	int k = 0;
	//read file and get data
	while (!input.eof()) {
		pack tmp;
		getline(input, tmp.stt, L'\t');
		getline(input, tmp.text, L'\t');
		int loop = tmp.text.size() / 30;
		int count = 0;
		int block = 30;
		while (count++ < loop) {
			while ((block + k) != tmp.text.size()) {
				if (tmp.text.at(block + k) == L' ') {
					tmp.text.insert(block + k, L"\n");
					k = 0;

					break;
				}
				k++;
			};
			block += 30;
		}
		getline(input, tmp.author, L'\n');
		data.push_back(tmp);
	}
	nPack = data.size();
	input.close();

}
int timx(vector<int> a, int x)// co gia tri x trong mang a do dai n hay ko 
{
	int i;
	if (a.size() == 0)return 0;
	for (i = 0; i<a.size(); ++i)
		if (a[i] == x)return 1;
	return 0;
}

void Quote::Random() {
	int i, x;
	srand(time(0));
	x = rand() % nPack;
	for (i = 0; i<nPack; ++i)
	{
		while (timx(ran, x)) {
			x = rand() % nPack;
		}
		ran.push_back(x);
	}
}

wstring Quote::GetText(int i) {
	return data[i].text;
}
int Quote::GetPlace(int i) {
	return ran[i];
}
int Quote::GetNumPack() {
	return nPack;
}