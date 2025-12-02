# Assinaturas das funções

**Versão:** 1.3

**Última atualização:** 02-12-2025 | 19:24

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

### Estrutura da estadia

typedef struct {
    int codigo_cliente;
    int numero_quarto;
    char data_entrada[11];   // Formato: DD/MM/AAAA
    char data_saida[11];     // Formato: DD/MM/AAAA
    int quantidade_hospedes;
    int quantidade_diarias;
    bool ativa;  // true = ativa, false = finalizada
} Estadia;

## Assinatura das funções

### Épico 01 - Menu principal e principais funcionalidades

## E1-F01 - Exibir Menu

- **Função:** exibirMenuPrincipal.

- **Descrição:** Exibe o menu principal do sistema com todas as opções disponíveis.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** void.

void exibirMenuPrincipal(void);

- **Função:** lerOpcaoMenu.

- **Descrição:** Lê e valida opção escolhida pelo usuário no menu.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** int - Número da opção escolhida pelo usuário (de 1 a N).

int lerOpcaoMenu(void);

## E1-F02 - Cadastrar cliente

- **Função:** cadastrarCliente.

- **Descrição:** Realiza o cadastro completo de um novo cliente no sistema.

- **Parâmetros de entrada:** 
Cliente: ponteiro para estrutura cliente a ser preenchida.

- **Retorno:** 
int
- 0: Cadastro realizado com sucesso.
- 1: Erro no cadastro (código duplicado).
- 2: Erro no cadastro (nome duplicado).
- 3: Erro no cadastro (telefone duplicado).

int cadastrarCliente(Cliente *cliente);
