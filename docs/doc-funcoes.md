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

int cadastrarFuncionario(Funcionario *funcionario);

- **Função:** cadastrarFuncionario.

- **Descrição:** Realiza o cadastro completo de um novo funcionário no sistema.

- **Parâmetros de entrada:** 
funcionário: Ponteiro para estrutura funcionário a ser preenchida

- **Retorno:** int
0: cadastro realizado com sucesso.
1: erro no cadastro (código duplicado).
2: erro no cadastro (nome duplicado).
3: erro no cadastro (telefone duplicado).

- **Retorno:** bool
true: Código já existe
false: Código disponível

- **Função:** verificarNomeFuncionarioExiste

bool verificarCodigoFuncionarioExiste

- **Descrição:** Verifica se já existe um funcionário com o código informado.

- **Parâmetros de entrada:** 
código: Código do funcionário a ser verificado.

- **Retorno:** bool
true: Código já existe
false: Código disponível

- **Função:** verificarNomeFuncionarioExiste

bool verificarNomeFuncionarioExiste(const char *nome);

- **Descrição:** Verifica se já existe um funcionário com nome exato.

- **Parâmetros de entrada:** 
nome: String contendo o nome a ser verificado.

- **Retorno:** bool
true: Nome já existe
False: Nome disponível
