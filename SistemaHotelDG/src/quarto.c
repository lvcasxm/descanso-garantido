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

    printf("\n=== CADASTRAR QUARTO ===\n");
    printf("Numero do quarto: ");
    scanf("%d", &novo.numero);

    rewind(f);
    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == novo.numero) { existe = 1; break; }
    }

    if (existe) {
        printf("[!] Erro: Quarto numero %d ja cadastrado.\n", novo.numero);
    } else {
        printf("Capacidade (hospedes): ");
        scanf("%d", &novo.qtdHospedes);
        printf("Valor da diaria: ");
        scanf("%f", &novo.valorDiaria);
        strcpy(novo.status, "desocupado");

        fseek(f, 0, SEEK_END);
        fwrite(&novo, sizeof(Quarto), 1, f);
        printf("[+] Quarto %d cadastrado com sucesso!\n", novo.numero);
    }
    fclose(f);
}

void excluirQuarto() {
    int num;
    listarQuartos();
    printf("\nNumero do quarto para excluir: ");
    scanf("%d", &num);

    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    FILE *temp = fopen("data/temp_q.dat", "wb");
    if (!f) return;

    Quarto q;
    int encontrado = 0;
    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == num) {
            if (strcmp(q.status, "ocupado") == 0) {
                printf("[!] Nao e possivel excluir um quarto ocupado!\n");
                fwrite(&q, sizeof(Quarto), 1, temp);
            } else { encontrado = 1; }
        } else { fwrite(&q, sizeof(Quarto), 1, temp); }
    }
    fclose(f); fclose(temp);
    remove(ARQUIVO_QUARTOS);
    rename("data/temp_q.dat", ARQUIVO_QUARTOS);

    if (encontrado) printf("[+] Quarto removido com sucesso.\n");
    else printf("[!] Quarto nao encontrado.\n");
}

void listarQuartos() {
    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    if (!f) { printf("\n[!] Nenhum quarto cadastrado.\n"); return; }
    Quarto q;
    printf("\n%-10s %-15s %-10s %-10s\n", "NUMERO", "CAPACIDADE", "VALOR", "STATUS");
    printf("--------------------------------------------------\n");
    while (fread(&q, sizeof(Quarto), 1, f)) {
        printf("%-10d %-15d R$%-9.2f %-10s\n", q.numero, q.qtdHospedes, q.valorDiaria, q.status);
    }
    fclose(f);
}

void menuQuartos() {
    int op;
    do {
        printf("\n=== MENU QUARTOS ===\n1-Cadastrar 2-Listar 3-Excluir 0-Voltar\nEscolha: ");
        scanf("%d", &op);
        if (op == 1) cadastrarQuarto();
        else if (op == 2) listarQuartos();
        else if (op == 3) excluirQuarto();
    } while (op != 0);
}