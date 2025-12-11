#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/quarto.h"

// Arquivo onde os quartos são salvos
#define ARQUIVO_QUARTOS "data/quartos.dat"

// ===============================
// FUNÇÕES DE LEITURA SEGURA
// ===============================

int lerint() {
    char buffer[100];
    int valor;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            continue;
        }

        // Verifica se é inteiro válido
        if (sscanf(buffer, "%d", &valor) == 1) {

            // Bloqueia negativos
            if (valor >= 0) {
                return valor;
            }

            printf("Valor inválido! Digite um inteiro NÃO NEGATIVO: ");
            continue;
        }

        printf("Entrada inválida! Digite um número inteiro: ");
    }
}


float lerFloat() {
    char buffer[100];
    float valor;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            continue;
        }

        if (sscanf(buffer, "%f", &valor) == 1) {
            return valor;
        }

        printf("Entrada inválida! Digite um valor numérico: ");
    }
}

// ===============================
// CADASTRAR QUARTO
// ===============================

void cadastrarQuarto() {
    FILE *f = fopen(ARQUIVO_QUARTOS, "rb+");
    if (!f) f = fopen(ARQUIVO_QUARTOS, "wb+");

    Quarto q, novo;
    int existe = 0;

    printf("\n=== CADASTRAR NOVO QUARTO ===\n");
    printf("Número do quarto: ");
    novo.numero = lerint();

    rewind(f);
    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == novo.numero) {
            existe = 1;
            break;
        }
    }

    if (existe) {
        printf("\n[!] O quarto %d já está cadastrado!\n", novo.numero);
    } else {
        printf("Capacidade (máximo de hóspedes): ");
        novo.qtdHospedes = lerint();

        printf("Valor da diária (R$): ");
        novo.valorDiaria = lerFloat();

        strcpy(novo.status, "desocupado");

        fseek(f, 0, SEEK_END);
        fwrite(&novo, sizeof(Quarto), 1, f);

        printf("\n[✓] Quarto %d cadastrado com sucesso!\n", novo.numero);
    }

    fclose(f);
}

// ===============================
// LISTAR QUARTOS
// ===============================

void listarQuartos() {
    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    if (!f) {
        printf("\n[!] Nenhum quarto cadastrado.\n");
        return;
    }

    Quarto q;

    printf("\n=== LISTA DE QUARTOS ===\n");
    printf("%-10s %-15s %-12s %-12s\n", "NÚMERO", "CAPACIDADE", "VALOR", "STATUS");
    printf("-----------------------------------------------------------\n");

    while (fread(&q, sizeof(Quarto), 1, f)) {
        printf("%-10d %-15d R$ %-10.2f %-12s\n",
               q.numero, q.qtdHospedes, q.valorDiaria, q.status);
    }

    fclose(f);
}

// ===============================
// EXCLUIR QUARTO
// ===============================

void excluirQuarto() {
    listarQuartos();

    printf("\n=== EXCLUIR QUARTO ===\n");
    printf("Número do quarto para excluir: ");

    int num = lerint();

    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    FILE *temp = fopen("data/temp_q.dat", "wb");

    if (!f || !temp) {
        printf("[!] Erro ao abrir arquivos.\n");
        return;
    }

    Quarto q;
    int encontrado = 0;

    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == num) {
            if (strcmp(q.status, "ocupado") == 0) {
                printf("\n[!] Não é possível excluir um quarto OCUPADO!\n");
                fwrite(&q, sizeof(Quarto), 1, temp);
            } else {
                encontrado = 1;
            }
        } else {
            fwrite(&q, sizeof(Quarto), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO_QUARTOS);
    rename("data/temp_q.dat", ARQUIVO_QUARTOS);

    if (encontrado)
        printf("\n[✓] Quarto removido com sucesso.\n");
    else
        printf("\n[!] Quarto não encontrado.\n");
}

// ===============================
// MENU DE QUARTOS
// ===============================

void menuQuartos() {
    int op;

    do {
        printf("\n=== MENU DE QUARTOS ===\n");
        printf("1 - Cadastrar Quarto\n");
        printf("2 - Listar Quartos\n");
        printf("3 - Excluir Quarto\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");

        op = lerint();

        switch (op) {
            case 1: cadastrarQuarto(); break;
            case 2: listarQuartos(); break;
            case 3: excluirQuarto(); break;
            case 0: break;
            default: printf("[!] Opção inválida!\n");
        }

    } while (op != 0);
}
