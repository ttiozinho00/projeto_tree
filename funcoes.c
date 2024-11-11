/* funcoes.c */
#include <io.h>        /* _findfirst(), _findnext(), _findclose() para busca de arquivos e diret�rios */
#include <stdio.h>     /* printf() para exibir informa��es na tela */
#include <stdlib.h>    /* exit() para encerrar o programa em caso de erro */
#include <string.h>    /* strcmp() para comparar strings */
#include "funcoes.h"   /* Declara��es das fun��es definidas neste arquivo */

/* Fun��o recursiva que busca arquivos e pastas em um diret�rio */
void buscar_arquivos(char *diretorio, int incluir_arquivos, int usar_ascii, int nivel) 
{
    struct _finddata_t dados_arquivo;  /* Estrutura que armazena informa��es sobre arquivos e pastas */
    char caminho_completo[520];        /* Armazena o caminho completo do arquivo ou pasta */
    char padrao_busca[520];            /* Padr�o de busca  */
    char *simbolo = usar_ascii ? "\++ " : "|___"; /* Define o s�mbolo usado para mostrar a hierarquia */

    long handle;  /* Vari�vel para armazenar o identificador da busca (_findfirst retorna um handle) */
    int i;        /* Vari�vel de controle para loops */

    /* Define o padr�o de busca usando o diret�rio informado */
    sprintf(padrao_busca, "%s\\*.*", diretorio);

    /* Inicia a busca no diret�rio usando o padr�o definido */
    handle = _findfirst(padrao_busca, &dados_arquivo);
    if (handle == -1L) 
    {
        /* Verifica se houve erro ao abrir o diret�rio */
        printf("Erro ao abrir o diret�rio: %s\n", diretorio);
        return; /* Sai da fun��o se o diret�rio n�o puder ser aberto */
    }

    /* Loop para listar arquivos e pastas encontrados */
    do 
    {
        /* Verifica se o arquivo � "." ou "..", que representam o diret�rio atual e o pai */
        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue; /* Ignora esses diret�rios especiais */
        }

        /* Constr�i o caminho completo do arquivo ou pasta */
        sprintf(caminho_completo, "%s\\%s", diretorio, dados_arquivo.name);

        /* Exibe a indenta��o para representar a hierarquia de diret�rios */
        for (i = 0; i < nivel; i++) 
        {
            printf("    ");
        }

        /* Verifica se � uma pasta */
        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            /* Exibe o nome da pasta com o s�mbolo de hierarquia */
            printf("%s %s\n", simbolo, dados_arquivo.name);
            /* Chama a fun��o recursivamente para listar o conte�do da pasta */
            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, nivel + 1);
        } 
        else if (incluir_arquivos) 
        {
            /* Exibe o nome do arquivo se a op��o de incluir arquivos estiver ativada */
            printf("%s %s\n", simbolo, dados_arquivo.name);
        }
    } while (_findnext(handle, &dados_arquivo) == 0); /* Continua listando os pr�ximos arquivos at� n�o haver mais */

    /* Fecha a busca para liberar recursos */
    _findclose(handle);
}

/* Fun��o que exibe a ajuda do programa */
void exibir_ajuda() 
{
    /* Exibe a sintaxe de uso e as op��es dispon�veis */
    printf("Uso: TREE++ [diret�rio] [/A] [/F]\n");
    printf("Op��es:\n");
    printf("  [diret�rio]  Especifica o caminho do diret�rio a ser listado.\n");
    printf("  /A           Usa caracteres ASCII para o layout gr�fico\n");
    printf("  /F           Exibe os nomes dos arquivos nos diret�rios\n");
    printf("  /?           Exibe esta tela de ajuda\n\n");

    /* Exemplos de como usar o programa */
    printf("Exemplos:\n");
    printf("TREE++ C:\\meu_diret�rio /A /F  - Lista o conte�do do diret�rio 'C:\\meu_diret�rio' com ASCII e inclui arquivos.\n");
    printf("TREE++ /F - Lista o conte�do do diret�rio solicitado com arquivos inclu�dos.\n");
}