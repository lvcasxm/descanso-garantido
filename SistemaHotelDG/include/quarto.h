#ifndef QUARTO_H
#define QUARTO_H

typedef struct {
    int numero;
    int qtdHospedes;
    float valorDiaria;
    char status[12];
} Quarto;

void menuQuartos();
void cadastrarQuarto();
void listarQuartos();

#endif
