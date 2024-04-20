#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct {
    float X;
    float Y;
} Ponto;

float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    return fabs((A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y)) / 2.0);
}

int main() {
    FILE *arquivoLeitura;
    Ponto *vertices;
    int numVertices;
    float areaTotalPoligono = 0.0;

    arquivoLeitura = fopen("dadosPoligono.txt", "r");
    if (arquivoLeitura == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivoLeitura, "%d", &numVertices);
    vertices = (Ponto *)malloc(numVertices * sizeof(Ponto));
    if (vertices == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    for (int i = 0; i < numVertices; i++) {
        fscanf(arquivoLeitura, "%f %f", &vertices[i].X, &vertices[i].Y);
    }
    for (int i = 1; i < numVertices - 1; i++) {
        areaTotalPoligono = areaTotalPoligono + AreaTriangulo(vertices[0], vertices[i], vertices[i + 1]);
    }

    printf("A area do poligono e %.2f\n", areaTotalPoligono);

    free(vertices);
    fclose(arquivoLeitura);

    return 0;
}
