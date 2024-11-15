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
int main(int argc, char const *argv[])
{
    char diretorio[520] = "."; /* Diret�rio inicial */
    int incluir_arquivos = 0;  /* Flag para incluir arquivos */
    int usar_ascii = 0;        /* Flag para usar ASCII */
    int exibir_ajuda_flag = 0; /* Flag para exibir ajuda */
    int i;                     /* �ndice para loops */

    /* Inicializa��o das vari�veis de controle */
    exibir_ajuda_flag = 0;    /* Flag para indicar se a ajuda deve ser exibida  */
    incluir_arquivos = 0;     /* Flag para indicar se arquivos devem ser inclu�dos na listagem */
    usar_ascii = 0;           /* Flag para definir o uso de caracteres ASCII na formata��o */

    setlocale(LC_ALL, ""); /* Configura a localidade para UTF-8 */

    /* Processa argumentos da linha de comando */
    for (i = 1; i < argc; i++)
    {
        /* Verifica se o argumento � "/?" (solicita��o de ajuda) */
        if (strcmp(argv[i], "/?") == 0) 
        {
            exibir_ajuda_flag = 1;  /* Ativa o indicador de exibi��o da ajuda */
        } 
        /* Verifica se o argumento � "/A" ou "/a" (usar modo ASCII e incluir arquivos na busca) */
        else if (strcmp(argv[i], "/A") == 0 || strcmp(argv[i], "/a") == 0) 
        {
            usar_ascii = 1;        /* Ativa a flag para uso de caracteres ASCII */
            incluir_arquivos = 1;  /* Ativa a flag para incluir arquivos na busca */
        } 
        /* Verifica se o argumento � "/F" (incluir arquivos na busca) */
        else if (strcmp(argv[i], "/F") == 0 || strcmp(argv[i], "/f") == 0) 
        {
            incluir_arquivos = 1;  /* Ativa a flag para incluir arquivos na busca */
        } 
        /* Se o argumento n�o for uma op��o, assume que � o diret�rio especificado */
        else 
        {
            strncpy(diretorio, argv[i], sizeof(diretorio) - 1);  /* Copia o argumento para a vari�vel 'diretorio' */
            diretorio[sizeof(diretorio) - 1] = '\0';             /* Garante que a string seja terminada com '\0' */
        }
    }
        

    /* Verifica se a ajuda foi solicitada */
    if (exibir_ajuda_flag) 
    {
        exibir_ajuda();  /* Chama a fun��o que exibe a ajuda ao usu�rio */
        return 0;        /* Encerra o programa ap�s exibir a ajuda */
    }

    /* Verifica se o diret�rio especificado existe */
    if (_access(diretorio, 0) != 0) 
    {
        printf("Erro: O diret�rio especificado '%s' n�o existe ou n�o pode ser acessado.\n", diretorio);
        return 1;  /* Encerra o programa com erro */
    }

    /* Exibe a estrutura do diret�rio */
    printf("Estrutura do diret�rio: %s\n", diretorio);

    /* Chama a fun��o para buscar arquivos no diret�rio */
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, 0);
    return 0;
}