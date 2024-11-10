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

    simbolo = usar_ascii ? "|-- " : "|-- "; /*Para ANSI, ambos são "|-- "*/ 

    /*Define o padrão de busca para todos os arquivos e diretórios no diretório atual*/ 
    sprintf(padrao_busca, "%s\\*.*", diretorio);

    /*Inicia a busca no diretório*/ 
    handle = _findfirst(padrao_busca, &dados_arquivo);

    if (handle == -1L) 
    {
        printf("Erro ao abrir diretório: %s (possivelmente sem permissão ou não existe)\n", diretorio);
        return;  
    }

    /*Alinha pastas e arquivos em sequência com indentação*/ 
    printf("Conteúdo do diretório '%s':\n\n", diretorio);
    
    do 
    {
        /*Ignora os diretórios "." e ".."*/ 
        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue;
        }

        /*Cria o caminho completo para o arquivo ou subdiretório*/ 
        sprintf(caminho_completo, "%s\\%s", diretorio, dados_arquivo.name);

        /*Imprime a indentação para simular a hierarquia*/ 
        for (i = 0; i < nivel; i++) 
        {
            printf("    ");
        }

        /*Se é um subdiretório, exibe, incrementa o contador e chama a função recursivamente*/ 
        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            (*contador_pastas)++;
            printf("%s[DIR] %s\n", simbolo, dados_arquivo.name);

            /*Chamada recursiva para explorar a subpasta*/
            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, contador_pastas, contador_arquivos, nivel + 1);
        } 
        /*Se for um arquivo e a opção incluir_arquivos está ativada, exibe e incrementa o contador de arquivos*/ 
        else if (incluir_arquivos) 
        {  
            (*contador_arquivos)++;
            printf("%s[ARQ] %s\n", simbolo, dados_arquivo.name);
        }
    } while (_findnext(handle, &dados_arquivo) == 0);  

    _findclose(handle);  /*Fecha o manipulador de diretório*/ 

    /*Exibe o resumo final ao sair da recursão principal*/ 
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
    printf("Opções:\n");
    printf("  [diretorio]  Especifica o caminho do diretório a ser listado.\n");
    printf("  /A           Usa caracteres ASCII para o layout gráfico\n");
    printf("  /F           Exibe os nomes dos arquivos nos diretórios\n");
    printf("  /?           Exibe esta tela de ajuda\n\n");
    printf("Exemplos:\n");
    printf("  TREE++ C:\\meu_diretorio /A /F  - Lista o conteúdo do diretório 'C:\\meu_diretorio' com ASCII e inclui arquivos.\n");
    printf("  TREE++ /F                      - Lista o conteúdo do diretório solicitado com arquivos incluídos.\n");
}
