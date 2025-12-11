# Sprint 1 - Cadastro do cliente, funcionário, estadias e demais funcionalidades do sistema

- **Status:** Terminada
- **Responsáveis:** Ana Luiza Cavalcante e André Fortini de Melo
- **Data de início:** 05/12/2025 | 20:00
- **Data de término:** 09/12/2025 | 19:08

## Objetivo da Sprint

Implementar todas as principais funcionalidades do sistema listadas e descritas no product-backlog.md do projeto.

## Backlog da sprint

### Histórias de usuário selecionadas

- 1: O sistema deve garantir que não haja dois clientes com o mesmo código.
- 2: O sistema deve garantir qu não haja dois clientes com exatamente o mesmo nome.
- 3: O sistema deve garantir que não haja clientes diferentes com mesmo número de telefone, nem funcionários.
- 4: Telefone deve ser escrito no padrão (xx) xxxx-xxxx.
- 5: Endereço e nome devem ser armazenados em string.
- 6: O sistema deve garantir que não haja dois funcionŕios com o mesmo código.
- 7: O sistema deve garantir que não haja dois funcionários com exatamente o mesmo nome.
- 8: O sistema deve garantir que não haja dois funcionários com número de telefone iguais (também verificar com os clientes).
- 9: Telefone deve ser escrito no padrão (xx) xxxx-xxxx.
- 10: Endereço e nome devem ser armaazenados em string.
- 11: Salário deve ser guardado em inteiro
- 12: O sistema deve garantir que não haja dois quartos cadastrados com o mesmo número.
- 13: Um quarto não pode ter dois status ao mesmo tempo, deve ser ocupado ou desocupado.
- 14: O sistema deve identificar automaticamente um quarto que contenha a quantidade de hóspedes requisitada para estadia. 
- 15: O quarto que o sistema encontrar há de ter status desocupado.
- 16: O sistema deve calcular a quantidade de diárias pela subtração do tempo de entrada e saída.
- 17: Um quarto não pode ter duas estadias ao mesmo tempo.
- 18:Um cliente não pode fazer duas estadias ao mesmo tempo.
- 19: Precisa receber corretamente o tempo de estadia do hóspede.
- 20: Precisa calcular o valor total a ser pago pelo cliente.
- 21: Precisa retornar esse valor corretamente na tela.
- 22: Precisa automaticamente trocar o status de "ocupado" para "desocupado" dos respectivos quartos.
- 23: Deve ser possível pesquisar tanto por nome, quanto por código.
- 24: O resultado por nome ou código deve ser o mesmo.
- 25: Deverá ser exibido todas as informações de cadastro da pessoa em forma de lista.
- 26: Essa função deve aceitar nome ou código.
- 27: O resultado para nome ou código tem que ser iguais.
- 28: Essa função deve listar estadias ativas e estadias que já foram feitas pelo cliente.
- 29: Função deve calcular corretamente os pontos de fidelidade do cliente.
- 30: Cada diária equivale a 10 pontos.
- 31: O cliente pode ter várias estadias ao mesmo tempo, e devem ser calculados, portanto, os pontos de cada uma dessas estadias em conjunto
- 32: Criar, editar e armazenar todas as informações relacionadas a cadastro em arquivos binários.

### Funcionalidades selecionadas

### Funcionalidades do módulo de clientes: 

- 1: int limparBuffer(void);
- 2: int lerInteiro(void);
- 3: int ehSomenteNumero(void);
- 4: int gerarCodigoCliente(void);
- 5: void listarClientes(void);
- 6: void cadastrarCliente(void);
- 7: void pesquisarCliente(void);
- 8: void excluirCliente(void);
- 9: void menuClientes(void);

### Funcionalidades do módulo de funcionários

- 10: int validarNumeros(void);
- 11: int validarLetras(char *str);
- 12: int gerarCodigoFuncionario(void);
- 13: void listarFuncionario(void);
- 14: void cadastrarFuncionario(void);
- 15: void pesquisarFuncionario(void);
- 16: void excluirFuncionario(void);
- 17: void menuFuncionarios(void);

### Funcionalidades do módulo de quartos

- 18: int lerint(void);
- 19: float lerFloat(void);
- 20: void cadastrarQuarto(void);
- 21: void listarQuartos(void);
- 22: void excluirQuarto(void);
- 23: void menuQuartos(void);

### Funcionalidades do módulo de estadias

- 24: int lerIntNaoNegativo(void);
- 25: void lerData(int *dia, int *mes, int *ano);
- 26: int lerOpcaoMenu(void);
- 27: int validarCliente(void);
- 28: int calcularDiferencaDias (int d1, int m1, int a1, int d2, int m2, int a2);
- 29: int gerarCodigoEstadia(void);
- 30: void cadastrarEstadia(void);
- 31: void finalizarEstadia(void);
- 32: void listarEstadiaPorCliente(void);
- 33: void menuEstadias(void);

### Funcionalidade do módulo do sistema, que corresponde ao menu principal

- 34: void menuPrincipal(void);
- 35: void iniciarSistema(void);
