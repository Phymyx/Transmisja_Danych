// DFT.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <chrono>

using namespace std;

float A = 1;
float f = 1;
//float f = 400;
float fi = 0;

float Tc = 1;
float fs = 8000;
float Ts = 1 / fs;

int N = ceil(Tc / Ts);

float fs2 = 22050;
float Ts2 = 1 / fs2;

int G = ceil(Tc / Ts2);

float *u = new float[N];
float *y = new float[N];
float *z = new float[N];
float *v = new float[N];
float *x = new float[N];
float *t = new float[N];

float *bk = new float[G];
float *bk2 = new float[G];
float *bk3 = new float[G];
float *tabt = new float[G];

float p, p2, p3;
float tt = 0;

float *tablica_r = new float[N];
float *tablica_u = new float[N];

float *tablica_mk = new float[N];
float *tablica_mk1 = new float[N];
float *tablica_fk = new float[N];

float *tablica_mkG = new float[G];
float *tablica_mk1G = new float[G];
float *tablica_fkG = new float[G];


void DFT(float *tablica, string nazwa, int N, float fs_wybor)
{
	fstream zad;

	for (int k = 0; k <= N - 1; k++)
	{
		tablica_r[k] = 0;
		tablica_u[k] = 0;
		for (int n = 0; n <= N - 1; n++)
		{
			tablica_r[k] += tablica[n] * cos(-(2 * (M_PI * k * n) / N));
			tablica_u[k] += tablica[n] * sin(-(2 * (M_PI * k * n) / N));
		}
	}
	if (fs_wybor == fs)
	{
		for (int k = 0; k <= N - 1; k++)
		{
			tablica_mk[k] = sqrt(pow(tablica_r[k], 2) + pow(tablica_u[k], 2));
			//tablica_mk[k] = tablica_mk[k] * 2 / N;
		}

		for (int k = 0; k <= N - 1; k++)
		{
			tablica_mk1[k] = 10 * log10(tablica_mk[k]);
			tablica_fk[k] = k * (fs_wybor / N);
		}
	}
	if (fs_wybor == fs2)
	{
		for (int k = 0; k <= N - 1; k++)
		{
			tablica_mkG[k] = sqrt(pow(tablica_r[k], 2) + pow(tablica_u[k], 2));
			//tablica_mk[k] = tablica_mk[k] * 2 / N;
		}

		for (int k = 0; k <= N - 1; k++)
		{
			tablica_mk1G[k] = 10 * log10(tablica_mkG[k]);
			tablica_fkG[k] = k * (fs_wybor / N);
		}
	}


	/*
	zad.open(nazwa, ios::out);
	if (zad.good() == true)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			zad << tablica_fk[i] << " ";
			zad << tablica_mk1[i] << endl;
		}
		zad.close();
	}
	*/
}

int main()
{
	
	for (int i = 0; i < N; i++)
	{

		t[i] = i / fs;

		x[i] = (sin(2 * M_PI * f * t[i] + cos(t[i] / 2))) / 2.07 + sin(3 * t[i] + fi);

		y[i] = (x[i] * t[i]) / (3 + cos(20 * M_PI*t[i]));

		z[i] = pow(t[i], 2)*abs(x[i] * y[i] - (2 / (10 + y[i])));

		v[i] = pow(z[i], 3) + 3 * sin(z[i] * y[i])*abs(y[i] - x[i]);
	}

	
	for (int i = 0; i < (0.14*N); i++)
	{
		t[i] = i / fs;

		u[i] = cos(10 * pow(t[i], 2));

	}

	for (int i = (0.14*N); i < (0.24*N); i++)
	{
		t[i] = i / fs;

		u[i] = sin(4 * M_PI*pow(t[i], 2))*cos(8 * M_PI*pow(t[i], 2)) * 1 / t[i];

	}

	for (int i = (0.24*N); i < (0.44*N); i++)
	{
		t[i] = i / fs;

		u[i] = 0.92*pow(t[i], 2)*pow(-1, floor(25 * t[i]));

	}

	for (int i = (0.44*N); i < (0.72*N); i++)
	{
		t[i] = i / fs;

		u[i] = (0.6*pow(t[i], 2)) / (log2(t[i] + abs(cos(10 * t[i]))));

	}

	for (int i = (0.72*N); i < (1*N); i++)
	{
		t[i] = i / fs;

		u[i] = 10.5 - pow(t[i], 3);

	}

	
	for (int i = 0; i < G; i++)
	{
		tt = i / fs2;

		//dla h1 = 2
		for (int h1 = 1; h1 <= 2; h1++)
		{
			p = p + (sin(2 * M_PI*h1*tt) + cos(2 * M_PI*h1*tt)) / (2 * h1 + 4);

		}


		//dla h2 = 10

		for (int h2 = 1; h2 <= 10; h2++)
		{
			p2 = p2 + (sin(2 * M_PI*h2*tt) + cos(2 * M_PI*h2*tt)) / (2 * h2 + 4);

		}

		// dla h3 = 20

		for (int h3 = 1; h3 <= 20; h3++)
		{
			p3 = p3 + (sin(2 * M_PI*h3*tt) + cos(2 * M_PI*h3*tt)) / (2 * h3 + 4);

		}



		tabt[i] = tt;
		bk[i] = (1 / pow(M_PI, 2))*p;
		bk2[i] = (1 / pow(M_PI, 2))*p2;
		bk3[i] = (1 / pow(M_PI, 2))*p3;

	}

	using namespace std::chrono;

	auto start = high_resolution_clock::now();
	
	auto start1 = high_resolution_clock::now();
	DFT(x, "xxdft.txt", N, fs);
	auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "dft_x: " << duration1.count() << " microseconds" << endl;


	auto start2 = high_resolution_clock::now();
	DFT(y, "yydft.txt", N, fs);
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	cout << "dft_y: " << duration2.count() << " microseconds" << endl;


	auto start3 = high_resolution_clock::now();
	DFT(z, "zzdft.txt", N, fs);
	auto stop3 = high_resolution_clock::now();
	auto duration3 = duration_cast<microseconds>(stop3 - start3);
	cout << "dft_z: " << duration3.count() << " microseconds" << endl;


	auto start4 = high_resolution_clock::now();
	DFT(v, "vvdft.txt", N, fs);
	auto stop4 = high_resolution_clock::now();
	auto duration4 = duration_cast<microseconds>(stop4 - start4);
	cout << "dft_v: " << duration4.count() << " microseconds" << endl;


	auto start5 = high_resolution_clock::now();
	DFT(u, "uudft.txt", N, fs);
	auto stop5 = high_resolution_clock::now();
	auto duration5 = duration_cast<microseconds>(stop5 - start5);
	cout << "dft_u: " << duration5.count() << " microseconds" << endl;


	auto start6 = high_resolution_clock::now();
	DFT(bk, "bkdft.txt", G, fs2);	
	auto stop6 = high_resolution_clock::now();
	auto duration6 = duration_cast<microseconds>(stop6 - start6);
	cout << "dft_bk: " << duration6.count() << " microseconds" << endl;


	auto start7 = high_resolution_clock::now();
	DFT(bk2, "bk2dft.txt", G, fs2);
	auto stop7 = high_resolution_clock::now();
	auto duration7 = duration_cast<microseconds>(stop7 - start7);
	cout << "dft_bk2: " << duration7.count() << " microseconds" << endl;


	auto start8 = high_resolution_clock::now();
	DFT(bk3, "bk3dft.txt", G, fs2);
	auto stop8 = high_resolution_clock::now();
	auto duration8 = duration_cast<microseconds>(stop8 - start8);
	cout << "dft_bk3: " << duration8.count() << " microseconds" << endl;


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "czas calosci: " << duration.count() << " microseconds" << endl;

	system("PAUSE");
	return 0;
}


