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

## Épico 01 - Menu principal e principais funcionalidades

### - **Função:** void menuPrincipal(void);

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

### **Função:** int gerarCodigoFuncionario(void);

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

### **Função:** void listarFuncionarios(void);

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

### **Função:** void cadastrarFuncionario(void);

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

## E01-F04: Cadastrar Quarto

### **Função:** void lerint(void);

- **Descrição:** Garante a leitura de um número positivo para uso nas demais outras funcionalidades.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Int (retorna um valor positivo, armazenado como inteiro na memória).
```c
int lerint() {
    char buffer[100];
    int valor;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            continue;
        }

        // Verifica se é inteiro válido
        if (sscanf(buffer, "%d", &valor) == 1) {

            // Bloqueia negativos
            if (valor >= 0) {
                return valor;
            }

            printf("Valor inválido! Digite um inteiro NÃO NEGATIVO: ");
            continue;
        }

        printf("Entrada inválida! Digite um número inteiro: ");
    }
}
```

### **Função:** float lerFloat(void);

- **Descrição:** Garante que o número lido será do tipo float, para uso nas demais outras funcionalidades desse módulo.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Float (retorna um número flutuante).
```c
float lerFloat() {
    char buffer[100];
    float valor;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            continue;
        }

        if (sscanf(buffer, "%f", &valor) == 1) {
            return valor;
        }

        printf("Entrada inválida! Digite um valor numérico: ");
    }
}
```

### **Função:** void cadastrarQuarto(void);

- **Descrição:** Função responsável pelo cadastro do quarto; solicita número do quarto, capacidade de hóspedes e valor da diária.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
void cadastrarQuarto() {
    FILE *f = fopen(ARQUIVO_QUARTOS, "rb+");
    if (!f) f = fopen(ARQUIVO_QUARTOS, "wb+");

    Quarto q, novo;
    int existe = 0;

    printf("\n=== CADASTRAR NOVO QUARTO ===\n");
    printf("Número do quarto: ");
    novo.numero = lerint();

    rewind(f);
    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == novo.numero) {
            existe = 1;
            break;
        }
    }

    if (existe) {
        printf("\n[!] O quarto %d já está cadastrado!\n", novo.numero);
    } else {
        printf("Capacidade (máximo de hóspedes): ");
        novo.qtdHospedes = lerint();

        printf("Valor da diária (R$): ");
        novo.valorDiaria = lerFloat();

        strcpy(novo.status, "desocupado");

        fseek(f, 0, SEEK_END);
        fwrite(&novo, sizeof(Quarto), 1, f);

        printf("\n[✓] Quarto %d cadastrado com sucesso!\n", novo.numero);
    }

    fclose(f);
}
```

### **Função:** void listarQuartos(void);

- **Descrição:** Função que lista todos os quartos que foram cadastrados no sistema, até aqueles em sessões anteriores.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
void listarQuartos() {
    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    if (!f) {
        printf("\n[!] Nenhum quarto cadastrado.\n");
        return;
    }

    Quarto q;

    printf("\n=== LISTA DE QUARTOS ===\n");
    printf("%-10s %-15s %-12s %-12s\n", "NÚMERO", "CAPACIDADE", "VALOR", "STATUS");
    printf("-----------------------------------------------------------\n");

    while (fread(&q, sizeof(Quarto), 1, f)) {
        printf("%-10d %-15d R$ %-10.2f %-12s\n",
               q.numero, q.qtdHospedes, q.valorDiaria, q.status);
    }

    fclose(f);
}
```

### **Função:** void excluirQuarto(void);

- **Descrição:** Função que exclui um quarto que foi anteriormente cadastrado no sistema.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
void excluirQuarto() {
    listarQuartos();

    printf("\n=== EXCLUIR QUARTO ===\n");
    printf("Número do quarto para excluir: ");

    int num = lerint();

    FILE *f = fopen(ARQUIVO_QUARTOS, "rb");
    FILE *temp = fopen("data/temp_q.dat", "wb");

    if (!f || !temp) {
        printf("[!] Erro ao abrir arquivos.\n");
        return;
    }

    Quarto q;
    int encontrado = 0;

    while (fread(&q, sizeof(Quarto), 1, f)) {
        if (q.numero == num) {
            if (strcmp(q.status, "ocupado") == 0) {
                printf("\n[!] Não é possível excluir um quarto OCUPADO!\n");
                fwrite(&q, sizeof(Quarto), 1, temp);
            } else {
                encontrado = 1;
            }
        } else {
            fwrite(&q, sizeof(Quarto), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO_QUARTOS);
    rename("data/temp_q.dat", ARQUIVO_QUARTOS);

    if (encontrado)
        printf("\n[✓] Quarto removido com sucesso.\n");
    else
        printf("\n[!] Quarto não encontrado.\n");
}
```

### **Função:** void menuQuartos(void);

- **Descrição:** Função que exibe o menu que exibe as funções correspondentes desse módulo.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
void menuQuartos() {
    int op;

    do {
        printf("\n=== MENU DE QUARTOS ===\n");
        printf("1 - Cadastrar Quarto\n");
        printf("2 - Listar Quartos\n");
        printf("3 - Excluir Quarto\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");

        op = lerint();

        switch (op) {
            case 1: cadastrarQuarto(); break;
            case 2: listarQuartos(); break;
            case 3: excluirQuarto(); break;
            case 0: break;
            default: printf("[!] Opção inválida!\n");
        }

    } while (op != 0);
}
```
