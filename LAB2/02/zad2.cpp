// zad2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

//podpunkt 1

#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
	fstream yt, zt, vt;

	float fs = 8000;
	float Ts = 1 / fs;
	float Tc = 1;

	int N = ceil(Tc / Ts);

	float *y = new float[N];
	float *z = new float[N];
	float *v = new float[N];
	float *x = new float[N];
	float *t = new float[N];

	float A = 1;
	float f = 1;
	float fi = 0;

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		x[i] = (sin(2 * M_PI * f * t[i] + cos(t[i] / 2))) / 2.07 + sin(3 * t[i] + fi);

		y[i] = (x[i] * t[i]) / (3 + cos(20 * M_PI*t[i]));

		z[i] = pow(t[i], 2)*abs(x[i] * y[i] - (2 / (10 + y[i])));

		v[i] = pow(z[i], 3) + 3 * sin(z[i] * y[i])*abs(y[i] - x[i]);

	}




	yt.open("yt.txt", ios::out | ios::app);
	if (yt.good() == true)
	{
		for (int i = 0; i < N; i++)
		{
			yt << t[i] << " ";
			yt << y[i] << endl;
		}
		yt.close();
	}

	zt.open("zt.txt", ios::out | ios::app);
	if (zt.good() == true)
	{
		for (int i = 0; i < N; i++)
		{
			zt << t[i] << " ";
			zt << z[i] << endl;
		}
		zt.close();
	}

	vt.open("vt.txt", ios::out | ios::app);
	if (vt.good() == true)
	{
		for (int i = 0; i < N; i++)
		{
			vt << t[i] << " ";
			vt << v[i] << endl;
		}
		vt.close();
	}


	system("PAUSE");
	return 0;
}


