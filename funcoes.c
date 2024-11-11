#include <io.h>        /* _findfirst(), _findnext(), _findclose()  */
#include <stdio.h>     /* printf()  */
#include <stdlib.h>    /* exit()  */
#include <string.h>    /* strcmp()  */
#include "funcoes.h"   /* Declarações das funções  */

/* Função recursiva que busca arquivos e pastas em um diretório */
void buscar_arquivos(char *diretorio, int incluir_arquivos, int usar_ascii, int *contador_pastas, int *contador_arquivos, int nivel) 
{
    struct _finddata_t dados_arquivo;  /* Estrutura que armazena informações sobre arquivos e diretórios encontrados. */
    char caminho_completo[520];        /* Variável para armazenar o caminho completo do arquivo ou diretório. */
    char padrao_busca[520];            /* Padrão para busca de arquivos e pastas. */
    char *simbolo;                    /* Variável para armazenar o símbolo a ser usado na exibição da estrutura. */
    long handle;                      /* Identificador de busca para a função _findfirst() e _findnext(). */
    int i;

    simbolo = usar_ascii ? "|-- " : "|-- ";  /* Define o símbolo que será usado na exibição, dependendo da opção ASCII. */

    sprintf(padrao_busca, "%s\\*.*", diretorio);  /* Define o padrão de busca para arquivos e pastas no diretório. */

    handle = _findfirst(padrao_busca, &dados_arquivo);  /* Inicia a busca no diretório. */

    if (handle == -1L) 
    {
        printf("Erro ao abrir diretório: %s (possivelmente sem permissão ou não existe)\n", diretorio);
        return;  /* Se não for possível abrir o diretório, exibe erro e retorna. */
    }

    printf("Conteúdo do diretório '%s':\n\n", diretorio);  /* Exibe o título para o conteúdo do diretório. */

    do 
    {
        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue;  /* Ignora os diretórios "." e ".." */
        }

        sprintf(caminho_completo, "%s\\%s", diretorio, dados_arquivo.name);  /* Cria o caminho completo do arquivo ou diretório. */
        
        for (i = 0; i < nivel; i++) 
        {
            printf("    ");  /* Exibe a indentação para simular a hierarquia de pastas. */
        }

        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            (*contador_pastas)++;  /* Incrementa o contador de pastas. */
            printf("%s[DIR] %s\n", simbolo, dados_arquivo.name);

            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, contador_pastas, contador_arquivos, nivel + 1);  /* Chama recursivamente para subdiretórios. */
        } 
        else if (incluir_arquivos) 
        {
            (*contador_arquivos)++;  /* Incrementa o contador de arquivos. */
            printf("%s[ARQ] %s\n", simbolo, dados_arquivo.name);  /* Exibe o arquivo encontrado. */
        }
    } while (_findnext(handle, &dados_arquivo) == 0);  /* Continua a busca enquanto houver arquivos e pastas. */
    
    _findclose(handle);  /* Fecha o identificador de busca do diretório. */
}

/* Função que exibe a ajuda do programa */
void exibir_ajuda() 
{
    printf("Uso: TREE++ [diretorio] [/A] [/F]\n");
    printf("Opções:\n");
    printf("  [diretorio]  Especifica o caminho do diretório a ser listado.\n");
    printf("  /A           Usa caracteres ASCII para o layout gráfico\n");
    printf("  /F           Exibe os nomes dos arquivos nos diretórios\n");
    printf("  /?           Exibe esta tela de ajuda\n\n");
    printf("\nExemplos:\n");
    printf("TREE++ C:\\meu_diretorio /A /F  - Lista o conteúdo do diretório 'C:\\meu_diretorio' com ASCII e inclui arquivos.\n");
    printf("TREE++ /F - Lista o conteúdo do diretório solicitado com arquivos incluídos.\n");
}
