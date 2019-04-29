#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TXT 100
#define KEY 20

void ingresatexto(char*texto);
void ingresallave(char*llave);
void asciipos(char *texto, int *text, int largo);
void printascii(int *texto, int largo);
void Cifrado(int*texto,int tamtxt,int *key,int tamkey);
void claveinversa(int *key,int *keyinv, int tamkey);
void abrirArchivo(char* texto);
void guardarArchivo(int* textoCifrado,int tam);
int main()
{
	char texto[TXT];
	int  text[TXT];
	char key[KEY];
	int kei[KEY];
	int iek[KEY];	
	int i,opcion;
	do
	{
	system("cls");
	printf("Elija una opcion:\n");
	printf("1:Cifrado Cesar\n");
	printf("2:Decifrado Cesar\n");		
	printf("3:Cifrado Vigenere\n");
	printf("4:Decifrado Vigenere\n");
	printf("5:Cifrar un texto\n");
	printf("6:Decifrar un texto\n");
	printf("Tu opcion: ");
	scanf("%d",&opcion);
	}while(opcion<1&&opcion>4);
	ingresatexto(texto);
	system("cls");
	switch(opcion)
	{
	case 1: printf("Cifrado Cesar\n");
			ingresatexto(texto);
			asciipos(texto, text, strlen(texto));
			kei[0]=35;
			Cifrado(text,strlen(texto),kei,1);
			printascii(text,strlen(texto));
			break;
	case 2: printf("Decifrado Cesar\n");
			ingresatexto(texto);
			asciipos(texto, text, strlen(texto));
			kei[0]=29;
			Cifrado(text,strlen(texto),kei,1);
			printascii(text,strlen(texto));
			break;
	case 3:	printf("Cifrado Vigenere\n");
			ingresatexto(texto);
		    ingresallave(key);
		    asciipos(texto, text, strlen(texto));
		    asciipos(key, kei, strlen(key));
		    Cifrado(text,strlen(texto),kei,strlen(key));
		    printascii(text,strlen(texto));
		    claveinversa(kei,iek,strlen(key));		    
		    break;
	case 4:	printf("Decifrado Vigenere\n *Ingresar la clave inversa en el apartado clave*\n");
			ingresatexto(texto);
		    ingresallave(key);
		    asciipos(texto, text, strlen(texto));
		    asciipos(key, kei, strlen(key));
		    Cifrado(text,strlen(texto),kei,strlen(key));
		    printascii(text,strlen(texto));	    
		    break;
	case 5:	printf("Cifrado Texto\n");
			abrirArchivo(texto);
	    	ingresallave(key);
	    	system("cls");
	    	printf("Cifrado Texto\n");
	    	ingresallave(key);
		    asciipos(texto, text, strlen(texto));
		    asciipos(key, kei, strlen(key));
		    Cifrado(text,strlen(texto),kei,strlen(key));
		    guardarArchivo(text,strlen(texto));
			claveinversa(kei,iek,strlen(key));    
		    break;
	case 6:	printf("Decifrado Texto\n*Ingresar la clave inversa en el apartado clave*\n");
			abrirArchivo(texto);
			ingresallave(key);
			system("cls");
	    	printf("Decifrado Texto\n*Ingresar la clave inversa en el apartado clave*\n");
	    	ingresallave(key);
			asciipos(texto, text, strlen(texto));
		    asciipos(key, kei, strlen(key));
		    Cifrado(text,strlen(texto),kei,strlen(key));
		    guardarArchivo(text,strlen(texto));
			break;
	default:;
	}
	system("pause");
	return 0;	
}
void ingresatexto(char*texto)
{
	printf("Ingrese el texto a codificar: ");
	gets(texto);
}
void ingresallave(char*llave)
{
	printf("Ingrese la clave de codificacion: ");
	gets(llave);
}

void asciipos(char *texto, int *text, int largo)
{
	int j;
	for(j=0;j<largo;j++)
	{
		text[j]=(int)texto[j];
		if(text[j]<0)
		text[j]+=256;
		if(text[j]>251)
		text[j]-=223;
	}
	
}
void printascii(int *texto, int largo)
{
	int i;
	printf("Texto nuevo:");
	for(i=0;i<largo;i++)
	printf("%c",texto[i]);
	printf("\n");	
}
void Cifrado(int*texto,int tamtxt,int* key,int tamkey)
{
	int ct,ck;
	ck=0;
	for(ct=0;ct<tamtxt;ct++)
	{
		texto[ct]=texto[ct]+key[ck]-64;
		if(texto[ct]>222&&texto[ct]<414)
        texto[ct]-=191;
        else if(texto[ct]>413)
        texto[ct]-=382;
		else
        texto[ct]+=32;
		ck++;
		if(ck==tamkey)
		ck=0;
	}
}
void claveinversa(int *key,int *keyinv, int tamkey)
{
	int i;
	printf("Clave inversa: ");
	for(i=0;i<tamkey;i++)
	{
		keyinv[i]=287-key[i];
		printf("%c",keyinv[i]);
	}
	printf("\n");
}
void abrirArchivo(char* texto){
        int i;
		FILE* file  = NULL;
        char nomArchivo[KEY];
        char cadenaAux[KEY];
        printf("Introduzca el nombre del archivo \n");
        scanf("%s",nomArchivo);
        file = fopen(nomArchivo,"r+");
        if(file == NULL)
            {
                printf("El archivo está vacío o no existe \n");
                return;
            }
         while(fgets(cadenaAux,KEY,file)!=NULL)
            {
                 if(texto[0]==0)
                 {
                 strcpy(texto,cadenaAux);
				 }
                 else
                 {
                     strcat(texto,cadenaAux);
                 }
             }
        printf("%s \n",texto);
        fclose(file);
    }
    void guardarArchivo(int* textoCifrado,int tam){
        FILE* file = NULL;
        char nomArchivo[KEY];
        int code,i;
        printf("\n Introduzca el nombre del archivo para guardar el cifrado \n");
        scanf("%s",nomArchivo);
        file = fopen(nomArchivo,"r+");
        for(i=0;i<tam;i++)
		{
		code = fputc(textoCifrado[i],file);
        if(code<0)
        {
		printf("Error al abrir el archivo");
    	break;
		}
    	}
    	if(code>-1)
    	printf("Cifrado guardado con éxito");
        fclose(file);
    }
