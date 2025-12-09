#include <stdio.h>
#include "../include/sistema.h"
#include "../include/cliente.h"
#include "../include/funcionario.h"
#include "../include/quarto.h"
#include "../include/estadia.h"


void menuPrincipal() {
    int opc;
    do {
        printf("\n===== SISTEMA HOTEL DG =====\n");
        printf("1 - Clientes\n2 - Funcionarios\n3 - Quartos\n4 - Estadia\n0 - Sair\nEscolha: ");

        scanf("%d", &opc);

        switch(opc) {
            case 1: menuClientes(); break;
            case 2: menuFuncionarios(); break;
            case 3: menuQuartos(); break;
            case 4: menuEstadias(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opc != 0);
}

void iniciarSistema() {
    menuPrincipal();
}