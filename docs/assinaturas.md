# Assinaturas das funções

**Versão:** 1.3

**Última atualização:** 28-11-2025 | 20:21

**Autores:** Lucas, André e Ana

Este arquivo documenta todas as assinaturas das funções que desenvolvemos no projeto, bem como as estruturas de dados também.

## Estruturas de dados

### Estrutura do cliente

typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];  // Formato: (xx) xxxx-xxxx
} Cliente;

### Estrutura do funcionário

typedef struct {
    int codigo;
    char nome[100];
    char telefone[15];  // Formato: (xx) xxxx-xxxx
    char cargo[50];
    int salario;
} Funcionario;

### Estrutura do quarto

typedef struct {
    int numero;
    int quantidade_hospedes;
    float valor_diaria;
    bool ocupado;  // true = ocupado, false = desocupado
} Quarto;

## Assinatura das funções

### Épico 01 - Menu principal e principais funcionalidades

## E1-F01 - Exibir Menu

- **Função:** exibirMenuPrincipal.

- **Descrição:** Exibe o menu principal do sistema com todas as opções disponíveis.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** void.

void exibirMenuPrincipal(void);
