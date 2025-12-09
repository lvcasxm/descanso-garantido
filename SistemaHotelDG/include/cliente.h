#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
} Cliente;

void cadastrarCliente();
void pesquisarCliente();
void menuClientes();
void listarClientes();
void excluirCliente();

#endif