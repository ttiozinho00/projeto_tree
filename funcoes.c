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
    long handle;                       
    int i;

    sprintf(padrao_busca, "%s\\*.*", diretorio);

    handle = _findfirst(padrao_busca, &dados_arquivo);

    if (handle == -1L) 
    {
        printf("Erro ao abrir diretório: %s (possivelmente sem permissão)\n", diretorio);
        return;  
    }

    do 
    {

        if (strcmp(dados_arquivo.name, ".") == 0 || strcmp(dados_arquivo.name, "..") == 0) 
        {
            continue;
        }

        sprintf(caminho_completo, "%s\\%s", diretorio, dados_arquivo.name);

        for (i = 0; i < nivel; i++) 
        {
            if (usar_ascii) 
            {
                printf("|   ");
            } 
            else 
            {
                printf("|   ");  
            }
        }

        
        if (dados_arquivo.attrib & _A_SUBDIR) 
        {
            (*contador_pastas)++;
            if (usar_ascii) 
            {
                printf("+-- %s\n", dados_arquivo.name);
            } 
            else 
            {
                printf("+-- %s\n", dados_arquivo.name);  
            }

            
            buscar_arquivos(caminho_completo, incluir_arquivos, usar_ascii, contador_pastas, contador_arquivos, nivel + 1);
        } 

        else if (incluir_arquivos) 
        {  
            (*contador_arquivos)++;
            if (usar_ascii) 
            {
                printf("+-- %s\n", dados_arquivo.name);
            } 
            else 
            {
                printf("+-- %s\n", dados_arquivo.name); 
            }
        }
    } while (_findnext(handle, &dados_arquivo) == 0);  

    _findclose(handle);  
}

void exibir_ajuda() 
{
    printf("Uso: TREE++ [diretorio] [/A] [/F]\n");
    printf("Opções:\n");
    printf("  /A   Usa caracteres ASCII para o layout gráfico\n");
    printf("  /F   Exibe os nomes dos arquivos nos diretórios\n");
    printf("  /?   Exibe esta tela de ajuda\n");
}