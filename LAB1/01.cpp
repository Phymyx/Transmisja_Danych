// 01.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
	fstream zad01;

	float fs = 100;
	float Ts = 1 / fs;
	float Tc = 1;

	int N = ceil(Tc / Ts);

	float *s = new float[N];
	float *t = new float[N];

	float A = 1;
	float f = 1;
	float fi = 0;

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		s[i] = A * sin(2 * M_PI * f * t[i] + fi);
	}

	zad01.open("01.txt", ios::out | ios::app);
	if (zad01.good() == true)
	{
		for (int i = 0; i < N; i++)
		{
			zad01 << t[i] << " ";
			zad01 << s[i] << endl;
		}
		zad01.close();
	}


	system("PAUSE");
	return 0;
}


