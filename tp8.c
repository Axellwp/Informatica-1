//by axel eliel elio llampa-424731    https://github.com/Axellwp/Informatica-1
#include <stdio.h>
#include <stdlib.h>
#define TAM 20
int cuantas_piezas(int);
int rectificable(float, float);
int rechazada(float, float);
void cargar_piezas(float *, int);
int contar(int (*)(float, float), float, float *, int);
float* reserva_memoria(int);
void segregar(int (*)(float, float), float, float *, int, float *);
void mostrar_piezas(char *, float *, int);
int main (void) {
	float diametros[TAM] = {0};
	int n;
	float max = 12;
	float min = 10;
	n = cuantas_piezas(TAM);
	cargar_piezas(diametros, n);
	int n_rectificar = contar(rectificable, max, diametros, n);
	float *p_rectificables = reserva_memoria(n_rectificar);
	segregar(rectificable, max, diametros, n, p_rectificables);
	int n_rechazar = contar(rechazada, min, diametros, n);
	float *p_rechazadas = reserva_memoria(n_rechazar);
	segregar(rechazada, min, diametros, n, p_rechazadas);
	mostrar_piezas("rectificables", p_rectificables, n_rectificar);
	mostrar_piezas("rechazadas", p_rechazadas, n_rechazar);
	return 0;
}
int cuantas_piezas(int max) {
	int n;
	do {
		printf("Cuántas piezas ingresará? ");
		scanf("%d", &n);
	} while (n < 0 || n > max);
	return n;
}
int rectificable(float diametro, float valor) {
	if (diametro > valor)
		return 1;
	else
		return 0;
}
int rechazada(float diametro, float valor) {
	if (diametro < valor)
		return 1;
	else
		return 0;
}
void cargar_piezas(float *p,int n){
	for(int i = 0; i < n; i++){
		do{
			printf("ingrese el diametro de la pieza %d\n", i);
			scanf(" %f", (p+i));
		} while(*(p+i) <= 0);
	}
}
int contar(int (*condicion)(float,float), float max, float *p, int n){
	int contador = 0;
	for(int i = 0; i < n; i++){
		int m = condicion(*(p+i),max);
		if (m == 1){
			contador += 1;
		}
	}
	return contador;
}
float *reserva_memoria(int n){
	float *p;
	p = malloc(n * sizeof(float));
	if (p == NULL){
		exit(1);
	}
	return p;
}
	void segregar(int (*condicion)(float, float),float max, float *diam,int n, float *p){
		int j = 0;
		for(int i = 0; i < n; i ++){
			int m = condicion(*(diam+i),max);
			if(m == 1){
				*(p+j) = *(diam+i); 
				j++;
			}
		}
	}
		void mostrar_piezas(char *mos, float *p, int n){
			printf("Piezas %s:\n", mos);
			for(int i = 0; i < n; i++){
				printf("Diametro = %.2f\n", *(p+i));
			}
		}
