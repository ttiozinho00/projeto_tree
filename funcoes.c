#include <io.h>        /* _findfirst(), _findnext(), _findclose()  */
#include <stdio.h>     /* printf()  */
#include <stdlib.h>    /* exit()  */
#include <string.h>    /* strcmp()  */
#include "funcoes.h"   /* Declara��es das fun��es  */

/* Fun��o recursiva que busca arquivos e pastas em um diret�rio */
void buscar_arquivos(char *diretorio, int incluir_arquivos, int usar_ascii, int *contador_pastas, int *contador_arquivos, int nivel) 
{
    struct _finddata_t dados_arquivo;  /* Estrutura que armazena informa��es sobre arquivos e diret�rios encontrados. */
    char caminho_completo[520];        /* Vari�vel para armazenar o caminho completo do arquivo ou diret�rio. */
    char padrao_busca[520];            /* Padr�o para busca de arquivos e pastas. */
    char *simbolo;                    /* Vari�vel para armazenar o s�mbolo a ser usado na exibi��o da estrutura. */
    long handle;                      /* Identificador de busca para a fun��o _findfirst() e _findnext(). */
    int i;

    simbolo = usar_ascii ? "|-- " : "|-- ";  /* Define o s�mbolo que ser� usado na exibi��o, dependendo da op��o ASCII. */

    sprintf(padrao_busca, "%s\\*.*", diretorio);  /* Define o padr�o de busca para arquivos e pastas no diret�rio. */

    handle = _findfirst(padrao_busca, &dados_arquivo);  /* Inicia a busca no diret�rio. */

    if (handle == -1L) 
    {
        printf("Erro ao abrir diret�rio: %s (possivelmente sem permiss�o ou n�o existe)\n", diretorio);
        return;  /* Se n�o for poss�vel abrir o diret�rio, exibe erro e retorna. */
    }

    printf("Conte�do do diret�rio '%s':\n\n", diretorio);  /* Exibe o t�tulo para o conte�do do diret�rio. */

    do 
    {
        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue;  /* Ignora os diret�rios "." e ".." */
        }

        sprintf(caminho_completo, "%s\\%s", diretorio, dados_arquivo.name);  /* Cria o caminho completo do arquivo ou diret�rio. */
        
        for (i = 0; i < nivel; i++) 
        {
            printf("    ");  /* Exibe a indenta��o para simular a hierarquia de pastas. */
        }

        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            (*contador_pastas)++;  /* Incrementa o contador de pastas. */
            printf("%s[DIR] %s\n", simbolo, dados_arquivo.name);

            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, contador_pastas, contador_arquivos, nivel + 1);  /* Chama recursivamente para subdiret�rios. */
        } 
        else if (incluir_arquivos) 
        {
            (*contador_arquivos)++;  /* Incrementa o contador de arquivos. */
            printf("%s[ARQ] %s\n", simbolo, dados_arquivo.name);  /* Exibe o arquivo encontrado. */
        }
    } while (_findnext(handle, &dados_arquivo) == 0);  /* Continua a busca enquanto houver arquivos e pastas. */
    
    _findclose(handle);  /* Fecha o identificador de busca do diret�rio. */
}

/* Fun��o que exibe a ajuda do programa */
void exibir_ajuda() 
{
    printf("Uso: TREE++ [diretorio] [/A] [/F]\n");
    printf("Op��es:\n");
    printf("  [diretorio]  Especifica o caminho do diret�rio a ser listado.\n");
    printf("  /A           Usa caracteres ASCII para o layout gr�fico\n");
    printf("  /F           Exibe os nomes dos arquivos nos diret�rios\n");
    printf("  /?           Exibe esta tela de ajuda\n\n");
    printf("\nExemplos:\n");
    printf("TREE++ C:\\meu_diretorio /A /F  - Lista o conte�do do diret�rio 'C:\\meu_diretorio' com ASCII e inclui arquivos.\n");
    printf("TREE++ /F - Lista o conte�do do diret�rio solicitado com arquivos inclu�dos.\n");
}
