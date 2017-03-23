#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

struct casilla {
	char etiqueta ;
	char tipo;
	int nMinas;
};

typedef struct casilla tipoCasilla;

void destapaceros(tipoCasilla** r, int filas, int columna, int i, int j );

/*para la funciÃ²n que crea una matriz*/

tipoCasilla** crearMatrix(int filas, int columna){
	int i ;
	tipoCasilla** mat=(tipoCasilla**)malloc(filas*sizeof(tipoCasilla*));//numero de filas que son apuntadores a nada.
	for (i=0;i<filas; i++){
		mat[i]=(tipoCasilla*) malloc(sizeof(tipoCasilla)*columna);// espacio de memoria para las columnas
	}
	return mat; 
}

void llenarMat(tipoCasilla **mat, int filas, int columna){
	int i, j ;
	for (i =0 ; i< filas; i++){
		for(j=0 ; j<columna; j++){
			mat[i][j].etiqueta='#';
			mat[i][j].tipo='c';
			mat[i][j].nMinas=0;
		}
	}
}
 
 void dibujar(int filas,int columna, tipoCasilla** r){
	 int i,j ;
	 for (i=1 ; i<filas-1; i++){
		 for(j=1; j<columna-1; j++){
			printf("%c\t ",/*r[i][j].nMinas, r[i][j].tipo,*/ r[i][j].etiqueta);
		 }
		 printf("\n");
	 }
 }
 
 
 void ponerMina(tipoCasilla** r, int filas, int columna, int minas){
 	int posx, posy, i;
	for ( i=1; i <= minas; i++ ){
		posx= 1+(rand() % (filas-2));
		posy= 1+(rand() % (columna-2));
		if(r[posx][posy].tipo != 'M'){
			r[posx][posy].tipo='M';
		}else{
			posx= 1+(rand() % (filas-2));
			posy= 1+(rand() % (columna-2));
			r[posx][posy].tipo='M';
		}
	} 
 }
void ponerNumero(tipoCasilla** r, int filas, int columnas, int minas  ){
	int i,j,contMin;
	for (i=1; i < filas-1; i ++){
		for(j=1; j<columnas-1; j++){
			if (r[i][j].tipo == 'M'){
				if(r[i-1][j-1].tipo != 'M'){
					r[i-1][j-1].nMinas=r[i-1][j-1].nMinas+1;
				}if(r[i][j-1].tipo !='M'){
					r[i][j-1].nMinas=r[i][j-1].nMinas+1;
				}if (r[i-1][j].tipo != 'M'){
					r[i-1][j].nMinas=r[i-1][j].nMinas+1;
				}if (r[i-1][j+1].tipo != 'M'){
					r[i-1][j+1].nMinas = r[i-1][j+1].nMinas+1;
				}if (r[i][j+1].tipo != 'M'){
					r[i][j+1].nMinas= r[i][j+1].nMinas+1;
				}if (r[i+1][j-1].tipo != 'M'){
					r[i+1][j-1].nMinas=r[i+1][j-1].nMinas+1;
				}if (r[i+1][j].tipo != 'M'){
					r[i+1][j].nMinas=r[i+1][j].nMinas+1;
				}if (r[i+1][j+1].tipo != 'M'){
					r[i+1][j+1].nMinas=r[i+1][j+1].nMinas+1;
				}
			}
		}
	}
}

void destapar(tipoCasilla** r, int filas, int columna){
	int i, j;
	while(1){
		printf("Digite la posicion en la fila:");
		scanf("%d",&i);
		printf("Digite la poscion de la columna:");
		scanf("%d",&j);
		if(r[i][j].tipo == 'M'){
			r[i][j].etiqueta=r[i][j].tipo;
			printf("perdiste!!");
			break;
		}else{
			r[i][j].etiqueta=r[i][j].nMinas +'0';
			if(r[i][j].nMinas== '0'){
				destapaceros(r, filas, columna, i , j );
			}
			dibujar(filas,columna, r);

		}
	}

}

void destapaceros(tipoCasilla** r, int filas, int columna, int i, int j ){
		if(r[i-1][j-1].nMinas == '0'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}if(r[i][j-1].tipo !='M'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}if (r[i-1][j].tipo != 'M'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}if (r[i-1][j+1].tipo != 'M'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}if (r[i][j+1].tipo != 'M'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}if (r[i+1][j-1].tipo != 'M'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}if (r[i+1][j].tipo != 'M'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}if (r[i+1][j+1].tipo != 'M'){
			r[i][j].etiqueta=r[i][j].nMinas +'0';
		}

}

int main(int argc,char *argv[]){

    int filas=atoi(argv[1])+2;
    int columna=atoi(argv[2])+2;
    int minas= atoi(argv[3]);
	srand(time(NULL));
    tipoCasilla ** r = crearMatrix(filas,columna);
    llenarMat(r, filas,columna);
	dibujar(filas, columna, r);
	ponerMina(r,filas,columna,minas);
	ponerNumero(r, filas, columna, minas);
	destapar(r, filas, columna);
	//dibujar(filas, columna, r);
}
