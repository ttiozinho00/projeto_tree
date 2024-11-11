/*
* M�todo de compila��o do c�digo: gcc -o tree.exe tree.c funcoes.c -Wall -pedantic -Wextra -Werror
*/

/*
   Programa: Estrutura de Diret�rios (Tree)
   Descri��o: Este programa exibe a estrutura de diret�rios e arquivos a partir de um diret�rio raiz, com op��es para incluir ou excluir arquivos, e exibir a estrutura utilizando caracteres ASCII.

   Funcionalidades:
   - Aceita par�metros via linha de comando:
     (a) Diret�rio inicial para a busca de arquivos e pastas
     (b) Op��o "/A" para usar caracteres ASCII na exibi��o da estrutura
     (c) Op��o "/F" para incluir arquivos na exibi��o (por padr�o, exibe apenas pastas)
     (d) Op��o "/?" para exibir a ajuda sobre o uso do programa
   - Realiza a busca recursiva de arquivos e pastas a partir do diret�rio inicial
   - Exibe a estrutura de diret�rios com diferentes n�veis de profundidade
   - Suporta a exibi��o de arquivos (op��o "/F")
   - Exibe um resumo ao final com o n�mero total de arquivos e pastas analisados

   Exemplos de uso:
   - tree                       (Exibe a estrutura do diret�rio atual)
   - tree /A                    (Exibe a estrutura utilizando caracteres ASCII)
   - tree /F                    (Exibe a estrutura com arquivos inclu�dos)
   - tree /A /F                 (Exibe a estrutura com arquivos e usando ASCII)
   - tree /?                    (Exibe a ajuda do programa)

   Observa��es:
   - O programa verifica se o diret�rio informado existe e se � acess�vel.
   - O programa exibe a estrutura de diret�rios recursivamente, podendo incluir arquivos e usar ASCII conforme as op��es fornecidas.

   Programador: [Seu Nome]
   RGM: [Seu RGM]
   Data da �ltima modifica��o: [Data da modifica��o]
*/
#include <io.h>        /* _findfirst(), _findnext(), _findclose() */
#include <locale.h>    /* setlocale() */
#include <stdio.h>     /* printf() */
#include <string.h>    /* strcmp() */
#include "funcoes.h"   /* Declara��es das fun��es */

/* Fun��o principal do programa */
int main(int argc, char *argv[]) 
{
    char diretorio[520] = "."; /* Diret�rio inicial */
    int incluir_arquivos = 0;  /* Flag para incluir arquivos */
    int usar_ascii = 0;        /* Flag para usar ASCII */
    int exibir_ajuda_flag = 0; /* Flag para exibir ajuda */
    int i;                     /* �ndice para loops */

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

    /* Verifica se o diret�rio especificado existe */
    if (_access(diretorio, 0) != 0) 
    {
        printf("Erro: O diret�rio especificado '%s' n�o existe ou n�o pode ser acessado.\n", diretorio);
        return 1;
    }

    /* Exibe a estrutura do diret�rio */
    printf("Estrutura do diret�rio: %s\n", diretorio);
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, 0);

    return 0;
}

