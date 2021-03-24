#include "pch.h"
#include "Bresenham.h"

void Bresenham::LineBresenham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color) {
    int x, y, Dx, Dy, p;
    Dx = abs(x2 - x1);
    Dy = abs(y2 - y1);
    x = x1;
    y = y1;

    int x_unit = 1, y_unit = 1;

    if (x2 - x1 < 0)
        x_unit = -x_unit;
    if (y2 - y1 < 0)
        y_unit = -y_unit;

    if (x1 == x2)  
    {
        while (y != y2 + 1)
        {
            y += y_unit;
            pDC->SetPixel(x, y, color);
        }
    }

    else if (y1 == y2)  
    {
        while (x != x2 + 1)
        {
            x += x_unit;
            pDC->SetPixel(x, y, color);
        }
    }
    
    else {
        if (Dy < Dx) {
            p = 2 * Dy - Dx;
            pDC->SetPixel(x, y, color);
            while (x != x2) {
                if (p < 0) p += 2 * Dy;
                else {
                    p += 2 * (Dy - Dx);
                    y += y_unit;
                }
                x += x_unit;
                pDC->SetPixel(x, y, color);
            }
        }
        else {
            p = 2 * Dx - Dy;
            pDC->SetPixel(x, y, color);
            while (y != y2) {
                if (p < 0) p += 2 * Dx;
                else {
                    p += 2 * (Dx - Dy);
                    x += x_unit;
                }
                y += y_unit;
                pDC->SetPixel(x, y, color);
            }
        }
    }
}
