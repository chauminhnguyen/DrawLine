#pragma once
class LineDDA
{
public:
	static void LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void DDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
};

