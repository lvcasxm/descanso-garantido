#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct {
    int codigo;
    char nome[50];
    char telefone[20];
    char cargo[30];
    float salario;
} Funcionario;

void cadastrarFuncionario();
void pesquisarFuncionario();
void menuFuncionarios();
void listarFuncionarios();
void excluirFuncionario();

#endif 
