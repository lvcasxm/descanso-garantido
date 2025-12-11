# Assinatura das funções

## Módulo do sistema, referente aos menus de exibição principais

- void menuPrincipal();
- void menuPrincipal();

## Módulo de clientes

- void limparBuffer(void);
- int lerInteiro(void);
- int ehSomenteNumero(const char *str);
- int clienteExiste(const char *nome, const char *telefone);
- int gerarCodigoCliente(void);
- void listarClientes(void);
- void cadastrarCliente(void);
- void pesquisarCliente(void);
- void excluirCliente(void);
- void menuClientes(void);

## Módulo de funcionários

- int gerarCodigoFuncionario(void);
- void listarFuncionarios(void);
- void cadastrarFuncionario(void);

## Módulo dos quartos

- void lerint(void);
- float lerFloat(void);
- void cadastrarQuarto(void);
- void listarQuartos(void);
- void excluirQuarto(void);
- void menuQuartos(void);

## Módulo de estadias

- *static* int lerInteiroNaoNegativo(void);
- void lerData(int *dia, int *mes, int *ano);
- int lerOpcaoMenu(void);
- int validarCLiente (int id);
- int calcularDiferencaDias(int d1, int m1, int a1, int d2, int m2, int a2);
- *static* int gerarCodigoEstadia(void);
- void finalizarEstadia(void);
- void listarEstadiasPorCliente(void);
- void menuEstadias(void);
