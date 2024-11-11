#include <io.h>        /* _findfirst(), _findnext(), _findclose() */
#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* exit() */
#include <string.h>    /* strcmp() */
#include "funcoes.h"   /* Declarações das funções */

/* Função recursiva que busca arquivos e pastas em um diretório */
void buscar_arquivos(char *diretorio, int incluir_arquivos, int usar_ascii, int nivel) 
{
    struct _finddata_t dados_arquivo;  /* Estrutura para armazenar informações sobre arquivos e pastas */
    char caminho_completo[520];        /* Caminho completo do arquivo ou pasta */
    char padrao_busca[520];            /* Padrão de busca */
    char *simbolo = usar_ascii ? "|-- " : "└── "; /* Símbolo para exibição */
    long handle;
    int i;

    /* Define o padrão de busca */
    sprintf(padrao_busca, "%s\\*.*", diretorio);

    handle = _findfirst(padrao_busca, &dados_arquivo);
    if (handle == -1L) 
    {
        printf("Erro ao abrir o diretório: %s\n", diretorio);
        return;
    }

    /* Loop para exibir arquivos e pastas */
    do 
    {
        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue; /* Ignora "." e ".." */
        }

        /* Monta o caminho completo */
        sprintf(caminho_completo, "%s\\%s", diretorio, dados_arquivo.name);

        /* Exibe a hierarquia */
        for (i = 0; i < nivel; i++) 
        {
            printf("    ");
        }

        /* Verifica se é uma pasta */
        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            printf("%s[DIR] %s\n", simbolo, dados_arquivo.name);
            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, nivel + 1);
        } 
        else if (incluir_arquivos) 
        {
            printf("%s[ARQ] %s\n", simbolo, dados_arquivo.name);
        }
    } while (_findnext(handle, &dados_arquivo) == 0);

    _findclose(handle);
}

/* Função que exibe a ajuda do programa */
void exibir_ajuda() 
{
    printf("Uso: TREE++ [diretório] [/A] [/F]\n");
    printf("Opções:\n");
    printf("  [diretório]  Especifica o caminho do diretório a ser listado.\n");
    printf("  /A           Usa caracteres ASCII para o layout gráfico\n");
    printf("  /F           Exibe os nomes dos arquivos nos diretórios\n");
    printf("  /?           Exibe esta tela de ajuda\n\n");
    printf("Exemplos:\n");
    printf("TREE++ C:\\meu_diretório /A /F  - Lista o conteúdo do diretório 'C:\\meu_diretório' com ASCII e inclui arquivos.\n");
    printf("TREE++ /F - Lista o conteúdo do diretório solicitado com arquivos incluídos.\n");
}

