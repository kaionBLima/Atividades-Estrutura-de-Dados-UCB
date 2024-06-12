#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ordenarCidades(Cidade *cidades, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (cidades[j].Posicao > cidades[j + 1].Posicao) {
                Cidade temp = cidades[j];
                cidades[j] = cidades[j + 1];
                cidades[j + 1] = temp;
            }
        }
    }
}

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        perror("Erro ao alocar memória para Estrada");
        fclose(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d", &(estrada->T));
    fscanf(arquivo, "%d", &(estrada->N));
    fgetc(arquivo); // Consome o caractere de nova linha após o número de cidades

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        perror("Erro ao alocar memória para as cidades");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    char linha[512];
    for (int i = 0; i < estrada->N; i++) {
        fgets(linha, sizeof(linha), arquivo);
        sscanf(linha, "%d %[^\n]", &(estrada->C[i].Posicao), estrada->C[i].Nome);
    }

    ordenarCidades(estrada->C, estrada->N);  // utilizado para ordenar as cidades

    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1;

    double menorVizinhanca = estrada->T; // Inicializa com o comprimento total da estrada
    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhancaAtual = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhancaAtual < menorVizinhanca) {
            menorVizinhanca = vizinhancaAtual;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhanca = estrada->T; // Inicializa com o comprimento total da estrada
    char *cidadeMenor = (char *)malloc(256 * sizeof(char));
    if (!cidadeMenor) {
        perror("Erro ao alocar memória para cidadeMenor");
        free(estrada->C);
        free(estrada);
        return NULL;
    }
    double vizinhancaAtual;
    for (int i = 0; i < estrada->N - 1; i++) {
        vizinhancaAtual = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhancaAtual < menorVizinhanca) {
            menorVizinhanca = vizinhancaAtual;
            strcpy(cidadeMenor, estrada->C[i].Nome);
        }
    }

    // Verificar último trecho da estrada
    vizinhancaAtual = (estrada->T - estrada->C[estrada->N - 1].Posicao) / 2.0;
    if (vizinhancaAtual < menorVizinhanca) {
        menorVizinhanca = vizinhancaAtual;
        strcpy(cidadeMenor, estrada->C[estrada->N - 1].Nome);
    }

    free(estrada->C);
    free(estrada);
    return cidadeMenor;
}