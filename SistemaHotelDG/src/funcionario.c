#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/funcionario.h"

#define ARQUIVO_FUNCIONARIOS "data/funcionarios.dat"

int validarLetras(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) return 0;
    }
    return 1;
}

int gerarCodigoFuncionario() {
    FILE *f = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    Funcionario func;
    int maior = 0;
    if (f) {
        while (fread(&func, sizeof(Funcionario), 1, f)) {
            if (func.codigo > maior) maior = func.codigo;
        }
        fclose(f);
    }
    return maior + 1;
}

void listarFuncionarios() {
    FILE *f = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (!f) {
        printf("\n[!] Nenhum funcionario cadastrado no momento.\n");
        return;
    }

    Funcionario f1;
    printf("\n=== LISTA DE FUNCIONARIOS DISPONIVEIS ===\n");
    printf("%-10s %-30s %-20s\n", "ID", "NOME", "CARGO");
    printf("------------------------------------------------------------\n");
    while (fread(&f1, sizeof(Funcionario), 1, f)) {
        printf("%-10d %-30s %-20s\n", f1.codigo, f1.nome, f1.cargo);
    }
    fclose(f);
    printf("------------------------------------------------------------\n");
}

void cadastrarFuncionario() {
    Funcionario f;
    f.codigo = gerarCodigoFuncionario();

    printf("\n=== CADASTRAR FUNCIONARIO (ID: %d) ===\n", f.codigo);
    
    do {
        printf("Nome: ");
        fflush(stdin);
        fgets(f.nome, 50, stdin);
        f.nome[strcspn(f.nome, "\n")] = 0;
    } while (!validarLetras(f.nome));

    printf("Telefone: ");
    scanf("%s", f.telefone);

    do {
        printf("Cargo: ");
        fflush(stdin);
        fgets(f.cargo, 30, stdin);
        f.cargo[strcspn(f.cargo, "\n")] = 0;
    } while (!validarLetras(f.cargo));

    printf("Salario: ");
    scanf("%f", &f.salario);

    FILE *file = fopen(ARQUIVO_FUNCIONARIOS, "ab");
    if (file) {
        fwrite(&f, sizeof(Funcionario), 1, file);
        fclose(file);
        printf("\n[+] Funcionario cadastrado com sucesso!\n");
    }
}

void pesquisarFuncionario() {
    listarFuncionarios();
    FILE *f = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (!f) return;

    int opcao;
    printf("\nPesquisar por:\n1 - ID\n2 - Nome\nEscolha: ");
    if (scanf("%d", &opcao) != 1) {
        printf("\nEntrada invalida!\n");
        fflush(stdin);
        fclose(f);
        return;
    }

    Funcionario func;
    int achou = 0;

    if (opcao == 1) {
        int cod;
        printf("Digite o ID: ");
        scanf("%d", &cod);
        while (fread(&func, sizeof(Funcionario), 1, f)) {
            if (func.codigo == cod) { achou = 1; break; }
        }
    } else if (opcao == 2) {
        char nomeBusca[50];
        printf("Digite o nome: ");
        fflush(stdin);
        fgets(nomeBusca, 50, stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = 0;
        while (fread(&func, sizeof(Funcionario), 1, f)) {
            if (stricmp(func.nome, nomeBusca) == 0) { achou = 1; break; }
        }
    } else {
        printf("\nOpcao inexistente!\n");
        fclose(f);
        return;
    }

    fclose(f);

    if (achou) {
        printf("\n=== FUNCIONARIO ENCONTRADO ===\n");
        printf("ID:      %d\n", func.codigo);
        printf("Nome:    %s\n", func.nome);
        printf("Cargo:   %s\n", func.cargo);
        printf("Salario: R$ %.2f\n", func.salario);
        printf("Tel:     %s\n", func.telefone);
    } else {
        printf("\nFuncionario nao encontrado no sistema.\n");
    }
}
void excluirFuncionario() {
    listarFuncionarios();
    int cod;
    printf("\nDigite o ID para EXCLUIR: ");
    if (scanf("%d", &cod) != 1) {
        fflush(stdin);
        return;
    }

    FILE *f = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    FILE *temp = fopen("data/temp_func.dat", "wb");
    if (!f) return;

    Funcionario func;
    int encontrado = 0;
    while (fread(&func, sizeof(Funcionario), 1, f)) {
        if (func.codigo == cod) encontrado = 1;
        else fwrite(&func, sizeof(Funcionario), 1, temp);
    }
    fclose(f); fclose(temp);

    remove(ARQUIVO_FUNCIONARIOS);
    rename("data/temp_func.dat", ARQUIVO_FUNCIONARIOS);

    if (encontrado) printf("\n[+] Funcionario removido com sucesso.\n");
    else printf("\n[!] ID %d nao encontrado.\n", cod);
}

void menuFuncionarios() {
    int op;
    do {
        printf("\n=== MENU FUNCIONARIOS ===\n");
        printf("1 - Cadastrar\n");
        printf("2 - Pesquisar\n");
        printf("3 - Excluir\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        
        if (scanf("%d", &op) != 1) {
            printf("\n[!] Opcao invalida!\n");
            fflush(stdin);
            op = -1;
            continue;
        }

        switch(op) {
            case 1: cadastrarFuncionario(); break;
            case 2: pesquisarFuncionario(); break;
            case 3: excluirFuncionario(); break;
            case 0: break;
            default: printf("\n[!] Opcao invalida!\n");
        }
    } while (op != 0);
}
