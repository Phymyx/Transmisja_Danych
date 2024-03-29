// modulacja1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

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

float fs = 150000; //100 000
float Tc = 0.1;
float Ts = 1 / fs;

int N = ceil(Tc / Ts);

float fm = 100;
float fn = 500;
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


void ton_prosty(string nazwa)
{

	fstream zad;

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		m[i] = sin(2 * M_PI*fm*t[i]);
	}


	zad.open(nazwa, ios::out);
	if (zad.good() == true)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			zad << t[i] << " ";
			zad << m[i] << endl;
		}
		zad.close();
	}
	
}

void sygnal_mod_amp(string nazwa, float ka)
{
	fstream zad;

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		za[i] = (ka*(m[i] + 1))*cos(2 * M_PI*fn*t[i]);
	}

	zad.open(nazwa, ios::out);
	if (zad.good() == true)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			zad << t[i] << " ";
			zad << za[i] << endl;
		}
		zad.close();
	}

}

void mod_fazy(string nazwa, float kp)
{
	fstream zad;

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		zp[i] = cos(2 * M_PI*fn*t[i] + kp*m[i]);
	}

	zad.open(nazwa, ios::out);
	if (zad.good() == true)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			zad << t[i] << " ";
			zad << zp[i] << endl;
		}
		zad.close();
	}

}

void mod_czestotliwosc(string nazwa, float kf)
{
	fstream zad;

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;

		zf[i] = cos(2 * M_PI*fn*t[i] + ((kf/fm)*m[i]));
	}

	zad.open(nazwa, ios::out);
	if (zad.good() == true)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			zad << t[i] << " ";
			zad << zf[i] << endl;
		}
		zad.close();
	}

}

int main()
{

	ton_prosty("tonprosty.txt");

	//a

	sygnal_mod_amp("sygnalmodampa.txt", 0.5);
	mod_fazy("modfaza.txt", 0.5);
	mod_czestotliwosc("modcza.txt", 0.5);

	//b

	sygnal_mod_amp("sygnalmodampb.txt", 8);
	mod_fazy("modfazb.txt", 2);
	mod_czestotliwosc("modczb.txt", 2);

	//c

	sygnal_mod_amp("sygnalmodampc.txt", 30);
	mod_fazy("modfazc.txt", 10);
	mod_czestotliwosc("modczc.txt", 10);


	//system("PAUSE");
	return 0;
}
