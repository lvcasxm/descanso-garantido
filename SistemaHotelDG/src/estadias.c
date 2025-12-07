#include <stdio.h>
#include "../include/estadia.h"

void cadastrarEstadia() {
    printf("\n[!] Funcionalidade de cadastro de estadias ainda nao implementada.\n");
}

void finalizarEstadia() {
    printf("\n[!] Funcionalidade de baixa de estadia ainda nao implementada.\n");
}

void listarEstadiasPorCliente() {
    printf("\n[!] Funcionalidade de pesquisa de estadias ainda nao implementada.\n");
}

void menuEstadias() {
    int op;
    do {
        printf("\n=== MENU ESTADIAS ===\n");
        printf("1 - Cadastrar Estadia\n");
        printf("2 - Finalizar Estadia (Dar Baixa)\n");
        printf("3 - Ver Estadias por Cliente\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch(op) {
            case 1: cadastrarEstadia(); break;
            case 2: finalizarEstadia(); break;
            case 3: listarEstadiasPorCliente(); break;
        }
    } while (op != 0);
}
