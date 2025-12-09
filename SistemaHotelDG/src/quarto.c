#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/quarto.h"

#define ARQUIVO_QUARTOS "data/quartos.dat"

void cadastrarQuarto() {
    FILE *f = fopen(ARQUIVO_QUARTOS, "rb+");
    if (!f) f = fopen(ARQUIVO_QUARTOS, "wb+");

    Quarto q, novo;
    int existe = 0;

    printf("\n=== CADASTRAR NOVO QUARTO ===\n");
    printf("Número do quarto: ");
    scanf("%d", &novo.numero);

    rewind(f);
    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == novo.numero) { existe = 1; break; }
    }

    if (existe) {
        printf("\n[!] O quarto %d já está cadastrado!\n", novo.numero);
    } else {
        printf("Capacidade (número máximo de hóspedes): ");
        scanf("%d", &novo.qtdHospedes);

        printf("Valor da diária: R$ ");
        scanf("%f", &novo.valorDiaria);

        strcpy(novo.status, "desocupado");

        fseek(f, 0, SEEK_END);
        fwrite(&novo, sizeof(Quarto), 1, f);

        printf("\n[✓] Quarto %d cadastrado com sucesso!\n", novo.numero);
    }

    fclose(f);
}

void excluirQuarto() {
    int num;
    listarQuartos();

    printf("\n=== EXCLUIR QUARTO ===\n");
    printf("Número do quarto para excluir: ");
    scanf("%d", &num);

    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    FILE *temp = fopen("data/temp_q.dat", "wb");
    if (!f) return;

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

void listarQuartos() {
    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    if (!f) {
        printf("\n[!] Nenhum quarto cadastrado até o momento.\n");
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

void menuQuartos() {
    int op;
    do {
        printf("\n=== MENU DE QUARTOS ===\n");
        printf("1 - Cadastrar Quarto\n");
        printf("2 - Listar Quartos\n");
        printf("3 - Excluir Quarto\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");

        scanf("%d", &op);

        if (op == 1) cadastrarQuarto();
        else if (op == 2) listarQuartos();
        else if (op == 3) excluirQuarto();

    } while (op != 0);
}
