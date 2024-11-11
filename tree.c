#include <io.h>          /* Para uso de _access no Windows */
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "funcoes.h"

int main(int argc, char *argv[]) 
{
    char diretorio[520] = ".";  /* Diret�rio padr�o � o diret�rio atual */
    int incluir_arquivos;
    int usar_ascii;
    int contador_pastas;
    int contador_arquivos;
    int exibir_ajuda_flag;
    int i;

    incluir_arquivos = 0;
    usar_ascii = 0;
    contador_pastas = 0;
    contador_arquivos = 0;
    exibir_ajuda_flag = 0;
    

    setlocale(LC_CTYPE, "");

    /* Processa os argumentos da linha de comando */ 
    for (i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "/?") == 0) 
        {
            exibir_ajuda_flag = 1;
        } 
        else if (strcmp(argv[i], "/A") == 0) 
        {
            if (usar_ascii) 
            {
                printf("Erro: A op��o /A foi especificada mais de uma vez.\n");
                return 1;
            }
            usar_ascii = 1;
        } 
        else if (strcmp(argv[i], "/F") == 0) 
        {
            if (incluir_arquivos) 
            {
                printf("Erro: A op��o /F foi especificada mais de uma vez.\n");
                return 1;
            }
            incluir_arquivos = 1;
        } 
        else 
        {
            strncpy(diretorio, argv[i], sizeof(diretorio) - 1);  /* Assume que o argumento � um diret�rio */ 
        }
    }

    /* Exibe a ajuda se a op��o /? foi especificada */ 
    if (exibir_ajuda_flag) 
    {
        exibir_ajuda();
        return 0;
    }

    /* Verifica se o diret�rio especificado existe */ 
    if (_access(diretorio, 0) != 0) 
    {
        printf("Erro: O diret�rio especificado '%s' n�o existe ou n�o pode ser acessado.\n", diretorio);
        return 1;
    }

    /* Exibe a estrutura do diret�rio atual e chama a fun��o de busca com o n�vel inicial 0 */ 
    printf("Estrutura do diret�rio: %s\n", diretorio);
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, &contador_pastas, &contador_arquivos, 0);

    /* Exibe o resumo final */ 
    printf("\nVerifica��o conclu�da.\n");
    printf("Total de pastas analisadas: %d\n", contador_pastas);
    printf("Total de arquivos analisados: %d\n", contador_arquivos);

    return 0;
}
