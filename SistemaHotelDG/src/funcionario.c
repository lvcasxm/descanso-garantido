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
        printf("\n[!] Nenhum funcionário cadastrado.\n");
        return;
    }

    Funcionario f1;
    printf("\n=== FUNCIONÁRIOS CADASTRADOS ===\n");
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

    printf("\n=== NOVO FUNCIONÁRIO | ID: %d ===\n", f.codigo);

    do {
        printf("Nome completo: ");
        fflush(stdin);
        fgets(f.nome, 50, stdin);
        f.nome[strcspn(f.nome, "\n")] = 0;
    } while (!validarLetras(f.nome));

    printf("Telefone (apenas números): ");
    scanf("%s", f.telefone);

    do {
        printf("Cargo: ");
        fflush(stdin);
        fgets(f.cargo, 30, stdin);
        f.cargo[strcspn(f.cargo, "\n")] = 0;
    } while (!validarLetras(f.cargo));

    printf("Salário: R$ ");
    scanf("%f", &f.salario);

    FILE *file = fopen(ARQUIVO_FUNCIONARIOS, "ab");
    if (file) {
        fwrite(&f, sizeof(Funcionario), 1, file);
        fclose(file);
        printf("\n[✓] Funcionário cadastrado com sucesso!\n");
    }
}

void pesquisarFuncionario() {
    listarFuncionarios();
    FILE *f = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (!f) return;

    int opcao;
    printf("\n=== PESQUISAR FUNCIONÁRIO ===\n");
    printf("1 - Buscar por ID\n");
    printf("2 - Buscar por Nome\n");
    printf("Escolha: ");

    if (scanf("%d", &opcao) != 1) {
        printf("\n[!] Entrada inválida!\n");
        fflush(stdin);
        fclose(f);
        return;
    }

    Funcionario func;
    int achou = 0;

    if (opcao == 1) {
        int cod;
        printf("Informe o ID: ");
        scanf("%d", &cod);

        while (fread(&func, sizeof(Funcionario), 1, f)) {
            if (func.codigo == cod) { achou = 1; break; }
        }

    } else if (opcao == 2) {
        char nomeBusca[50];
        printf("Informe o nome: ");
        fflush(stdin);
        fgets(nomeBusca, 50, stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = 0;

        while (fread(&func, sizeof(Funcionario), 1, f)) {
            if (stricmp(func.nome, nomeBusca) == 0) { achou = 1; break; }
        }

    } else {
        printf("\n[!] Opção inexistente!\n");
        fclose(f);
        return;
    }

    fclose(f);

    if (achou) {
        printf("\n=== FUNCIONÁRIO ENCONTRADO ===\n");
        printf("ID:        %d\n", func.codigo);
        printf("Nome:      %s\n", func.nome);
        printf("Cargo:     %s\n", func.cargo);
        printf("Salário:   R$ %.2f\n", func.salario);
        printf("Telefone:  %s\n", func.telefone);
    } else {
        printf("\n[!] Funcionário não encontrado no sistema.\n");
    }
}

void excluirFuncionario() {
    listarFuncionarios();
    int cod;

    printf("\n=== EXCLUIR FUNCIONÁRIO ===\n");
    printf("Informe o ID para exclusão: ");

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

    fclose(f);
    fclose(temp);

    remove(ARQUIVO_FUNCIONARIOS);
    rename("data/temp_func.dat", ARQUIVO_FUNCIONARIOS);

    if (encontrado)
        printf("\n[✓] Funcionário removido com sucesso.\n");
    else
        printf("\n[!] ID %d não encontrado.\n", cod);
}

void menuFuncionarios() {
    int op;
    do {
        printf("\n=== MENU DE FUNCIONÁRIOS ===\n");
        printf("1 - Cadastrar Funcionário\n");
        printf("2 - Pesquisar Funcionário\n");
        printf("3 - Excluir Funcionário\n");
        printf("0 - Voltar ao Menu Anterior\n");
        printf("Escolha: ");

        if (scanf("%d", &op) != 1) {
            printf("\n[!] Opção inválida!\n");
            fflush(stdin);
            op = -1;
            continue;
        }

        switch(op) {
            case 1: cadastrarFuncionario(); break;
            case 2: pesquisarFuncionario(); break;
            case 3: excluirFuncionario(); break;
            case 0: break;
            default:
                printf("\n[!] Escolha uma opção válida!\n");
        }

    } while (op != 0);
}
