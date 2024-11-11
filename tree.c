/*
*metodo compilar codigo: gcc -o tree.exe tree.c funcoes.c -Wall -pedantic -Wextra -Werror
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

#include <io.h>        /* _findfirst(), _findnext(), _findclose()  */
#include <locale.h>    /* setlocale() */
#include <stdio.h>     /* printf() . */
#include <string.h>    /* strcmp() */
#include "funcoes.h"   /* Declara��es das fun��es  */

/* Fun��o principal do programa */
int main(int argc, char *argv[]) 
{
    char diretorio[520] = "."; /* Declara uma vari�vel 'diretorio',  tamanho 520, inicializada com o valor "." que representa o diret�rio atual. */
    int contador_arquivos; /* Declara uma vari�vel 'contador_arquivos', utilizada para contar o n�mero de arquivos em um diret�rio. */
    int exibir_ajuda_flag; /* Declara uma vari�vel 'exibir_ajuda_flag', utilizada como flag para controlar se a ajuda ser� exibida ao usu�rio. */
    int incluir_arquivos; /* Declara uma vari�vel 'incluir_arquivos', utilizada para decidir se os arquivos devem ser inclu�dos na opera��o (1 para incluir, 0 para n�o). */
    int contador_pastas; /* Declara uma vari�vel 'contador_pastas',  utilizada para contar o n�mero de pastas em um diret�rio. */
    int usar_ascii; /* Declara uma vari�vel 'usar_ascii', usada para controlar se a exibi��o deve ser feita com caracteres ASCII. */
    int i; /* Declara uma vari�vel 'i', frequentemente usada como �ndice em loops de itera��o. */


    incluir_arquivos = 0;      /* Inicializa a flag para incluir arquivos. */
    usar_ascii = 0;           /* Inicializa a flag para usar ASCII na exibi��o da estrutura. */
    contador_pastas = 0;      /* Inicializa o contador de pastas encontradas. */
    contador_arquivos = 0;    /* Inicializa o contador de arquivos encontrados. */
    exibir_ajuda_flag = 0;    /* Inicializa a flag para exibir a ajuda */

   setlocale(LC_ALL, ""); /* Configura a localidade para UTF-8 */

    /* Processa cada argumento da linha de comando */
    for (i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "/?") == 0) /* Verifica se o argumento � "/?" para exibir ajuda */
        {
            exibir_ajuda_flag = 1; /* Seta a flag para exibir a ajuda */
        } 
        else if (strcmp(argv[i], "/A") == 0) /* Verifica se o argumento � "/A" para layout ASCII */
        {
            if (usar_ascii) /* Verifica se "/A" j� foi definido anteriormente */
            {
                printf("Erro: A op��o /A foi especificada mais de uma vez.\n");
                return 1; /* Sai do programa com erro */
            }
            usar_ascii = 1; /* Ativa o layout ASCII */
            incluir_arquivos = 1; /* Ativa a inclus�o de arquivos */
        } 
        else if (strcmp(argv[i], "/F") == 0) /* Verifica se o argumento � "/F" para incluir arquivos */
        {
            if (incluir_arquivos) /* Verifica se "/F" j� foi definido anteriormente */
            {
                printf("Erro: A op��o /F foi especificada mais de uma vez.\n");
                return 1; /* Sai do programa com erro */
            }
            incluir_arquivos = 1; /* Ativa a inclus�o de arquivos */
        } 
        else 
        {
            strncpy(diretorio, argv[i], sizeof(diretorio) - 1);  /* Assume que o argumento � um diret�rio */ 
        }
    }

    /* Verifica se a ajuda foi solicitada */
    if (exibir_ajuda_flag) 
    {
        exibir_ajuda(); /* Exibe a ajuda */
        return 0;       /* Sai do programa */
    }

    /* Verifica se o diret�rio especificado existe */ 
    if (_access(diretorio, 0) != 0) 
    {
        printf("Erro: O diret�rio especificado '%s' n�o existe ou n�o pode ser acessado.\n", diretorio);
        return 1; /* Sai do programa com erro */
    }

    /* Exibe a estrutura do diret�rio atual e inicia a busca */
    printf("Estrutura do diret�rio: %s\n", diretorio);
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, &contador_pastas, &contador_arquivos, 0);

    /* Exibe o resumo final */
    printf("\nVerifica��o conclu�da.\n");
    printf("Total de pastas analisadas: %d\n", contador_pastas);
    printf("Total de arquivos analisados: %d\n", contador_arquivos);

    return 0;  /* Encerra o programa com sucesso. */
}
