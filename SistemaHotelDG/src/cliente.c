#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/cliente.h"

#define ARQUIVO_CLIENTES "data/clientes.dat"

#include <sys/stat.h>
#include <sys/types.h>

void garantirPastas() {
#ifdef _WIN32
    system("mkdir data >nul 2>nul");
#else
    mkdir("data", 0777);
#endif
}

// limpa buffer do teclado após scanf
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int lerInteiro() {
    char buffer[50];

    fgets(buffer, 50, stdin);

    buffer[strcspn(buffer, "\n")] = 0;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            return -1;
        }
    }

    return atoi(buffer);
}

int ehSomenteNumero(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') return 0;
    }
    return 1;
}

int clienteExiste(const char *nome, const char *telefone) {
    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    if (!f) return 0;

    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (stricmp(c.nome, nome) == 0 || stricmp(c.telefone, telefone) == 0) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int gerarCodigoCliente() {
    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    Cliente c;
    int maior = 0;
    if (f) {
        while (fread(&c, sizeof(Cliente), 1, f)) {
            if (c.codigo > maior) maior = c.codigo;
        }
        fclose(f);
    }
    return maior + 1;
}

void listarClientes() {
    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    if (!f) {
        printf("\n[!] Nenhum cliente cadastrado.\n");
        return;
    }

    Cliente c;
    printf("\n=== LISTA DE CLIENTES ===\n");
    printf("%-10s %-30s\n", "CODIGO", "NOME");
    printf("------------------------------------------\n");

    while (fread(&c, sizeof(Cliente), 1, f)) {
        printf("%-10d %-30s\n", c.codigo, c.nome);
    }

    fclose(f);
    printf("------------------------------------------\n");
}

void cadastrarCliente() {
    Cliente c;
    c.codigo = gerarCodigoCliente();

    printf("\n=== CADASTRAR CLIENTE (ID: %d) ===\n", c.codigo);

    printf("Nome: ");
    fgets(c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;

    printf("Endereco: ");
    fgets(c.endereco, 100, stdin);
    c.endereco[strcspn(c.endereco, "\n")] = 0;

    printf("Telefone (somente números): ");
    fgets(c.telefone, 20, stdin);
    c.telefone[strcspn(c.telefone, "\n")] = 0;

    if (!ehSomenteNumero(c.telefone)) {
        printf("[!] Telefone invalido. Apenas numeros.\n");
        return;
    }

    if (clienteExiste(c.nome, c.telefone)) {
        printf("\n[!] Cliente já cadastrado.\n");
        return;
    }

    FILE *f = fopen(ARQUIVO_CLIENTES, "ab");
    if (f) {
        fwrite(&c, sizeof(Cliente), 1, f);
        fclose(f);
        printf("\n[+] Cliente cadastrado com sucesso!\n");
    } else {
        printf("\n[!] Erro ao salvar. Verifique a pasta 'data'.\n");
    }
}

void pesquisarCliente() {
    listarClientes();

    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    if (!f) return;

    printf("\nPesquisar por:\n1 - Codigo\n2 - Nome\nEscolha: ");
    int opcao = lerInteiro();

    Cliente c;
    int encontrado = 0;

    if (opcao == 1) {
        printf("Digite o codigo: ");
        int cod = lerInteiro();

        while (fread(&c, sizeof(Cliente), 1, f)) {
            if (c.codigo == cod) { encontrado = 1; break; }
        }

    } else if (opcao == 2) {
        char nomeBusca[50];
        printf("Digite o nome: ");
        fgets(nomeBusca, 50, stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = 0;

        while (fread(&c, sizeof(Cliente), 1, f)) {
            if (stricmp(c.nome, nomeBusca) == 0) { encontrado = 1; break; }
        }

    } else {
        printf("\nOpcao invalida.\n");
        fclose(f);
        return;
    }

    fclose(f);

    if (encontrado) {
        printf("\n=== CLIENTE ENCONTRADO ===\n");
        printf("ID:       %d\n", c.codigo);
        printf("Nome:     %s\n", c.nome);
        printf("Endereco: %s\n", c.endereco);
        printf("Telefone: %s\n", c.telefone);
    } else {
        printf("\nCliente nao encontrado.\n");
    }
}

void excluirCliente() {
    listarClientes();

    printf("\nDigite o codigo para excluir: ");
    int cod = lerInteiro();
    if (cod < 0) {
        printf("\n[!] Codigo invalido.\n");
        return;
    }

    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    if (!f) return;

    FILE *temp = fopen("data/temp.dat", "wb");
    if (!temp) {
        fclose(f);
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.codigo == cod) {
            encontrado = 1;
        } else {
            fwrite(&c, sizeof(Cliente), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO_CLIENTES);
    rename("data/temp.dat", ARQUIVO_CLIENTES);

    if (encontrado)
        printf("\n[+] Cliente removido.\n");
    else
        printf("\n[!] Codigo nao encontrado.\n");
}

void menuClientes() {
    int op;
    do {
        printf("\n=== MENU CLIENTES ===\n");
        printf("1 - Cadastrar\n");
        printf("2 - Pesquisar\n");
        printf("3 - Excluir\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        op = lerInteiro();

        switch(op) {
            case 1: cadastrarCliente(); break;
            case 2: pesquisarCliente(); break;
            case 3: excluirCliente(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (op != 0);
}
