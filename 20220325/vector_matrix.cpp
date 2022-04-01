#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

struct Vector{  // 3 x 1 Vector
	
	float x;
	float y;
	float z;
	
};

Vector Plus(Vector v1, Vector v2){
	
	Vector v_plus;
	
	v_plus.x = v1.x + v2.x;
	v_plus.y = v1.y + v2.y;
	v_plus.z = v1.z + v2.z;
	
	return v_plus;
	
}

Vector Minus(Vector v1, Vector v2){

	Vector v_minus;
	
	v_minus.x = v1.x - v2.x;
	v_minus.y = v1.y - v2.y;
	v_minus.z = v1.z - v2.z;
	
	return v_minus;
	
}

Vector Scalar_product(Vector v1, int scalar){
	
	Vector v_product;
	
	v_product.x = v1.x * scalar;
	v_product.y = v1.y * scalar;
	v_product.z = v1.z * scalar;
	
	return v_product;
	
}
 
float Inner_product(Vector v1, Vector v2){  // multiplication
	
	float inner_result = 0;
	
	inner_result = (v1.x * v2.x) + (v1.y * v2.y) * (v1.z * v2.z);
	
	return inner_result;
	
}	
		
Vector Outer_product(Vector v1, Vector v2){  // multiplication
	
	Vector outer_result;
	
	outer_result.x = (v1.y * v2.z) - (v1.z * v2.y);
	outer_result.y = (v1.z * v2.x) - (v1.x * v2.z);
	outer_result.z = (v1.x * v2.y) - (v1.y * v2.x);
		
	return outer_result;
	
}	

/*
Vector create(){
	
	Vector n1;
	
	srand(time(NULL));
		
	n1.x = rand()%10+1;
	n1.y = rand()%10+1;
	n1.z = rand()%10+1;
	
	return n1;
	
}
*/

int main(){
	
	Vector v1;
	
	v1.x = rand()%10+1;
	v1.y = rand()%10+1;
	v1.z = rand()%10+1;
	
	Vector v2;
	
	v2.x = rand()%10+1;
	v2.y = rand()%10+1;
	v2.z = rand()%10+1;
	
	int scalar = rand()%10+1;
	
	Vector v_plus = Plus(v1, v2);
    Vector v_minus = Minus(v1, v2);
    Vector v_product = Scalar_product(v1, scalar);
    float inner_result = Inner_product(v1, v2);
    Vector outer_result = Outer_product(v1, v2);
	
	printf("Vector 1 : [ %.2f , %.2f , %.2f ]\n", v1.x, v1.y, v1.z);
	printf("Vector 2 : [ %.2f , %.2f , %.2f ]\n", v2.x, v2.y, v2.z);
	
	printf("Addition of Vectors : [ %.2f , %.2f , %.2f ]\n", v_plus.x, v_plus.y, v_plus.z);
	printf("Subtraction of Vectors : [ %.2f , %.2f , %.2f ]\n", v_minus.x, v_minus.y, v_minus.z);
	printf("Scalar Product : [ %.2f , %.2f , %.2f ]\n", v_product.x, v_product.y, v_product.z);
	printf("Inner Product : [ %.2f ]\n", inner_result);
	printf("Outer Product : [ %.2f , %.2f , %.2f ]\n", outer_result.x, outer_result.y, outer_result.z);
	
	return 0;
	
}		
		
		
		
		
		
		
		
		
		
