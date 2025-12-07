#ifndef ESTADIA_H
#define ESTADIA_H

typedef struct {
    int codigoEstadia;
    char dataEntrada[11];
    char dataSaida[11];
    int qtdDiarias;
    int codigoCliente;
    int numeroQuarto;
} Estadia;

void menuEstadias();
void cadastrarEstadia();
void finalizarEstadia(); // Função para dar baixa
void listarEstadiasPorCliente();

#endif
