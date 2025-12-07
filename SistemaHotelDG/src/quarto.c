#include <stdio.h>
#include <string.h>
#include "../include/quarto.h"

void cadastrarQuarto() {
    printf("\n[!] Funcionalidade de cadastro de quartos ainda nao implementada.\n");
}

void listarQuartos() {
    printf("\n[!] Funcionalidade de listagem de quartos ainda nao implementada.\n");
}

void menuQuartos() {
    int op;
    do {
        printf("\n=== MENU QUARTOS ===\n");
        printf("1 - Cadastrar Quarto\n");
        printf("2 - Listar Quartos\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch(op) {
            case 1: cadastrarQuarto(); break;
            case 2: listarQuartos(); break;
        }
    } while (op != 0);
}