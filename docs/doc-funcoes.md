# Assinaturas das funções

**Versão:** 1.3

**Última atualização:** 10-12-2025 | 19:43

**Autores:** Lucas, André e Ana

Este arquivo documenta todas as funções que escrevemos ao longo do desenvolvimento do projeto.

## Estruturas de dados

### Estrutura do cliente
```c
typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
} Cliente;
```

### Estrutura do funcionário
```c
typedef struct {
    int codigo;
    char nome[50];
    char telefone[20];
    char cargo[30];
    float salario;
} Funcionario;
```

### Estrutura do quarto
```c
typedef struct {
    int numero;
    int qtdHospedes;
    float valorDiaria;
    char status[12];
} Quarto;
```

### Estrutura da estadia
```c
typedef struct {
    int codigoEstadia;
    char dataEntrada[11];
    char dataSaida[11];
    int qtdDiarias;
    int codigoCliente;
    int numeroQuarto;
} Estadia;
```

## Assinatura das funções

### Épico 01 - Menu principal e principais funcionalidades

## E1-F01 - Exibir Menu

- **Função:** void menuPrincipal(void);

- **Descrição:** Exibe o menu principal do sistema com todas as opções disponíveis.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** void.

```c
void menuPrincipal() {
    int opc;
    do {
        printf("\n===== SISTEMA HOTEL DG =====\n");
        printf("1 - Clientes\n");
        printf("2 - Funcionarios\n");
        printf("3 - Quartos\n");
        printf("4 - Estadia\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        opc = lerInteiro(); 

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
```

- **Função:** void iniciarSistema(void);

- **Descrição:** Subfunção que serve somente para chamar a função menuPrincipal(), para evitar bugs.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** void

```c
void iniciarSistema() {
    menuPrincipal();
}
```

## E1-F02 - Cadastrar cliente

- **Função:** int clienteExiste(void);

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

- **Função:** verificarCodigoClienteExiste

- **Descrição:** Verifica se já existe um cliente cadastrado com o código informado.

- **Parâmetros de entrada:** 
Código: Código do cliente a ser verificado.

- **Retorno:** bool (verdadeiro para se o código já existe, ou falso para caso não exista).

bool verificarCodigoClienteExiste(int codigo);

- **Função:** verificarNomeClienteExiste

- **Descrição:** Verifica se já existe um cliente cadastrado com o mesmo nome.

- **Parâmetros de entrada:** 
Nome: String contendo o nome a ser verificado.

- **Retorno:** bool (verdadeiro para se o nome já existe, ou falso para caso não exista);

bool verificarNomeClienteExiste(const char *nome);

- **Função:** verificarTelefoneExiste

- **Descrição:** Verifica se o telefone já está cadastrado (clientes ou funcionários)

- **Parâmetros de entrada:**
 telefone: String contendo o telefone no formato (xx) xxxx-xxxx
   
- **Retorno:** bool
 true: Telefone já cadastrado
 false: Telefone disponível

bool verificarTelefoneExiste(const char *telefone);

- **Função:** validarFormatoTelefone

- **Descrição:** Valida se o telefone está no formato correto (xx) xxxx-xxxx
 
- **Parâmetros de entrada:**
 telefone: String contendo o telefone a ser validado
 
- **Retorno: bool**
true: Formato válido
false: Formato inválido

bool validarFormatoTelefone(const char *telefone);

## E01-F03: Cadastrar funcionário

- **Função:** int gerarCodigoFuncionario(void);

- **Descrição:** Gera um código que servirá de identificação do funcionário que for cadastrado.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Int (gera um código armazenado numa variável inteira).

```c
int gerarCodigoFuncionario() {
    FILE *f = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    Funcionario func;
    int maior = 0;

    if (f) {
        while (fread(&func, sizeof(Funcionario), 1, f)) {
            if (func.codigo > maior) maior = func.codigo;
        }
        fclose(f);
    }

    return maior + 1;
}
```

- **Função:** void listarFuncionarios(void);

- **Descrição:** Lista todos os funcionários que foram cadastrados pelo sistema.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.

```c
void listarFuncionarios() {
    FILE *f = fopen(ARQUIVO_FUNCIONARIOS, "rb");
    if (!f) {
        printf("\n[!] Nenhum funcionário cadastrado.\n");
        return;
    }

    Funcionario f1;
    printf("\n=== FUNCIONÁRIOS CADASTRADOS ===\n");
    printf("%-10s %-30s %-20s\n", "ID", "NOME", "CARGO");
    printf("------------------------------------------------------------\n");

    while (fread(&f1, sizeof(Funcionario), 1, f)) {
        printf("%-10d %-30s %-20s\n", f1.codigo, f1.nome, f1.cargo);
    }

    fclose(f);
    printf("------------------------------------------------------------\n");
}
```

- **Função:** void cadastrarFuncionario(void);

- **Descrição:** Função que cadastra o funcionário; requer que o usuário digite nome completo, telefone, cargo e salário.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.

```c
void cadastrarFuncionario() {
    Funcionario f;
    f.codigo = gerarCodigoFuncionario();

    printf("\n=== NOVO FUNCIONÁRIO | ID: %d ===\n", f.codigo);

    // --- NOME ---
    do {
        printf("Nome completo: ");
        fgets(f.nome, 50, stdin);
        f.nome[strcspn(f.nome, "\n")] = 0;
    } while (!validarLetras(f.nome));

    // --- TELEFONE ---
    do {
        printf("Telefone (apenas números): ");
        fgets(f.telefone, 20, stdin);
        f.telefone[strcspn(f.telefone, "\n")] = 0;

        if (!validarNumeros(f.telefone))
            printf("[!] Digite apenas números!\n");

    } while (!validarNumeros(f.telefone));

    // --- CARGO ---
    do {
        printf("Cargo: ");
        fgets(f.cargo, 30, stdin);
        f.cargo[strcspn(f.cargo, "\n")] = 0;
    } while (!validarLetras(f.cargo));

    // --- SALÁRIO ---
    char buffer[50];
    int valido = 0;

    do {
        printf("Salário: R$ ");
        fgets(buffer, 50, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        valido = 1;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isdigit(buffer[i]) && buffer[i] != '.' && buffer[i] != ',') {
                valido = 0;
            }
        }

        if (!valido)
            printf("[!] Digite apenas números! (exemplo: 2500.50)\n");

    } while (!valido);

    f.salario = atof(buffer);

    FILE *file = fopen(ARQUIVO_FUNCIONARIOS, "ab");
    if (file) {
        fwrite(&f, sizeof(Funcionario), 1, file);
        fclose(file);
        printf("\n[✓] Funcionário cadastrado com sucesso!\n");
    }
}
```
