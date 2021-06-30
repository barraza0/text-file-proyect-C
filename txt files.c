//Brenda Barraza

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct registro{
    int vocales;
    int consonantes;
    char letras_mas_repetidas;
    int palabras_inic;
};

int contar_vocales(char*);
int funcion_vocales(char);
char letra_mas_repetida(char*);
int palabras_iniciadas(char*);
int contar_consonantes(int,char*);
int grabar_binario(int,int,int,char);

void main(){

    FILE *archivo;
    char buffer[4000];

    if((archivo = fopen("fragmento_del_Centinela.txt", "r+"))==NULL){
        printf("ERROR\nERROR\nERROR");//el archivo NO abre correctamente
    }else{
        printf("LEYENDO..........\n\n");//el archivo abre correctamente

        fread (&buffer,sizeof(buffer),1,archivo);//guardo el archivo en el vector del buffer


        //cuenta la letra mas repetida, recibe como parametro el vector con el texto
        char Mas_Repet = letra_mas_repetida(buffer);

        //cuenta la cantidas de vocales, recibe como parametro el vector con el texto
        int Vocales = contar_vocales(buffer);

        //cuenta la cantidad de consonantes, recibe como parametro el vector con el texto y la cantidad de vocales para restarlas
        int Consonantes = contar_consonantes(Vocales,buffer);

        //cuenta la cantidad de palabras que inician con la letra pedida al usuario, recibe el vector del texto
        int Palab_Inic = palabras_iniciadas(buffer);

        //recibe como parametros los resultados de las anteriores funciones y los guarda en un archivo binario
        grabar_binario(Vocales,Consonantes,Palab_Inic,Mas_Repet);
    }
    fclose(archivo);//cierro archivo
}

int contar_vocales(char*buffer){

    char *ptr,*var,temporal[4000];
    int Num_Caracter=0,vocales=0,resultado,total=strlen(buffer);

    ptr=buffer;//inicializo el puntero a la variable
    var=temporal;//inicializo el puntero a la variable

        while(Num_Caracter<total){//mientras no se lea el total de caracteres

            *var=*ptr;//voy copiando los caracteres
            ptr++;//incremento punteros
            var++;
            temporal[Num_Caracter] = toupper(temporal[Num_Caracter]);//convierto el caracter a mayuscula

            //almaceno en la variable resultado si el caracter es vocal o no
            resultado = funcion_vocales(temporal[Num_Caracter]);

            //si el caracter es vocal el resultado de la funcion es 1
            if(resultado==1){
                vocales++;//incrememto variable
            }

            Num_Caracter++;//incremento numero de caracteres para analizar el siguiente
        }

    return vocales;//retorno la cantidad total de vocales
}

int funcion_vocales(char letra){

    if(letra=='A'||letra=='E'||letra=='I'||letra=='O'||letra=='U'||letra=='í'||letra=='ó'||letra=='ú'||letra=='é'||letra=='á'){
        //si el caracter comple con alguna de las condiciones es vocal y la funcion retorna 1
        return 1;

        }else{
            //si no es vocal retorna 0
            return 0;
        }
}

char letra_mas_repetida(char*buffer){

    int contador[256]={0};//inicializo en 0 el vector
    int max=0;
    char caracter=0;

    while(*buffer){
        //guardo en el array contador los caracteres del codigo ASCII y voy incrementando a medida que los encuentro en buffer
        //exeptua los espacios porque son los que mas se repiten
        if(++contador[*buffer]>max&&*buffer!=' '){
            //guardo la cantidad de veces que aparece el caracter en max
            max=contador[*buffer];
            //guardo en la variable caracter el caracter mas aparecido hasta el momento
            caracter=*buffer;
        }
        buffer++;//incremento para analizar el siguiente caracter

    }
    return caracter;//retorno la letra mas repetida
}

int palabras_iniciadas(char*buffer){

    char Letra;
    int palabra=0,Total=strlen(buffer),ContCaract=0;

    printf("buscar palabras iniciadas por letra... : ");
    scanf("%c", &Letra);
    if (buffer[ContCaract] == Letra) {
                palabra++;
    }
    while(ContCaract<Total){

        if(buffer[ContCaract]==' '){
            ContCaract++;
            //si la palabra empieza por la letra elegida incremento la variable
            if (buffer[ContCaract] == Letra) {
                palabra++;
            }
        }
        ContCaract++;
    }
    return palabra;//retorno la cantidad de palabras que inician con la letra elegida
}

int contar_consonantes(int Vocales,char*buffer){

    int Total=strlen(buffer),Consonantes=0,Cont_Caracter=0;
    char *ptr,*var,temporal[4000];

    //inicializo los punteros a las variables
    ptr=buffer;
    var=temporal;

        //mientras no se supere el total de caracteres
        while(Cont_Caracter<Total){
            *var=*ptr; //voy copiando los caracteres
            ptr++;//incremento los punteros
            var++;
            temporal[Cont_Caracter] = toupper(temporal[Cont_Caracter]);  //convierto a mayusculas el caracter

            if(temporal[Cont_Caracter]<=90&&temporal[Cont_Caracter]>=65||temporal[Cont_Caracter]<=163&&temporal[Cont_Caracter]>=160||temporal[Cont_Caracter]==130){
                //si se cumplen las condiciones quiere decir que el caracter es una letra y se incrementa la variable
                Consonantes++;
            }
            Cont_Caracter++;//incremento para analizar el siguente caracter
        }
        Consonantes-=Vocales;//resto las vocales a la cantidad total de letras que hay en consonante
        return Consonantes;//retorno la cantidad total de consonantes
}

int grabar_binario(int vocales,int consonantes,int palab_inic,char letra_mas_repet){
    struct registro DATO;
    FILE *binario;
    char opcion_visualizar;

    if((binario = fopen("BD.bin", "ab"))==NULL){
            printf("Error al abrir el archivo binario..");
        }else{
            DATO.vocales=vocales;
            DATO.consonantes=consonantes;
            DATO.palabras_inic=palab_inic;
            DATO.letras_mas_repetidas=letra_mas_repet;

            if(fwrite (&DATO,1,sizeof(struct registro),binario)){
                printf("grabado correctamente.\n");
            }else{
                printf("FALLA al grabar ... saliendo..\n");
            }
            fclose(binario);
        }

        printf("desea ver los resultados?(S/N)\n");
        fflush(stdin);
        scanf("%c",&opcion_visualizar);
        if(opcion_visualizar=='s'||opcion_visualizar=='S'){
            printf("\nCANTIDAD DE VOCALES: %d\n",DATO.vocales);
            printf("CANTIDAD DE CONSONANTES: %d\n",DATO.consonantes);
            printf("CANTIDAD DE PALABRAS INICIADAS: %d\n",DATO.palabras_inic);
            printf("LETRA MAS REPETIDA: %c\n",DATO.letras_mas_repetidas);

        }else{
            return 0;
        }

}


















