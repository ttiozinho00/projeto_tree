#include <string.h>
#include <stdio.h>
#include "funcoes.h"

int main(int argc, char *argv[]) 
{
    char *diretorio = ".";
    int incluir_arquivos;
    int usar_ascii;
    int contador_pastas;
    int contador_arquivos;
    int i;

    incluir_arquivos = 0;
    usar_ascii = 0;
    contador_pastas = 0;
    contador_arquivos = 0;

    for (i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "/?") == 0) 
        {
            exibir_ajuda();
            return 0;
        } 

        else if (strcmp(argv[i], "/A") == 0) 
        {
            usar_ascii = 1;
        } 

        else if (strcmp(argv[i], "/F") == 0) 
        {
            incluir_arquivos = 1;
        } 
        else 
        {
            diretorio = argv[i];
        }
    }

    printf("Estrutura do diretório: %s\n", diretorio);
    
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, &contador_pastas, &contador_arquivos, 0);

    return 0;
}
