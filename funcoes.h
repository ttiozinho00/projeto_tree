#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>

/* Declarações das funções */
void buscar_arquivos(const char *diretorio, int incluir_arquivos, int usar_ascii, int *contador_pastas, int *contador_arquivos, int nivel); 
void exibir_ajuda();

#endif 