#include <windows.h>  /* Para uso de funções do Windows, como GetConsoleCP() e SetConsoleCP() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "funcoes.h"

/* Função recursiva que busca arquivos e pastas em um diretório */
void buscar_arquivos(char *diretorio, int incluir_arquivos, int usar_ascii, int nivel) 
{
    struct _finddata_t dados_arquivo;  /* Estrutura que armazena informações sobre arquivos e pastas */
    char caminho_completo[520];        /* Armazena o caminho completo do arquivo ou pasta */
    char padrao_busca[520];            /* Padrão de busca  */
    char simbolo[5];                   /* Define o símbolo usado para mostrar a hierarquia */

    long handle;  /* Variável para armazenar o identificador da busca (_findfirst retorna um handle) */
    int i;        /* Variável de controle para loops */
    CONSOLE_SCREEN_BUFFER_INFO csbi;  /* Para armazenar informações do console */

    /* Obtém informações do console para verificar o código de página (CP) atual */
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    /* Verifica se deve usar ASCII ou caracteres gráficos completos */
    if (usar_ascii) 
    {
        strcpy(simbolo, "/++ ");  /* Define o símbolo ASCII */
    }
    else 
    {
        /* Utiliza caracteres gráficos para formar a árvore */
        strcpy(simbolo, "|   ");
    }

    /* Define o padrão de busca usando o diretório informado */
    snprintf(padrao_busca, sizeof(padrao_busca), "%s\\*.*", diretorio);  /* Utiliza snprintf para evitar overflow */

    /* Inicia a busca no diretório usando o padrão definido */
    handle = _findfirst(padrao_busca, &dados_arquivo);
    if (handle == -1L) 
    {
        /* Verifica se houve erro ao abrir o diretório */
        printf("Erro ao abrir o diretório: %s\n", diretorio);
        return; /* Sai da função se o diretório não puder ser aberto */
    }

    /* Loop para listar arquivos e pastas encontrados */
    do 
    {
        /* Verifica se o arquivo é "." ou "..", que representam o diretório atual e o pai */
        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue; /* Ignora esses diretórios especiais */
        }

        /* Constrói o caminho completo do arquivo ou pasta */
        snprintf(caminho_completo, sizeof(caminho_completo), "%s\\%s", diretorio, dados_arquivo.name);

        /* Exibe a indentação para representar a hierarquia de diretórios */
        for (i = 0; i < nivel; i++) 
        {
            printf("    ");
        }

        /* Verifica se é uma pasta */
        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            /* Exibe o nome da pasta com o símbolo de hierarquia */
            printf("%s └── %s\n", simbolo, dados_arquivo.name);
            /* Chama a função recursivamente para listar o conteúdo da pasta */
            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, nivel + 1);
        } 
        else if (incluir_arquivos) 
        {
            /* Exibe o nome do arquivo se a opção de incluir arquivos estiver ativada */
            printf("%s └── %s\n", simbolo, dados_arquivo.name);
        }
    } while (_findnext(handle, &dados_arquivo) == 0); /* Continua listando os próximos arquivos até não haver mais */

    /* Fecha a busca para liberar recursos */
    _findclose(handle);
}

/* Função que exibe a ajuda do programa */
void exibir_ajuda() 
{
    /* Exibe a sintaxe de uso e as opções disponíveis */
    printf("Uso: TREE++ [diretório] [/A] [/F]\n");
    printf("Opções:\n");
    printf("  [diretório]  Especifica o caminho do diretório a ser listado.\n");
    printf("  /A           Usa caracteres ASCII para o layout gráfico\n");
    printf("  /F           Exibe os nomes dos arquivos nos diretórios\n");
    printf("  /?           Exibe esta tela de ajuda\n\n");

    /* Exemplos de como usar o programa */
    printf("Exemplos:\n");
    printf("TREE++ C:\\meu_diretório /A /F  - Lista o conteúdo do diretório 'C:\\meu_diretório' com ASCII e inclui arquivos.\n");
    printf("TREE++ /F - Lista o conteúdo do diretório solicitado com arquivos incluídos.\n");
}
