#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//czas 1/10
//100hz
//czestotliwosc sgnalu nosnego 1000
//probkowanie 100 000

float fs = 150000; //150 000
float Tc = 0.1; //0.1
float Ts = 1 / fs;

int N = ceil(Tc / Ts);

float fm = 100;//100
float fn = 500;//500
/*
float ka = 1;
float kp = 1;
float kf = 150;
*/
float *t = new float[N];
float *m = new float[N];
float *za = new float[N];
float *zp = new float[N];
float *zf = new float[N];

float *tablica_r = new float[N];
float *tablica_u = new float[N];

float *tablica_mk = new float[N];
float *tablica_mk1 = new float[N];
float *tablica_fk = new float[N];

float *sygnal_mod_ampa = new float[N];
float *mod_fazya = new float[N];
float *mod_czestotliwosca = new float[N];

float *sygnal_mod_ampb = new float[N];
float *mod_fazyb = new float[N];
float *mod_czestotliwoscb = new float[N];

float *sygnal_mod_ampc = new float[N];
float *mod_fazyc = new float[N];
float *mod_czestotliwoscc = new float[N];


void DFT(float *tablica, string nazwa, int N)
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

	for (int k = 0; k <= N - 1; k++)
	{
		tablica_mk[k] = sqrt(pow(tablica_r[k], 2) + pow(tablica_u[k], 2));
		//tablica_mk[k] = tablica_mk[k] * 2 / N;
	}

	for (int k = 0; k <= N - 1; k++)
	{
		tablica_mk1[k] = 10 * log10(tablica_mk[k]);
		tablica_fk[k] = k * (fs / N);
	}



	
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
	
}


void ton_prosty(string nazwa)
{

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		m[i] = sin(2 * M_PI*fm*t[i]);
	}

}

float * sygnal_mod_amp(string nazwa, float ka)
{

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		za[i] = (ka*(m[i] + 1))*cos(2 * M_PI*fn*t[i]);
	}

	return za;

}

float * mod_fazy(string nazwa, float kp)
{

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		zp[i] = cos(2 * M_PI*fn*t[i] + kp * m[i]);
	}

	return zp;

}

float * mod_czestotliwosc(string nazwa, float kf)
{

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		zf[i] = cos(2 * M_PI*fn*t[i] + ((kf / fm)*m[i]));
	}

	return zf;

}

void minmax(float* band, int n)
{
	float max = band[0];
	float min = band[0];

	for (int i = 1; i < n; i++)
	{
		if (band[i] < min)
		{
			min = band[i];
		}
		if (band[i] > max)
		{
			max = band[i];
		}
	}
	float szerokosc = max - min;
	cout << szerokosc << endl;
}

int main()
{

	ton_prosty("tonprosty.txt");

	//a

	sygnal_mod_ampa = sygnal_mod_amp("sygnalmodamps.txt", 0.5);//0.5
	mod_fazya = mod_fazy("modfaza.txt", 0.5);
	mod_czestotliwosca = mod_czestotliwosc("modcza.txt", 0.5);
	//DFT(sygnal_mod_ampa, "DFTmodampa.txt", N);
	//DFT(mod_fazya, "DFTmodfaza.txt", N);
	//DFT(mod_czestotliwosca, "DFTmodcza.txt", N);

	minmax(sygnal_mod_ampa, N);//1.95191
	minmax(mod_fazya, N);//2
	minmax(mod_czestotliwosca, N);//2

	//b
	
	sygnal_mod_ampb = sygnal_mod_amp("sygnalmodampb.txt", 8);
	mod_fazyb = mod_fazy("modfazb.txt", 2);
	mod_czestotliwoscb = mod_czestotliwosc("modczb.txt", 2);
	//DFT(sygnal_mod_ampb, "DFTmodampb.txt", N);
	//DFT(mod_fazyb, "DFTmodfazb.txt", N);
	//DFT(mod_czestotliwoscb, "DFTmodczb.txt", N);

	minmax(sygnal_mod_ampb, N);//31.2306
	minmax(mod_fazyb, N);//2
	minmax(mod_czestotliwoscb, N);//2

	//c

	sygnal_mod_ampc = sygnal_mod_amp("sygnalmodampc.txt", 30);
	mod_fazyc = mod_fazy("modfazc.txt", 10);
	mod_czestotliwoscc = mod_czestotliwosc("modczc.txt", 10);
	//DFT(sygnal_mod_ampc, "DFTmodampc.txt", N);
	//DFT(mod_fazyc, "DFTmodfazc.txt", N);
	//DFT(mod_czestotliwoscc, "DFTmodczc.txt", N);
	
	minmax(sygnal_mod_ampc, N);//117.115
	minmax(mod_fazyc, N);//2
	minmax(mod_czestotliwoscc, N);//2





	system("PAUSE");
	return 0;
}
