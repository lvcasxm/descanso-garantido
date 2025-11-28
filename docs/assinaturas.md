# Assinaturas das funções

**Versão:** 1.0

**Última atualização:** 28-11-2025 | 19:49

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
