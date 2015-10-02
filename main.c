#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Precondicion: str apunta a un arreglo de caracteres terminado en null.
// Postcondicion: Imprime la representacion binaria de cada uno de los caracteres en str.
void print_binary_rep(char *str) {
	int i = 0,j = 0;
	char curr;
	unsigned char mask;
	while (curr = str[i]) {
//		printf("%d:",curr);
		// Los codigos ascii son: A: 65, B: 66, C: 67, D: 68 ........
		mask = 0x80;
		for (j=0;j<8;j++) {
			if (curr & mask)
				printf("1");
			else
				printf("0");
			mask = mask >> 1;
		}
		printf(" ");
		i += 1;
	}
	printf("\n");
}


// Precondicion: str apunta a la salida del algoritmo de encriptacion (termina con dos 00 consecutivos en la representacion binaria de la salida)
// Postcondicion: Imprime la representacion binaria de la salida del algoritmo de encriptacion
void print_encripted_string(char *str) {
	int i = 0,j = 0;
	char curr;
	unsigned char mask;
	int prev_zero = 0, finished = 0;
	while (!finished) {
		curr = str[i];

                printf("\n");

		mask = 0x80;
		for (j=0;j<8;j++) {
			if (curr & mask) {
				printf("1");
				prev_zero = 0;
			}
			else {
				printf("0");
				if (prev_zero) {
					//finished = 1;
					//break;
				} else {
					prev_zero = 1;
				}
			}
			mask = mask >> 1;
		}
	if (curr == 0)
    		finished =1;
		
	i += 1;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {

	// Ejemplo por defecto:
	// AAACCB
	char def_str[20] = "ABAB",null; // el fin de cadena te lo da C
	unsigned char key;
	int str_elems = 20;

	char *str;
	char *encripted_str;
	char *decripted_str;

	if (argc == 1) {
		str = &def_str; // cadena por defecto
		key = 130;     // pass por defecto
	}

	// Ejemplo provisto por el usuario
	if (argc == 2) {
		str = argv[1];   //
		str_elems = strlen(str)+1; //cantidad de elementos
	}
	printf("Elems: \n%d\n", str_elems);


	printf("-----------Cadena de entrada--------\n");
	printf("Cadena: \n%s\n", str);

	encripted_str = malloc(str_elems+20);
	decripted_str = malloc(str_elems+20);

	encrip(str, key, encripted_str);
	printf("-----------Resultado de la encriptacion--------\n");
	printf("Cadena encriptada: \n");
	print_encripted_string(encripted_str);
	//printf("Cadena encriptada en formato caracter: \n%s\n", encripted_str);
	decrip(encripted_str, key, decripted_str);

	printf("-----------Resultado de la desencriptacion--------\n");
	printf("Cadena desencriptada: \n%s\n", decripted_str);
	free(encripted_str);
	free(decripted_str);

}