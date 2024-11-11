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
int main(int argc, char const *argv[])
{
    char diretorio[520] = "."; /* Diretório inicial */
    int incluir_arquivos = 0;  /* Flag para incluir arquivos */
    int usar_ascii = 0;        /* Flag para usar ASCII */
    int exibir_ajuda_flag = 0; /* Flag para exibir ajuda */
    int i;                     /* Índice para loops */

    /* Inicialização das variáveis de controle */
    exibir_ajuda_flag = 0;    /* Flag para indicar se a ajuda deve ser exibida  */
    incluir_arquivos = 0;     /* Flag para indicar se arquivos devem ser incluídos na listagem */
    usar_ascii = 0;           /* Flag para definir o uso de caracteres ASCII na formatação */

    setlocale(LC_ALL, ""); /* Configura a localidade para UTF-8 */

    /* Processa argumentos da linha de comando */
    for (i = 1; i < argc; i++)
    {
        /* Verifica se o argumento é "/?" (solicitação de ajuda) */
        if (strcmp(argv[i], "/?") == 0) 
        {
            exibir_ajuda_flag = 1;  /* Ativa o indicador de exibição da ajuda */
        } 
        /* Verifica se o argumento é "/A" ou "/a" (usar modo ASCII e incluir arquivos na busca) */
        else if (strcmp(argv[i], "/A") == 0 || strcmp(argv[i], "/a") == 0) 
        {
            usar_ascii = 1;        /* Ativa a flag para uso de caracteres ASCII */
            incluir_arquivos = 1;  /* Ativa a flag para incluir arquivos na busca */
        } 
        /* Verifica se o argumento é "/F" (incluir arquivos na busca) */
        else if (strcmp(argv[i], "/F") == 0 || strcmp(argv[i], "/f") == 0) 
        {
            incluir_arquivos = 1;  /* Ativa a flag para incluir arquivos na busca */
        } 
        /* Se o argumento não for uma opção, assume que é o diretório especificado */
        else 
        {
            strncpy(diretorio, argv[i], sizeof(diretorio) - 1);  /* Copia o argumento para a variável 'diretorio' */
            diretorio[sizeof(diretorio) - 1] = '\0';             /* Garante que a string seja terminada com '\0' */
        }
    }
        

    /* Verifica se a ajuda foi solicitada */
    if (exibir_ajuda_flag) 
    {
        exibir_ajuda();  /* Chama a função que exibe a ajuda ao usuário */
        return 0;        /* Encerra o programa após exibir a ajuda */
    }

    /* Verifica se o diretório especificado existe */
    if (_access(diretorio, 0) != 0) 
    {
        printf("Erro: O diretório especificado '%s' não existe ou não pode ser acessado.\n", diretorio);
        return 1;  /* Encerra o programa com erro */
    }

    /* Exibe a estrutura do diretório */
    printf("Estrutura do diretório: %s\n", diretorio);

    /* Chama a função para buscar arquivos no diretório */
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, 0);
    return 0;
}