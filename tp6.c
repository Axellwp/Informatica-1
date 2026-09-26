#include <stdio.h>
#define pi 3.1416
float calcularAreaRectangulo(float a, float b);
float calcularPerimetroRectangulo (float a, float b);
float calcularAreaCirculo (float a);
float calcularPerimetroCirculo (float a);
void imprimirResultados (float a, float b);
int main(int argc, char *argv[]) {
	int opcion;
	printf("seleccione la figura: \n1) rectangulo \n2) circulo\n");
	do{
		scanf(" %d", &opcion);
		if(opcion != 1 && opcion != 2){
		printf("invalido, seleccione opcion ""1"" o ""2""\n");
		printf("vuelve a intentarlo:\n");
		}
	} while(opcion != 1 && opcion != 2);
	if( opcion == 1){
		float altura;
		float longitud;
		float area;
		float perimetro;
		printf("ingrese la altura de su rectangulo:\n");
		scanf(" %f", &altura);
		printf("ingrese la longitud de su rectangulo:\n");
		scanf(" %f", &longitud);
		area = calcularAreaRectangulo(altura, longitud);
		perimetro = calcularPerimetroRectangulo(altura, longitud);
		imprimirResultados(area, perimetro);
	}
	else if ( opcion == 2){
		float radio;
		float area, perimetro;
		printf("ingrese el radio de su circulo:\n");
		scanf(" %f", &radio);
		area = calcularAreaCirculo(radio);
		perimetro = calcularPerimetroCirculo(radio);
		imprimirResultados(area, perimetro);
	}
	return 0;
}
float calcularAreaRectangulo(float a, float l){
	float result;
	result = a * l;
	return result;
}
	float calcularPerimetroRectangulo(float a, float l){
		float result;
		result = (2 * a) + (2 * l);
		return result;
	}
	float calcularAreaCirculo(float radio){
		return pi * (radio * radio);
	}
	float calcularPerimetroCirculo(float radio){
		return (2 * pi) * radio;
	}
	void imprimirResultados(float area, float perimetro){
		printf(" su area es: %.2f \n su perimetro es: %.2f \n", area, perimetro);
	}
