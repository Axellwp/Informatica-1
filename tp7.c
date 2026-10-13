#include <stdio.h>
#define TAM 5
int main(int argc, char *argv[]) {
	int cod[TAM];
	float precio[TAM];
	printf("ingrese %d productos, se solicitara el codigo y precio:\n", TAM);
	for(int i = 0; i < TAM; i++){
	do{
	printf("ingrese el codigo de barra (0-999999999) del producto %d\n", i + 1);
	scanf(" %d", &cod[i]);
	if(cod[i] <= 0 || cod[i] > 999999999)
		printf("error, intentelo de nuevo \n");
	} while(cod[i] <= 0 || cod[i] > 999999999);
	do{
		printf("ingrese su precio:\n");
		scanf(" %f", &precio[i]);
		if(precio[i] < 0)
			printf("error, el precio no puede ser negativo\n");
	} while(precio[i] < 0);
		}
	float pmay = precio[0];
	int cmay = cod[0];
	float pmen = precio[0];
	int cmen = cod[0];
	printf("codigo\tprecio\n");
	for(int i = 0; i < TAM; i++){
		printf("%d\t%.2f\n", cod[i], precio[i]);}
	for(int i = 0; i < TAM; i++){
		if(precio[i] > pmay){
			pmay = precio[i];
			cmay = cod[i];
		}
		if(precio[i] < pmen){
			pmen = precio[i];
			cmen = cod[i];
		}
	}
	printf(" precio mayor:%.2f codigo: %d\n", pmay, cmay);
	printf(" precio menor:%.2f codigo: %d\n", pmen, cmen);
return 0;
}

