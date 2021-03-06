// MandelBrot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "olcGameEngine.h"
#include <complex>

class Mandelbrot : public olcConsoleGameEngine
{
public:
	Mandelbrot()
	{ }
	virtual bool OnUserCreate()
	{
		SetCursorVisible(false);
		return true;
	}

	bool mandelbrot(std::complex<double> c)
	{
		std::complex<double> z = c;
		for (int i = 0; i < quality; i++)
		{
			z = (z * z) + c;
		}
		if (abs(z) > 0.001) { return true;  }
		return false;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		//Fill(0, 0, 160, 100, PIXEL_SOLID, FG_BLACK);
		if (quality < 30)
		{
			for (double x = 0; x < 160 * 4; x++)
			{
				for (double y = 0; y < 100 * 4; y++)
				{
					double xpos = (x / zoom) - x_move, ypos = (y / zoom) - y_move;
					std::complex<double> cnum(xpos, ypos);
					bool out = mandelbrot(cnum);
					if (out)
					{
						Draw(x, y, PIXEL_SOLID, colours[quality % 4]);
					}
				}
			}
			quality += 1;
		}
		return true;
	}

	double x_move = 2, y_move = 1;
	double zoom = 50 * 4;
	int quality = 8;

	int colours[256] = {
		12,
		9,
		10,
		15
	};
};

int main()
{
	Mandelbrot fractal;
	fractal.ConstructConsole(160 * 4, 100 * 4, 2, 2);
	fractal.Start();
    return 0;
}

