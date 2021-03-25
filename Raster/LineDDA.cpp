#include "pch.h"
#include "LineDDA.h"
#include<windows.h>


void LineDDA::LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
	pDC->SetPixel(x1, y1, color);
	int x = x1;
	int y = y1;
	float m = 1.0 * (y2 - y1) / (y2 - y1);
	while (x < x2) {
		x += 1;
		y += m;
		y = round(y);
		pDC->SetPixel(x, y, color);
	}
}

void LineDDA::LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
	pDC->SetPixel(x1, y1, color);
	int x = x1;
	int y = y1;
	float k = 1.0 * (x2 - x1) / (y2 - y1);
	while (y < y2) {
		y += 1;
		x += k;
		x = round(x);
		pDC->SetPixel(x, y, color);
	}
}

void LineDDA::DDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
	pDC->SetPixel(x1, y1, color);
	float x = x1;
	float y = y1;
	float dx = x2 - x1;
	float dy = y2 - y1;
	float steps = abs(dx) < abs(dy) ? abs(dy) : abs(dx);
	float m = 1.0 * dy / steps;
	float k = 1.0 * dx / steps;
	for (int i = 0; i <= steps; i++)
	{
		y += m;
		x += k;
		//y = round(y);
		//x = round(x);
		pDC->SetPixel(int(x + 0.5), int(y + 0.5), color);
	}
}