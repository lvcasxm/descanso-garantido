#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/estadia.h"
#include "../include/quarto.h"
#include "../include/cliente.h"

#define ARQUIVO_ESTADIAS "data/estadias.dat"
#define ARQUIVO_QUARTOS "data/quartos.dat"

int validarCliente(int id) {
    FILE *f = fopen("data/clientes.dat", "rb");
    if (!f) return 0;
    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.codigo == id) { fclose(f); return 1; }
    }
    fclose(f);
    return 0;
}

int calcularDiferencaDias(int d1, int m1, int a1, int d2, int m2, int a2) {
    struct tm entrada = {0}, saida = {0};

    entrada.tm_mday = d1;
    entrada.tm_mon = m1 - 1;
    entrada.tm_year = a1 - 1900;
    entrada.tm_hour = 12;

    saida.tm_mday = d2;
    saida.tm_mon = m2 - 1;
    saida.tm_year = a2 - 1900;
    saida.tm_hour = 12;

    time_t t1 = mktime(&entrada);
    time_t t2 = mktime(&saida);

    if (t1 == -1 || t2 == -1) return 1;

    double segundos = difftime(t2, t1);
    int dias = (int)(segundos / (60 * 60 * 24));

    return (dias <= 0) ? 1 : dias;
}

void cadastrarEstadia() {
    int codCli, dE, mE, aE, dS, mS, aS, hospedes;

    printf("\n=== CADASTRO DE ESTADIA ===\n");
    printf("Informe o código do cliente: ");
    scanf("%d", &codCli);

    if (!validarCliente(codCli)) {
        printf("\n[!] Cliente de código %d não encontrado!\n", codCli);
        printf("Clientes cadastrados:\n");
        listarClientes();
        return;
    }

    printf("Data de entrada (DD MM AAAA): ");
    scanf("%d %d %d", &dE, &mE, &aE);
    printf("Data de saída  (DD MM AAAA): ");
    scanf("%d %d %d", &dS, &mS, &aS);
    printf("Quantidade de hóspedes: ");
    scanf("%d", &hospedes);

    FILE *fQ = fopen(ARQUIVO_QUARTOS, "rb+");
    if (!fQ) return;

    Quarto q;
    int achei = 0;
    while (fread(&q, sizeof(Quarto), 1, fQ)) {
        if (strcmp(q.status, "desocupado") == 0 && q.qtdHospedes >= hospedes) {
            Estadia e;

            strcpy(q.status, "ocupado");
            fseek(fQ, -sizeof(Quarto), SEEK_CUR);
            fwrite(&q, sizeof(Quarto), 1, fQ);

            achei = 1;
            break;
        }
    }
    fclose(fQ);
    if (!achei)
        printf("[!] Nenhum quarto disponível para %d hóspede(s).\n", hospedes);
}

void finalizarEstadia() {
    int id;
    printf("\n=== FINALIZAR ESTADIA ===\n");
    printf("Informe o ID da estadia para check-out: ");
    scanf("%d", &id);

    FILE *fE = fopen(ARQUIVO_ESTADIAS, "rb");
    Estadia e;
    int acheiE = 0;
    while (fread(&e, sizeof(Estadia), 1, fE)) {
        if (e.codigoEstadia == id) { acheiE = 1; break; }
    }
    fclose(fE);

    if (acheiE) {
        FILE *fQ = fopen(ARQUIVO_QUARTOS, "rb+");
        Quarto q;
        while (fread(&q, sizeof(Quarto), 1, fQ)) {
            if (q.numero == e.numeroQuarto) {

                printf("\n=== RESUMO DO CHECK-OUT ===\n");
                printf("Quarto: %d | Diárias: %d\n", q.numero, e.qtdDiarias);
                printf("Valor total a pagar: R$ %.2f\n", e.qtdDiarias * q.valorDiaria);

                strcpy(q.status, "desocupado");
                fseek(fQ, -sizeof(Quarto), SEEK_CUR);
                fwrite(&q, sizeof(Quarto), 1, fQ);
                break;
            }
        }
        fclose(fQ);
    } else {
        printf("[!] ID de estadia inválido.\n");
    }
}

void listarEstadiasPorCliente() {
    int codCli;
    printf("\nInforme o código do cliente para visualizar o histórico: ");
    scanf("%d", &codCli);

    FILE *f = fopen(ARQUIVO_ESTADIAS, "rb");
    if (!f) {
        printf("[!] Nenhuma estadia registrada no sistema.\n");
        return;
    }

    Estadia e;
    int encontrou = 0;
    int totalPonto = 0;

    printf("\n=== HISTÓRICO DE ESTADIAS DO CLIENTE %d ===\n", codCli);
    printf("%-10s %-10s %-10s\n", "ID", "Quarto", "Diárias");
    printf("------------------------------------------\n");

    while (fread(&e, sizeof(Estadia), 1, f)) {
        if (e.codigoCliente == codCli) {
            printf("%-10d %-10d %-10d\n", e.codigoEstadia, e.numeroQuarto, e.qtdDiarias);
            totalPonto += (e.qtdDiarias * 10);
            encontrou = 1;
        }
    }

    if (encontrou) {
        printf("------------------------------------------\n");
        printf("Total de pontos acumulados: %d\n", totalPonto);
    } else {
        printf("[!] Nenhuma estadia encontrada para esse cliente.\n");
    }

    fclose(f);
}

void menuEstadias() {
    int op;
    do {
        printf("\n=== MENU DE ESTADIAS ===\n");
        printf("1 - Reservar estadia\n");
        printf("2 - Finalizar estadia (Check-out)\n");
        printf("3 - Consultar histórico do cliente\n");
        printf("0 - Voltar ao menu anterior\n");
        printf("Opção desejada: ");
        scanf("%d", &op);

        if (op == 1) cadastrarEstadia();
        else if (op == 2) finalizarEstadia();
        else if (op == 3) listarEstadiasPorCliente();

    } while (op != 0);
}
