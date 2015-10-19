#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
* Encripta la cadena de caracteres de entrada 'str', y retorna el resultado en 'encoded_str'. 
* Recordar que 'encoded_str' debe terminar con dos bits consecutivos en 0. 
* Ademas, el procedimiento debe retornar en el parametro 'table' la encriptacion usada para cada una de las letras
*/
/*DEFINIDA EN ASSEMBLER*/

int encrip(char *str, char key, char *encripted_str) {
	encripted_str[0] = 0b10010000;
	encripted_str[1] = 0b01010000;
	encripted_str[2] = 0b10010000;
	encripted_str[3] = 0b01010000;
	encripted_str[4] = 0b00000000;
	encripted_str[5] = 0b11011110;
	return 0;
}


/* 
* Toma como entradas una cadena de caracteres encripta 'decoded_str' (que finaliza con dos bits consecutivos en cero), 
* la tabla con la Encriptacion usada por cada letra, 'table', y retornar la cadena Encriptada en el parametro 'decoded_str'.
* Es importante agregar al final de 'decoded_str' el caracter null. 
*/
/*DEFINIDA EN ASSEMBLER*/
int decrip(char *encripted_str, char key, char *decripted_str) {
	char def_str[20] = "ABAB0";
	strcpy(decripted_str, def_str);
	printf("clave %d",key);
	return 0;
}


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

	unsigned char key=130;
	int str_elems;
	char def_str[20] = "ABAB0";
	char *str;
	char *encripted_str;
	char *decripted_str;
	
	if (argc == 1) {
		str = def_str;
		str_elems=5;
	}

	// Ejemplo provisto por el usuario
	if (argc == 2) {
		str = argv[1];
		str_elems = strlen(str)+1; //cantidad de elementos
	}

	// Ejemplo y key provisto por el usuario
	if (argc == 3) {
		str = argv[1];
		str_elems = strlen(str)+1; //cantidad de elementos
		key=atoi(argv[2]);
	}


	printf("--------------Entrada-----------\n");
	printf("Elems: %d\nkey: %i\nCadena: %s\n", str_elems,key,str);

	encripted_str = malloc(str_elems);
	decripted_str = malloc(str_elems);

	encrip(str, key, encripted_str);
	printf("\n-----------Resultado de la encriptacion--------\n");
	printf("Cadena encriptada: \n");
	print_encripted_string(encripted_str);
	decrip(encripted_str, key, decripted_str);

	printf("\n-----------Resultado de la desencriptacion--------\n");
	printf("\nCadena desencriptada: '%s'\n", decripted_str);
	if (encripted_str != NULL)
		free(encripted_str);
	if(decripted_str != NULL)
		free(decripted_str);


}