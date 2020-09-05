#pragma once
#include <iostream>

struct Line
{
    int _x1;
    int _y1;
    int _x2;
    int _y2;

    Line(int x1, int y1, int x2, int y2)
        : _x1(x1), _y1(y1), _x2(x2), _y2(y2)
    {
    }
    Line() = default;
};

struct DrawColor
{
    int _r;
    int _g;
    int _b;

    DrawColor(int r, int g, int b)
        : _r(r), _g(g), _b(b)
    {
    }

    DrawColor() = default;
};
