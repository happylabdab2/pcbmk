#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <cmath>
// #include <fmt/base.h>

using namespace std;

class LibSVG
{
public:
    void addCircle(int radius, int x, int y, string fill = "orange") // Draw a graphic
    {
        file.append(format(R"(<circle cx="{}" cy="{}" r="{}" fill="{}}">)", x, y, radius, fill));
    }

    // linear interpolation mode
    void LinearInterpolation(bool boolean) // Set Linear Interpolation
    {
        isLinearInterpolation = boolean;
    }

    void setFormatSpecification(int x, int y) // Initial specification
    {
        xInt = x / 10;
        xDecimal = x % 10;
        yInt = x / 10;
        yDecimal = x % 10;
    }

    // impalment 4.3 Aperture Definition (AD)
    void setApertureDefinition(int id, char shape, double paramShape, tuple<> param) // 
    {
        apertureID[id] = {shape, paramShape, param};
    };

    void D02(double x = NAN, double y = NAN) // Move without drawing
    {
        if (x == NAN || y == NAN)
        {
            return;
        }
        xPos = x;
        yPos = y;
    }

    void D01(double x = NAN, double y = NAN) // draws a line
    {
        if (x == NAN || y == NAN)
        {
            x = xPos;
            y = yPos;
        }

        if (isLinearInterpolation) // line mode
        {
            file.append(format(R"(<line x1="{}" y1="{}" x2="{}" y2="{}" stroke="black" stroke-width="{}" />)", xPos, yPos, x, y, StrokeWidth));
        }
    }

    void D01(double x = NAN, double y = NAN, int x_offset, int y_offset) // draws an arc
    {
        if (x == NAN || y == NAN)
        {
            x = xPos;
            y = yPos;
        }

        if (!isLinearInterpolation) // arc mode
        {
            file.append(format(R"(<ellipse cx="{}" cy="{}" rx="{}" ry="{}" fill="{}}">)", xPos, yPos, x, y, StrokeWidth));
        }
    }

    void D03(double x, double y) // Places current shape (Aperture) - flash operation
    {
    }

    void G02()
    {
        isCircularInterpolationClockwise = true;
    }

    void G02()
    {
        isCircularInterpolationClockwise = false;
    }

    void G75() // dev note: idc, This command must be issued before the first circular interpolation operation, for compatibility with older Gerber versions
    {
    }

private:
    string file;
    double xPos = 0;
    double yPos = 0;

    double StrokeWidth = 2;

    int xDecimal = 1;
    int xInt = 1;
    int yDecimal = 1;
    int yInt = 1;

    std::map<int, tuple<char, double, tuple<>>> apertureID;

    bool isLinearInterpolation = true;

    bool isCircularInterpolation = false;
    bool isCircularInterpolationClockwise = true;
};