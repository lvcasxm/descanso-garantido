#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/cliente.h"

// Usaremos o caminho direto para a pasta data. 
// Certifique-se de que a pasta "data" existe no diretório raiz do projeto.
#define ARQUIVO_CLIENTES "data/clientes.dat"

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
        printf("\n[!] Nenhum cliente cadastrado ou arquivo data/clientes.dat nao encontrado.\n");
        return;
    }

    Cliente c;
    printf("\n=== LISTA DE CLIENTES DISPONIVEIS ===\n");
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
    fflush(stdin);
    fgets(c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;

    printf("Endereco: ");
    fflush(stdin);
    fgets(c.endereco, 100, stdin);
    c.endereco[strcspn(c.endereco, "\n")] = 0;

    printf("Telefone: ");
    fflush(stdin);
    fgets(c.telefone, 20, stdin);
    c.telefone[strcspn(c.telefone, "\n")] = 0;

    FILE *f = fopen(ARQUIVO_CLIENTES, "ab");
    if (f) {
        fwrite(&c, sizeof(Cliente), 1, f);
        fclose(f);
        printf("\n[+] Cliente cadastrado com sucesso!\n");
    } else {
        printf("\n[!] Erro ao salvar: verifique se a pasta 'data' existe.\n");
    }
}

void pesquisarCliente() {
    listarClientes(); 

    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    if (!f) return;

    int opcao;
    printf("\nPesquisar por:\n1 - Codigo\n2 - Nome\nEscolha: ");
    if (scanf("%d", &opcao) != 1) {
        printf("\nEntrada invalida!\n");
        fflush(stdin);
        fclose(f);
        return;
    }

    Cliente c;
    int encontrado = 0;

    if (opcao == 1) {
        int cod;
        printf("Digite o codigo: ");
        scanf("%d", &cod);
        while (fread(&c, sizeof(Cliente), 1, f)) {
            if (c.codigo == cod) { encontrado = 1; break; }
        }
    } else if (opcao == 2) {
        char nomeBusca[50];
        printf("Digite o nome: ");
        fflush(stdin);
        fgets(nomeBusca, 50, stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = 0;
        while (fread(&c, sizeof(Cliente), 1, f)) {
            if (stricmp(c.nome, nomeBusca) == 0) { encontrado = 1; break; }
        }
    } else {
        printf("\nOpcao inexistente!\n");
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
        printf("\nCliente nao encontrado no sistema.\n");
    }
}
void excluirCliente() {
    listarClientes();
    int cod;
    printf("\nDigite o codigo para EXCLUIR: ");
    if (scanf("%d", &cod) != 1) {
        fflush(stdin);
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

    if (encontrado) printf("\n[+] Cliente removido com sucesso.\n");
    else printf("\n[!] Codigo nao encontrado.\n");
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
        if (scanf("%d", &op) != 1) {
            fflush(stdin);
            op = -1;
        }

        switch(op) {
            case 1: cadastrarCliente(); break;
            case 2: pesquisarCliente(); break;
            case 3: excluirCliente(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (op != 0);
}