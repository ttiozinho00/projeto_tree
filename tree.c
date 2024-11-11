/*
*metodo compilar codigo: gcc -o tree.exe tree.c funcoes.c -Wall -pedantic -Wextra -Werror
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

#include <io.h>        /* _findfirst(), _findnext(), _findclose()  */
#include <locale.h>    /* setlocale() */
#include <stdio.h>     /* printf() . */
#include <string.h>    /* strcmp() */
#include "funcoes.h"   /* Declarações das funções  */

/* Função principal do programa */
int main(int argc, char *argv[]) 
{
    char diretorio[520] = "."; /* Declara uma variável 'diretorio',  tamanho 520, inicializada com o valor "." que representa o diretório atual. */
    int contador_arquivos; /* Declara uma variável 'contador_arquivos', utilizada para contar o número de arquivos em um diretório. */
    int exibir_ajuda_flag; /* Declara uma variável 'exibir_ajuda_flag', utilizada como flag para controlar se a ajuda será exibida ao usuário. */
    int incluir_arquivos; /* Declara uma variável 'incluir_arquivos', utilizada para decidir se os arquivos devem ser incluídos na operação (1 para incluir, 0 para não). */
    int contador_pastas; /* Declara uma variável 'contador_pastas',  utilizada para contar o número de pastas em um diretório. */
    int usar_ascii; /* Declara uma variável 'usar_ascii', usada para controlar se a exibição deve ser feita com caracteres ASCII. */
    int i; /* Declara uma variável 'i', frequentemente usada como índice em loops de iteração. */


    incluir_arquivos = 0;      /* Inicializa a flag para incluir arquivos. */
    usar_ascii = 0;           /* Inicializa a flag para usar ASCII na exibição da estrutura. */
    contador_pastas = 0;      /* Inicializa o contador de pastas encontradas. */
    contador_arquivos = 0;    /* Inicializa o contador de arquivos encontrados. */
    exibir_ajuda_flag = 0;    /* Inicializa a flag para exibir a ajuda */

    setlocale(LC_CTYPE, "");  /* Configura a localidade do programa para garantir o suporte a caracteres especiais. */

    /* Processa os argumentos da linha de comando */
    for (i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "/?") == 0) 
        {
            exibir_ajuda_flag = 1; /* Se a opção /? for fornecida, marca para exibir a ajuda. */
        } 
        else if (strcmp(argv[i], "/A") == 0) 
        {
            if (usar_ascii) 
            {
                printf("Erro: A opção /A foi especificada mais de uma vez.\n");
                return 1;  /* Se a opção /A for fornecida mais de uma vez, exibe erro e encerra. */
            }
            usar_ascii = 1;   /* Ativa a opção de usar ASCII para exibir a estrutura de diretórios. */
        } 
        else if (strcmp(argv[i], "/F") == 0) 
        {
            if (incluir_arquivos) 
            {
                printf("Erro: A opção /F foi especificada mais de uma vez.\n");
                return 1;  /* Se a opção /F for fornecida mais de uma vez, exibe erro e encerra. */
            }
            incluir_arquivos = 1; /* Ativa a opção de incluir arquivos na exibição da estrutura de diretórios. */
        } 
        else 
        {
            strncpy(diretorio, argv[i], sizeof(diretorio) - 1);  /* Se o argumento não for uma opção, assume como caminho do diretório. */
        }
    }

    /* Exibe a ajuda se a opção /? foi especificada */ 
    if (exibir_ajuda_flag) 
    {
        exibir_ajuda();   /* Chama a função para exibir a ajuda. */
        return 0;          /* Encerra a execução após exibir a ajuda. */
    }

    /* Verifica se o diretório especificado existe */
    if (_access(diretorio, 0) != 0) 
    {
        printf("Erro: O diretório especificado '%s' não existe ou não pode ser acessado.\n", diretorio);
        return 1;  /* Se o diretório não existir ou não puder ser acessado, exibe erro e encerra. */
    }

    /* Exibe a estrutura do diretório atual e chama a função de busca com o nível inicial 0 */ 
    printf("\nEstrutura do diretório: %s\n", diretorio);
    buscar_arquivos(diretorio, incluir_arquivos, usar_ascii, &contador_pastas, &contador_arquivos, 0);

    /* Exibe o resumo final */ 
    printf("\nVerificação concluída.\n");
    printf("Total de pastas analisadas: %d\n", contador_pastas);
    printf("Total de arquivos analisados: %d\n", contador_arquivos);

    return 0;  /* Encerra o programa com sucesso. */
}
