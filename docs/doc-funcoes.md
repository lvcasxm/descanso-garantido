# Assinaturas das funções

**Versão:** 5.3

**Última atualização:** 10-12-2025 | 21:09

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

### **Função:** void limparBuffer(void);

- **Descrição:** Função que limpa o buffer, escrita para ser usada nas demais funcionalidades deste módulo.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
```

### **Função:** int lerInteiro(void);

- **Descrição:** Função que garante leitura de um número inteiro, positivo, para ser usado nas demais funcionalidades desse módulo.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Int (retorna um valor do tipo inteiro apto para ser utilizado nas demais funcionalidades).
```c
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
```

### **Função:** int ehSomenteNumero(const char *str);

- **Descrição:** Garante que o número inserido seja somente um número, vedando símbolos.

- **Parâmetros de entrada:** const char *str (recebe quaisquer coisas digitadas, que não sejam números, pelo usuário).

- **Retorno:** Int (caso o usuário tenha digitado algo que não seja um número válido, a função retorna 1, e, para caso o usuário tenha digitado um número válido, ela retorna 0).
```c
int ehSomenteNumero(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') return 0;
    }
    return 1;
}
```

### **Função:** int clienteExiste(const char *nome, const char *telefone);

- **Descrição:** Função valida se o cliente já existe, recebendo suas informações de nome e telefone.

- **Parâmetros de entrada:** const char *nome, const char *telefone (a função recebe o nome e o telefone do cliente, para verificar que não haja outro cliente com essas mesmas informações).

- **Retorno:** Int (retorna 1 se caso exista outro cliente exista com essas mesmas informações, e 0 para caso não exista).
```c
int clienteExiste(const char *nome, const char *telefone) {
    FILE *f = fopen(ARQUIVO_CLIENTES, "rb");
    if (!f) return 0;

    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (strcasecmp(c.nome, nome) == 0 || strcasecmp(c.telefone, telefone) == 0) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
```

### **Função:** int gerarCodigoCliente(void);

- **Descrição:** Função que gera um ID no momento do cadastro de cada cliente, para que seja possível identificá-lo.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Int (retorna um valor inteiro, positivo, correspondente ao ID do novo cliente).
```c
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
```

### **Função:** void listarClientes(void);

- **Descrição:** Função que lista todos os clientes que foram cadastrados no sistema.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```

### **Função:** void cadastrarCliente(void);

- **Descrição:** Função que cadastra o cliente; solicita nome, endereço e telefone.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```

### **Função:** void pesquisarCliente(void);

- **Descrição:** Função que lista todos os clientes que foram cadastrados no sistema.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
            if (strcasecmp(c.nome, nomeBusca) == 0) { encontrado = 1; break; }
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
```

### **Função:** void excluirCliente(void);

- **Descrição:** Função que exclui um cliente que foi cadastrado no sistema.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```

### **Função:** menuClientes(void);

- **Descrição:** Função que exibe o menu com todas as opções correspondentes a cada uma das funcionalidades desse módulo.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```

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

## E01-F05: Cadastrar estadia

### **Função:** *static* int lerInteiroNaoNegativo(void);

- **Descrição:** Garante a leitura de um número do tipo inteiro positivo, para ser usado nas demais funcionalidades desse módulo.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Int (retorna um valor do tipo inteiro, que será utilizado nas demais funcionalidades desse módulo).
```c
static int lerIntNaoNegativo() {
    char buffer[128];
    int valor;
    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%d", &valor) == 1 && valor >= 0) return valor;
        printf("Entrada inválida! Digite um número inteiro não negativo: ");
    }
}
```

### **Função:** void lerData(int *dia, int *mes, int *ano);

- **Descrição:** Função que lê os valores que serão correspondentes as datas de início e de saída da estadia, para ser usada na funcionalidade de checkout.

- **Parâmetros de entrada:** int *dia, int *mes, int *ano (ponteiros que guardam os valores dessas informações).

- **Retorno:** Nenhum.
```c
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
```

### **Função:** int lerOpcaoMenu(void);

- **Descrição:** Lê a opção digitada pelo usuário no menu de opções deste módulo, garantindo que haja limpeza de buffer e que o menu permaneça aparecendo mesmo que o usuário digite um valor que não seja o número correspodente a alguma das opções.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Int (retorna um valor inteiro correspondete a opção escolhida pelo usuário).
```c
static int lerOpcaoMenu() {
    char buffer[64];
    int op;
    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%d", &op) == 1) return op;
        printf("Opção inválida, tente novamente: ");
    }
}
```

### **Função:** int validarCLiente (int id);

- **Descrição:** Função que garante que dois clientes não existam com o mesmo ID.

- **Parâmetros de entrada:** int id (usado para verificar que não há outro usuário com esse mesmo ID).

- **Retorno:** Int (retorna 1 para caso o ID exista em dois usuários, e 0 para caso não haja correspondências).
```c
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
```

### **Função:** int calcularDiferencaDias(int d1, int m1, int a1, int d2, int m2, int a2);

- **Descrição:** Função que recebe as datas de entrada e de saída do hóspede, e calcula quantos dias se passaram, para que seja feito cálculo de quanto ele deverá pagar.

- **Parãmetros de entrada:** int d1, int m1, int a1, int d2, int m2, int a2 (valores correspondentes as datas de entrada e de saída do hóspede, identificadas por 1 e 2, respectivamente).

- **Retorno:** Int (gera um número inteiro, positivo, correspondente a diferença entre datas).
```c
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
```

### **Função:** *static* int gerarCodigoEstadia(void);

- **Descrição:** Gera um ID no cadastro da estadia, para que seja possível identificá-la depois.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Int (retorna um valor inteiro, positivo, correspondente ao ID da estadia).

### **Função:** void cadastrarEstadia(void);

- **Descrição:** Função que cadastra a estadia, solicita código do cliente, datas de entrada e saída e quantidade de hóspedes.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```

### **Função:** void finalizarEstadia(void);

- **Descrição:** Função que dá checkout na estadia, liberando o quarto e calculando quanto o cliente deverá pagar.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```

### **Função:** void listarEstadiasPorCliente(void);

- **Descrição:** Função que lista todas as estadias que estão e que foram alugadas por um cliente.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```

### **Função:** void menuEstadias(void);

- **Descrição:** Função que exibe o menu com todas as funcionalidades do módulo de estadias.

- **Parâmetros de entrada:** Nenhum.

- **Retorno:** Nenhum.
```c
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
```
