#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>


void buscar_arquivos(const char *diretorio, int incluir_arquivos, int usar_ascii, int *contador_pastas, int *contador_arquivos, int nivel) 
{
    struct _finddata_t dados_arquivo; 
    char caminho_completo[520];        
    char padrao_busca[520]; 
    char *simbolo;           
    long handle;                       
    int i;

    simbolo = usar_ascii ? "|-- " : "|-- "; /*Para ANSI, ambos s�o "|-- "*/ 

    /*Define o padr�o de busca para todos os arquivos e diret�rios no diret�rio atual*/ 
    sprintf(padrao_busca, "%s\\*.*", diretorio);

    /*Inicia a busca no diret�rio*/ 
    handle = _findfirst(padrao_busca, &dados_arquivo);

    if (handle == -1L) 
    {
        printf("Erro ao abrir diret�rio: %s (possivelmente sem permiss�o ou n�o existe)\n", diretorio);
        return;  
    }

    /*Alinha pastas e arquivos em sequ�ncia com indenta��o*/ 
    printf("Conte�do do diret�rio '%s':\n\n", diretorio);
    
    do 
    {
        /*Ignora os diret�rios "." e ".."*/ 
        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue;
        }

        /*Cria o caminho completo para o arquivo ou subdiret�rio*/ 
        sprintf(caminho_completo, "%s\\%s", diretorio, dados_arquivo.name);

        /*Imprime a indenta��o para simular a hierarquia*/ 
        for (i = 0; i < nivel; i++) 
        {
            printf("    ");
        }

        /*Se � um subdiret�rio, exibe, incrementa o contador e chama a fun��o recursivamente*/ 
        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            (*contador_pastas)++;
            printf("%s[DIR] %s\n", simbolo, dados_arquivo.name);

            /*Chamada recursiva para explorar a subpasta*/
            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, contador_pastas, contador_arquivos, nivel + 1);
        } 
        /*Se for um arquivo e a op��o incluir_arquivos est� ativada, exibe e incrementa o contador de arquivos*/ 
        else if (incluir_arquivos) 
        {  
            (*contador_arquivos)++;
            printf("%s[ARQ] %s\n", simbolo, dados_arquivo.name);
        }
    } while (_findnext(handle, &dados_arquivo) == 0);  

    _findclose(handle);  /*Fecha o manipulador de diret�rio*/ 

    /*Exibe o resumo final ao sair da recurs�o principal*/ 
    if (nivel == 0) 
    {
        printf("\nTotal de pastas: %d\n", *contador_pastas);
        if (incluir_arquivos) 
        {
            printf("Total de arquivos: %d\n", *contador_arquivos);
        }
    }
}

void exibir_ajuda() 
{
    printf("Uso: TREE++ [diretorio] [/A] [/F]\n");
    printf("Op��es:\n");
    printf("  [diretorio]  Especifica o caminho do diret�rio a ser listado.\n");
    printf("  /A           Usa caracteres ASCII para o layout gr�fico\n");
    printf("  /F           Exibe os nomes dos arquivos nos diret�rios\n");
    printf("  /?           Exibe esta tela de ajuda\n\n");
    printf("Exemplos:\n");
    printf("  TREE++ C:\\meu_diretorio /A /F  - Lista o conte�do do diret�rio 'C:\\meu_diretorio' com ASCII e inclui arquivos.\n");
    printf("  TREE++ /F                      - Lista o conte�do do diret�rio solicitado com arquivos inclu�dos.\n");
}
