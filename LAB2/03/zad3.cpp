// zad3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

//podpunkt 12

#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
	fstream ut;

	float fs = 8000;
	float Ts = 1 / fs;
	float Tc = 1;

	int N = ceil(Tc / Ts);

	float *u = new float[2.5*N];
	float *t = new float[2.5*N];

	float A = 1;
	float f = 1;
	float fi = 0;

	for (int i = 0; i < (0.35*N); i++)
	{
		t[i] = i / fs;

		u[i] = cos(10 * pow(t[i], 2));

	}

	for (int i = (0.35*N); i < (0.6*N); i++)
	{
		t[i] = i / fs;

		u[i] = sin(4 * M_PI*pow(t[i], 2))*cos(8 * M_PI*pow(t[i], 2)) * 1 / t[i];

	}

	for (int i = (0.6*N); i < (1.1*N); i++)
	{
		t[i] = i / fs;

		u[i] = 0.92*pow(t[i], 2)*pow(-1, floor(25 * t[i]));

	}

	for (int i = (1.1*N); i < (1.8*N); i++)
	{
		t[i] = i / fs;

		u[i] = (0.6*pow(t[i], 2)) / (log2(t[i] + abs(cos(10 * t[i]))));

	}

	for (int i = (1.8*N); i < (2.5*N); i++)
	{
		t[i] = i / fs;

		u[i] = 10.5 - pow(t[i], 3);

	}




	ut.open("ut.txt", ios::out | ios::app);
	if (ut.good() == true)
	{
		for (int i = 0; i < (2.5*N); i++)
		{
			ut << t[i] << " ";
			ut << u[i] << endl;
		}
		ut.close();
	}


	system("PAUSE");
	return 0;
}


