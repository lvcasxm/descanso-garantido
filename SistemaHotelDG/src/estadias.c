#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/estadia.h"
#include "../include/quarto.h"
#include "../include/cliente.h"

#define ARQUIVO_ESTADIAS "data/estadias.dat"
#define ARQUIVO_QUARTOS "data/quartos.dat"

// Função para garantir que o ID do cliente é real
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

// Cálculo matemático exato de dias entre datas
int calcularDiferencaDias(int d1, int m1, int a1, int d2, int m2, int a2) {
    struct tm entrada = {0}, saida = {0};

    entrada.tm_mday = d1; 
    entrada.tm_mon = m1 - 1; 
    entrada.tm_year = a1 - 1900;
    entrada.tm_hour = 12; // Igualamos as horas para que a diferença seja exata em dias

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
    
    printf("\n=== CADASTRAR ESTADIA ===\n");
    printf("Codigo do cliente: ");
    scanf("%d", &codCli);

    if (!validarCliente(codCli)) {
        printf("\n[!] Codigo %d nao cadastrado!\n", codCli);
        listarClientes(); 
        return;
    }

    printf("Entrada (DIA MES ANO): ");
    scanf("%d %d %d", &dE, &mE, &aE);
    printf("Saida (DIA MES ANO): ");
    scanf("%d %d %d", &dS, &mS, &aS);
    printf("Hospedes: ");
    scanf("%d", &hospedes);

    FILE *fQ = fopen(ARQUIVO_QUARTOS, "rb+");
    if (!fQ) return;

    Quarto q;
    int achei = 0;
    while (fread(&q, sizeof(Quarto), 1, fQ)) {
        // REGRA: Status deve ser desocupado E a capacidade deve suportar o grupo
        if (strcmp(q.status, "desocupado") == 0 && q.qtdHospedes >= hospedes) {
            Estadia e;
            // ... (restante da lógica de preenchimento da estadia) ...

            strcpy(q.status, "ocupado"); // Ocupa o quarto
            fseek(fQ, -sizeof(Quarto), SEEK_CUR);
            fwrite(&q, sizeof(Quarto), 1, fQ);
            
            achei = 1; 
            break;
        }
    }
    fclose(fQ);
    if (!achei) printf("[!] Sem quartos para %d hospedes.\n", hospedes);
}

void finalizarEstadia() {
    int id;
    printf("\nID da estadia para check-out: ");
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
                printf("\n=== RESUMO CHECK-OUT ===\n");
                printf("Quarto: %d | Diarias: %d\n", q.numero, e.qtdDiarias);
                printf("VALOR TOTAL: R$ %.2f\n", e.qtdDiarias * q.valorDiaria);
                
                strcpy(q.status, "desocupado");
                fseek(fQ, -sizeof(Quarto), SEEK_CUR);
                fwrite(&q, sizeof(Quarto), 1, fQ);
                break;
            }
        }
        fclose(fQ);
    } else printf("[!] ID de estadia invalido.\n");
}

void listarEstadiasPorCliente() {
    int codCli;
    printf("\nID do cliente para ver historico e fidelidade: ");
    scanf("%d", &codCli);

    FILE *f = fopen(ARQUIVO_ESTADIAS, "rb");
    if (!f) {
        printf("[!] Nenhuma estadia registrada no sistema.\n");
        return;
    }

    Estadia e;
    int encontrou = 0;
    int totalPonto = 0;

    printf("\n=== HISTORICO DE ESTADIAS - CLIENTE %d ===\n", codCli);
    printf("%-10s %-10s %-10s\n", "ID EST.", "QUARTO", "DIARIAS");
    printf("------------------------------------------\n");
    
    while (fread(&e, sizeof(Estadia), 1, f)) {
        if (e.codigoCliente == codCli) {
            printf("%-10d %-10d %-10d\n", e.codigoEstadia, e.numeroQuarto, e.qtdDiarias);
            totalPonto += (e.qtdDiarias * 10); // Requisito 8: 10 pontos por diária
            encontrou = 1;
        }
    }
    
    if (encontrou) {
        printf("------------------------------------------\n");
        printf("TOTAL DE PONTOS FIDELIDADE: %d\n", totalPonto);
    } else {
        printf("[!] Nenhuma estadia encontrada para este cliente.\n");
    }
    
    fclose(f);
}
void menuEstadias() {
    int op;
    do {
        printf("\n=== MENU ESTADIAS ===\n");
        printf("1 - Reservar Estadia\n");
        printf("2 - Dar Baixa (Check-out)\n");
        printf("3 - Historico por Cliente\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);
        if (op == 1) cadastrarEstadia();
        else if (op == 2) finalizarEstadia();
        else if (op == 3) listarEstadiasPorCliente();
    } while (op != 0);
}