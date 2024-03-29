// FFT.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <fftw3.h>

#define REAL 0
#define IMAG 1

#define N 8

using namespace std;

void fft(fftw_complex *in, fftw_complex *out)
{
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(plan);

	fftw_destroy_plan(plan);
	fftw_cleanup();
}

void displayComplex(fftw_complex *y)
{
	for (int i = 0; i < N; i++)
	{
		if (y[i][IMAG] < 0)
			cout << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << endl;
		else
			cout << y[i][REAL] << " + " << y[i][IMAG] << "i" << endl;
	}
}


void displayReal(fftw_complex *y)
{
	for (int i = 0; i < N; i++)
		cout << y[i][REAL] << endl;
}

int main()
{
	fftw_complex x[N];

	fftw_complex y[N];

	for (int i = 0; i < N; i++)
	{
		x[i][REAL] = i + 1;
		x[i][REAL] = 0;
	}

	fft(x, y);

	cout << "FFT =" << endl;
	displayComplex(y);


	system("PAUSE");
	return 0;
}


