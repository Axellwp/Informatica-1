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
	printf("su indice de masa corporal es: %.2f \n", imc); //primer cambio del codigo
		printf("\tIndice\t\tCondicion\n");
	printf("\t-----------------------------\n");
	printf("\t<18.5\t\tBajo de peso\n");
	printf("\t18.5 a 24.9\tNormal\n");
	printf("\t25 a 29.9\tSobrepeso\n");
	printf("\t>=30\t\tObesidad\n\n");
	if (imc < 18.5) {
	printf("Usted esta bajo de peso.\n");
	}
	else if (imc < 25) {
	printf("Usted tiene un peso normal.\n");
	}
	else if (imc < 30) {
	printf("Usted tiene sobrepeso.\n");
	}
	else {
	printf("Usted tiene obesidad.\n");
	}
	return 0;
}

