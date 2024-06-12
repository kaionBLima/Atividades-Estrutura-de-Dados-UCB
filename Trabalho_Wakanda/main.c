#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"


int main() {
    const char *nomeArquivo = "cidadesVizinhasWakanda.txt";

    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada) {
        printf("Comprimento total da estrada: %d\n", estrada->T);
        for (int i = 0; i < estrada->N; i++) {
            printf("Cidade: %s, Distancia: %d\n", estrada->C[i].Nome, estrada->C[i].Posicao);
        }
        free(estrada->C);
        free(estrada);
    }

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    printf("Menor vizinhanca: %.2f\n", menorVizinhanca);

    char *cidadeMenor = cidadeMenorVizinhanca(nomeArquivo);
    if (cidadeMenor) {
        printf("Cidade com menor vizinhanca: %s\n", cidadeMenor);
        free(cidadeMenor);
    }

    return 0;
}