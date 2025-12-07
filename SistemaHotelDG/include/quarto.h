#ifndef QUARTO_H
#define QUARTO_H

typedef struct {
    int numero;
    int qtdHospedes;
    float valorDiaria;
    char status[12]; // "ocupado" ou "desocupado"
} Quarto;

void menuQuartos();
void cadastrarQuarto();
void listarQuartos();

#endif
