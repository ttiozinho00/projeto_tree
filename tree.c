/*
* Método de compilação do código: gcc -o tree.exe tree.c funcoes.c -Wall -pedantic -Wextra -Werror
*/

/*
   Programa: Estrutura de Diretórios (Tree)
   Descrição: Este programa exibe a estrutura de diretórios e arquivos a partir de um diretório raiz, com opções para incluir ou excluir arquivos, e exibir a estrutura utilizando caracteres ASCII.

   Funcionalidades:
   - Aceita parâmetros via linha de comando:
     (a) Diretório inicial para a busca de arquivos e pastas
     (b) Opção "/A" para usar caracteres ASCII na exibição da estrutura
     (c) Opção "/F" para incluir arquivos na exibição (por padrão, exibe apenas pastas)
     (d) Opção "/?" para exibir a ajuda sobre o uso do programa
   - Realiza a busca recursiva de arquivos e pastas a partir do diretório inicial
   - Exibe a estrutura de diretórios com diferentes níveis de profundidade
   - Suporta a exibição de arquivos (opção "/F")
   - Exibe um resumo ao final com o número total de arquivos e pastas analisados

   Exemplos de uso:
   - tree                       (Exibe a estrutura do diretório atual)
   - tree /A                    (Exibe a estrutura utilizando caracteres ASCII)
   - tree /F                    (Exibe a estrutura com arquivos incluídos)
   - tree /A /F                 (Exibe a estrutura com arquivos e usando ASCII)
   - tree /?                    (Exibe a ajuda do programa)

   Observações:
   - O programa verifica se o diretório informado existe e se é acessível.
   - O programa exibe a estrutura de diretórios recursivamente, podendo incluir arquivos e usar ASCII conforme as opções fornecidas.

   Programador: [Seu Nome]
   RGM: [Seu RGM]
   Data da última modificação: [Data da modificação]
*/
#include <io.h>        /* _findfirst(), _findnext(), _findclose() */
#include <locale.h>    /* setlocale() */
#include <stdio.h>     /* printf() */
#include <string.h>    /* strcmp() */
#include "funcoes.h"   /* Declarações das funções */

/* Função principal do programa */
int main(int argc, char *argv[]) 
{
    char diretorio[520] = "."; /* Diretório inicial */
    int incluir_arquivos = 0;  /* Flag para incluir arquivos */
    int usar_ascii = 0;        /* Flag para usar ASCII */
    int exibir_ajuda_flag = 0; /* Flag para exibir ajuda */
    int i;                     /* Índice para loops */

    setlocale(LC_ALL, ""); /* Configura a localidade para UTF-8 */

    /* Processa argumentos da linha de comando */
    for (i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "/?") == 0) 
        {
            exibir_ajuda_flag = 1;
        } 
        else if (strcmp(argv[i], "/A") == 0) 
        {
            usar_ascii = 1;
            incluir_arquivos = 1;
        } 
        else if (strcmp(argv[i], "/F") == 0) 
        {
            incluir_arquivos = 1;
        } 
        else 
        {
            strncpy(diretorio, argv[i], sizeof(diretorio) - 1);
        }
    }

    /* Verifica se a ajuda foi solicitada */
    if (exibir_ajuda_flag) 
    {
        exibir_ajuda();
        return 0;
    }

    /* Verifica se o diretório especificado existe */
    if (_access(diretorio, 0) != 0) 
    {
        printf("Erro: O diretório especificado '%s' não existe ou não pode ser acessado.\n", diretorio);
        return 1;
    }

    /* Exibe a estrutura do diretório */
    printf("Estrutura do diretório: %s\n", diretorio);
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, 0);

    return 0;
}

