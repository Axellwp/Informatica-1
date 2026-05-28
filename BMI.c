#include <stdio.h>

int main(int argc, char *argv[]) { //T.P N°3 by Axel ELiel ELio Llampa, legajo 424731, 1R5.
	float alt;
	float pes;
	float imc;
	printf("Indice de Masa corporal \n");
	printf("ingrese su altura en metros: \n");
	scanf(" %f", &alt);
	printf("ingrese su peso en Kg: \n");
	scanf(" %f", &pes);
	imc = pes / (alt*alt);
	printf("su indice de masa corporal es: %.2f \n", imc);
	printf("\t indice | Condicion \n \t-------------------- \n \t <18.5 | Bajo de peso \n \t 18.5 a 24.9 | Normal \n \t 25 a 29.9 | Sobrepeso \n \t >=30 | Obesidad");
	return 0;
}

