#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>
#define N 20     // data 
#define M 0.5   // error

using namespace std;

// coordinate
float datax[N] = {};
float datay[N] = {};


float dis(float x, float y, float a, float b) {
	
	return abs(a * x - y + b) / sqrt(a * a + 1);
	
}

float f(float a, float b) {
	
	float sum = 0.0;
	
	for (int i = 0; i < N; i++) {
		sum += dis(datax[i], datay[i], a, b) / N;
	}
	
	return sum;
	
}

float dfabda(float a, float b, float da) {
	
	return (f(a + da, b) - f(a, b)) / da;
	
}

float dfabdb(float a, float b, float db) {
	
	return (f(a, b + db) - f(a, b)) / db;
	
}

int main() {
	
	printf("[ DATA ]\n" );
	
	for (int i = 0; i < N; i++) {
		
		datax[i] = i + M;
		datay[i] = i - M;
		
		cout << datax[i] << "   " << datay[i] << endl;

	}
	
	float a0 = 0, b0 = 0;
	int iteration = 0;
	float eta = 0.0001;
	float psi = 0.005;
	float da = 0.01;
	float db = 0.01;
	float a1 = 6, b1 = 25;
	
	while (dis(a0, b0, a1, b1) > eta && iteration < 1000000) {
		
		a0 = a1;
		b0 = b1;
		a1 -=   psi * dfabda(a0, b0, da);
		b1 -=   psi * dfabdb(a0, b0, db);
		iteration++;
		
	}
	
	cout << " y  = " << a1 << "x + " << b1 << endl;
	cout << iteration << "-th  E = " << dis(a0, b0, a1, b1) << endl;
	
	return 0;
}
