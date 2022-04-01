#include <stdio.h>
#include <cmath>

float avg(int a[]){
	
	float sum = 0;
	
	for(int i=0; i<4; i++){
		
		sum += a[i];
		
	}
	
	sum = sum / 4;
	
	return sum;
}

float denominator(int a[], float m){
	
	float sum = 0;
	
	for(int i=0; i<4; i++){
		
		sum += pow((a[i]-m), 2);
		
	}
	
	return sum;
	
}

float numerator(int a[], int b[], float m, float n){
	
	float sum = 0;
	
	for(int i=0; i<4; i++){
		
		sum += (a[i]-m) * (b[i]-n);
		
	}
	
	return sum;
	
}


int main(){
	
int x[] = {2, 4, 6, 8};
int y[] = {81, 93, 91, 97};

float mx = avg(x);
float my = avg(y);
float divisor = denominator(x, mx);
float dividend = numerator(x, y, mx, my);
float gradient = dividend / divisor;
float y_intercept = my - (mx * gradient);

printf("[ Average ]\n");
printf(" x : %.1f ,  y : %.1f\n\n", mx, my);

printf("[ Numerator / Denominator ]\n");
printf("%.1f / %.1f\n\n", dividend, divisor);

printf("[ Gradient ]\n%.1f\n\n", gradient);
printf("[ y_Intercept ]\n%.1f\n\n", y_intercept);

printf("=> y = %.1fx + %.1f\n", gradient, y_intercept);

return 0;


}
