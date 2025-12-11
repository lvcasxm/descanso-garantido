#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/estadia.h"
#include "../include/quarto.h"
#include "../include/cliente.h"

#define ARQUIVO_ESTADIAS "data/estadias.dat"
#define ARQUIVO_QUARTOS "data/quartos.dat"
#define ARQUIVO_CLIENTES "data/clientes.dat"

// --- Funções auxiliares locais (escopo deste arquivo) ----------------

static int lerIntNaoNegativo() {
    char buffer[128];
    int valor;
    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%d", &valor) == 1 && valor >= 0) return valor;
        printf("Entrada inválida! Digite um número inteiro não negativo: ");
    }
}

static void lerData(int *dia, int *mes, int *ano) {
    char buffer[256];
    int d, m, a;
    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%d %d %d", &d, &m, &a) == 3 &&
            d >= 1 && d <= 31 && m >= 1 && m <= 12 && a >= 1900) {
            *dia = d; *mes = m; *ano = a;
            return;
        }
        printf("Data inválida! Digite novamente (DD MM AAAA): ");
    }
}

static int lerOpcaoMenu() {
    char buffer[64];
    int op;
    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%d", &op) == 1) return op;
        printf("Opção inválida, tente novamente: ");
    }
}

// --- Reaproveita as tuas funções existentes (ou mantém próximas adaptações) ----
// validarCliente() e calcularDiferencaDias() - se já estiverem declaradas em outro .c,
// você pode remover as versões daqui. Mantive implementações compatíveis.

int validarCliente(int id) {
    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
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

    if (t1 == -1 || t2 == -1) return -1;
    double segundos = difftime(t2, t1);
    int dias = (int)(segundos / (60 * 60 * 24));
    return dias > 0 ? dias : -1;
}

// --- Gera um código único para cada estadia -----------------------------
static int gerarCodigoEstadia() {
    FILE *f = fopen(ARQUIVO_ESTADIAS, "rb");
    if (!f) return 1;
    Estadia e;
    int maior = 0;
    while (fread(&e, sizeof(Estadia), 1, f)) {
        if (e.codigoEstadia > maior) maior = e.codigoEstadia;
    }
    fclose(f);
    return maior + 1;
}

// --- Funções principais --------------------------------------------------

void cadastrarEstadia() {
    int codCli, dE, mE, aE, dS, mS, aS, hospedes;

    printf("\n=== CADASTRO DE ESTADIA ===\n");
    printf("Informe o código do cliente: ");
    codCli = lerIntNaoNegativo();

    if (!validarCliente(codCli)) {
        printf("\n[!] Cliente de código %d não encontrado!\n", codCli);
        listarClientes();
        return;
    }

    printf("Data de entrada (DD MM AAAA): ");
    lerData(&dE, &mE, &aE);

    printf("Data de saída (DD MM AAAA): ");
    lerData(&dS, &mS, &aS);

    int dias = calcularDiferencaDias(dE, mE, aE, dS, mS, aS);
    if (dias <= 0) {
        printf("[!] Período inválido. A saída deve ser depois da entrada.\n");
        return;
    }

    printf("Quantidade de hóspedes: ");
    hospedes = lerIntNaoNegativo();
    if (hospedes <= 0) {
        printf("[!] Número de hóspedes deve ser maior que zero.\n");
        return;
    }

    // abre quartos e procura um disponível
    FILE *fQ = fopen(ARQUIVO_QUARTOS, "rb+");
    if (!fQ) { printf("[!] Não foi possível acessar cadastro de quartos.\n"); return; }

    Quarto q;
    int achei = 0;
    int numeroEscolhido = -1;

    while (fread(&q, sizeof(Quarto), 1, fQ)) {
        if (strcmp(q.status, "desocupado") == 0 && q.qtdHospedes >= hospedes) {
            // marca o quarto como ocupado e grava
            strcpy(q.status, "ocupado");
            fseek(fQ, -sizeof(Quarto), SEEK_CUR);
            fwrite(&q, sizeof(Quarto), 1, fQ);
            numeroEscolhido = q.numero;
            achei = 1;
            break;
        }
    }
    fclose(fQ);

    if (!achei) {
        printf("[!] Nenhum quarto disponível para %d hóspede(s).\n", hospedes);
        return;
    }

    // cria e grava a estadia no arquivo de estadias
    Estadia e;
    e.codigoEstadia = gerarCodigoEstadia();
    e.codigoCliente = codCli;
    e.numeroQuarto = numeroEscolhido;
    e.qtdDiarias = dias;
    // se sua struct tiver campos de data, atribua-os aqui também (opcional)

    FILE *fE = fopen(ARQUIVO_ESTADIAS, "ab");
    if (!fE) {
        printf("[!] Erro ao gravar estadia.\n");
        // caso gravar falhe, seria bom "desocupar" o quarto; implemento se quiser
        return;
    }
    fwrite(&e, sizeof(Estadia), 1, fE);
    fclose(fE);

    printf("\n[✓] Estadia registrada (ID %d) no quarto %d para %d diária(s).\n",
           e.codigoEstadia, e.numeroQuarto, e.qtdDiarias);
}

void finalizarEstadia() {
    int id;
    printf("\n=== FINALIZAR ESTADIA ===\n");
    printf("Informe o ID da estadia para check-out: ");
    id = lerIntNaoNegativo();

    FILE *fE = fopen(ARQUIVO_ESTADIAS, "rb");
    if (!fE) { printf("[!] Nenhuma estadia registrada.\n"); return; }

    Estadia e;
    int acheiE = 0;
    while (fread(&e, sizeof(Estadia), 1, fE)) {
        if (e.codigoEstadia == id) { acheiE = 1; break; }
    }
    fclose(fE);

    if (!acheiE) {
        printf("[!] ID de estadia inválido.\n");
        return;
    }

    // abre quartos e libera o quarto usado pela estadia
    FILE *fQ = fopen(ARQUIVO_QUARTOS, "rb+");
    if (!fQ) { printf("[!] Erro ao acessar quartos.\n"); return; }

    Quarto q;
    int achouQ = 0;
    while (fread(&q, sizeof(Quarto), 1, fQ)) {
        if (q.numero == e.numeroQuarto) {
            // mostra resumo e libera o quarto
            printf("\n=== RESUMO DO CHECK-OUT ===\n");
            printf("Quarto: %d | Diárias: %d\n", q.numero, e.qtdDiarias);
            printf("Valor total a pagar: R$ %.2f\n", e.qtdDiarias * q.valorDiaria);

            strcpy(q.status, "desocupado");
            fseek(fQ, -sizeof(Quarto), SEEK_CUR);
            fwrite(&q, sizeof(Quarto), 1, fQ);
            achouQ = 1;
            break;
        }
    }
    fclose(fQ);

    if (!achouQ) {
        printf("[!] Não foi possível localizar o quarto dessa estadia.\n");
    }

    // opcional: marcar estadia como finalizada no arquivo (requere estrutura com flag)
}

void listarEstadiasPorCliente() {
    int codCli;
    printf("\nInforme o código do cliente para visualizar o histórico: ");
    codCli = lerIntNaoNegativo();

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
        op = lerOpcaoMenu();

        if (op == 1) cadastrarEstadia();
        else if (op == 2) finalizarEstadia();
        else if (op == 3) listarEstadiasPorCliente();
        else if (op != 0) printf("Opção inválida.\n");

    } while (op != 0);
}
