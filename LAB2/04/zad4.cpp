// zad4.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

//podpunkt 12

#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <fstream>

using namespace std;

fstream bkt, bkt2, bkt3;

float fs = 22050;
float Ts = 1 / fs;
float Tc = 1;

int N = ceil(Tc / Ts);

float *bk = new float[N];
float *bk2 = new float[N];
float *bk3 = new float[N];
float *tabt = new float[N];


float A = 1;
float f = 1;
float fi = 0;

float p, p2, p3;
float t = 0;

int main()
{


	for (int i = 0; i < N; i++)
	{
		t = i / fs;

		//dla h1 = 2
		for (int h1 = 1; h1 <= 2; h1++)
		{
			p = p + (sin(2*M_PI*h1*t) + cos(2 * M_PI*h1*t)) / (2 * h1 + 4);
	
		}
		

		//dla h2 = 10

		for (int h2 = 1; h2 <= 10; h2++)
		{
			p2 = p2 + (sin(2 * M_PI*h2*t) + cos(2 * M_PI*h2*t)) / (2 * h2 + 4);

		}

		// dla h3 = 20

		for (int h3 = 1; h3 <= 20; h3++)
		{
			p3 = p3 + (sin(2 * M_PI*h3*t) + cos(2 * M_PI*h3*t)) / (2 * h3 + 4);

		}



		tabt[i] = t;
		bk[i] = (1 / pow(M_PI, 2))*p;
		bk2[i] = (1 / pow(M_PI, 2))*p2;
		bk3[i] = (1 / pow(M_PI, 2))*p3;

	}


	bkt.open("bkt1.txt", ios::out | ios::app);
	if (bkt.good() == true)
	{
		for (int i = 0; i < N; i++)
		{
			bkt << tabt[i] << " ";
			bkt << bk[i] << endl;
		}
		bkt.close();
	}


	bkt2.open("bkt2.txt", ios::out | ios::app);
	if (bkt2.good() == true)
	{
		for (int i = 0; i < N; i++)
		{
			bkt2 << tabt[i] << " ";
			bkt2 << bk2[i] << endl;
		}
		bkt2.close();
	}


	bkt3.open("bkt3.txt", ios::out | ios::app);
	if (bkt3.good() == true)
	{
		for (int i = 0; i < N; i++)
		{
			bkt3 << tabt[i] << " ";
			bkt3 << bk3[i] << endl;
		}
		bkt3.close();
	}


	//system("PAUSE");
	return 0;
}


