# Plano de testes para cada funcionalidade

## Módulo de Funcionários — Planejamento e Execução de Testes

1. Função: pesquisarFuncionario()
Planejamento dos Testes
Caso de Teste 1

Cenário: Buscar funcionário por ID existente
Entrada:

Opção: 1

ID informado: 10
Procedimento:

Sistema lista funcionários.

Usuário escolhe opção 1.

Usuário insere ID 10.

Função percorre arquivo até encontrar o registro.
Saída Esperada:

Dados completos do funcionário de ID 10 exibidos.

Caso de Teste 2

Cenário: Buscar funcionário por ID inexistente
Entrada:

Opção: 1

ID: 999
Procedimento: Igual ao caso anterior.
Saída Esperada:

Mensagem: "Funcionário não encontrado no sistema."

Caso de Teste 3

Cenário: Buscar funcionário por nome correspondente
Entrada:

Opção: 2

Nome: "Maria Santos"
Procedimento:

Sistema lista funcionários.

Usuário escolhe opção 2.

Informa nome exato.

Função usa strcasecmp até encontrar match.
Saída Esperada:

Dados completos da funcionária exibidos.

Caso de Teste 4

Cenário: Buscar funcionário por nome inexistente
Entrada:

Opção: 2

Nome: "Fulano XYZ"
Saída Esperada:

"Funcionário não encontrado no sistema."

Caso de Teste 5

Cenário: Usuário insere opção inválida
Entrada:

Opção: 7
Saída Esperada:

"[!] Opção inexistente!"

Execução encerrada antes da busca.

Relatório de Execução dos Testes
Caso 1 — Resultado

Status: Aprovado
Comportamento observado: Funcionário ID 10 exibido corretamente.

Caso 2 — Resultado

Status: Aprovado
Comportamento observado: Mensagem de não encontrado exibida.

Caso 3 — Resultado

Status: Aprovado
Comportamento observado: Nome “Maria Santos” localizado; dados exibidos.

Caso 4 — Resultado

Status: Aprovado
Comportamento observado: Função percorreu arquivo e exibiu mensagem de não encontrado.

Caso 5 — Resultado

Status: Aprovado
Comportamento observado: Opção inválida tratada corretamente.

2. Função: excluirFuncionario()
Planejamento dos Testes
Caso de Teste 1

Cenário: Exclusão de funcionário existente
Entrada:

ID: 15
Procedimento:

Sistema lista funcionários.

Usuário fornece ID 15.

Função copia todos os registros exceto ID 15 para arquivo temporário.

Substitui arquivo original.
Saída Esperada:

"[✓] Funcionário removido com sucesso."

Caso de Teste 2

Cenário: Tentativa de exclusão de funcionário inexistente
Entrada:

ID: 777
Saída Esperada:

"ID 777 não encontrado."

Caso de Teste 3

Cenário: Arquivo de funcionários não existe
Entrada:

ID qualquer
Procedimento:

Sistema tenta abrir o arquivo.
Saída Esperada:

Função retorna imediatamente sem falha de execução.

Caso de Teste 4

Cenário: Arquivo contendo somente um registro, que será excluído
Entrada:

ID do único funcionário existente
Saída Esperada:

Mensagem de sucesso.

Arquivo resultante vazio após renomear.

Relatório de Execução dos Testes
Caso 1 — Resultado

Status: Aprovado
Comportamento observado: ID 15 removido, arquivo atualizado corretamente.

Caso 2 — Resultado

Status: Aprovado
Comportamento observado: ID 777 não encontrado; mensagem exibida.

Caso 3 — Resultado

Status: Aprovado
Comportamento observado: Ausência do arquivo original tratada; função encerrou sem erros.

Caso 4 — Resultado

Status: Aprovado
Comportamento observado: Registro único removido; arquivo final sem registros.

## Plano de testes para o módulo de cliente

1. Função: listarClientes()
Planejamento dos Testes
Caso de Teste 1

Cenário: Arquivo inexistente ou vazio
Entrada:

Nenhuma (função sem parâmetros).
Procedimento:

Função tenta abrir ARQUIVO_CLIENTES.

fopen retorna nulo.
Saída Esperada:

"[!] Nenhum cliente cadastrado."

Execução encerrada.

Caso de Teste 2

Cenário: Listagem com um único cliente
Arquivo contém:

Cliente: {codigo = 1, nome = "Lucas Andrade"}
Procedimento:

Ler registro único via fread.
Saída Esperada:

Título da lista.

Linha do cliente com formatação correta.

Linha de fechamento.

Caso de Teste 3

Cenário: Listagem com vários clientes
Arquivo contém:

Dois ou mais registros válidos.
Saída Esperada:

Impressão de todos os clientes na ordem de leitura, formatados.

Caso de Teste 4

Cenário: Nome longo próximo ao limite (30 caracteres)
Arquivo contém: nome com 28–30 caracteres
Saída Esperada:

Nome exibido corretamente dentro da largura reservada.

Colunas alinhadas.

Relatório de Execução — listarClientes()
Caso 1 — Resultado

Status: Aprovado
Comportamento observado: Mensagem de ausência de clientes exibida.

Caso 2 — Resultado

Status: Aprovado
Comportamento observado: Registro único exibido com alinhamento correto.

Caso 3 — Resultado

Status: Aprovado
Comportamento observado: Todos os registros lidos e impressos sem falhas.

Caso 4 — Resultado

Status: Aprovado
Comportamento observado: Nome extenso respeitou o espaçamento; tabela manteve alinhamento.

2. Função: gerarCodigoCliente()
Planejamento dos Testes
Caso de Teste 1

Cenário: Arquivo inexistente
Entrada: Nenhuma
Procedimento:

fopen retorna nulo.
Saída Esperada:

Retorno: 1.

Caso de Teste 2

Cenário: Arquivo com apenas um cliente
Arquivo contém:

Cliente: {codigo = 7}
Saída Esperada:

Retorno: 8.

Caso de Teste 3

Cenário: Arquivo com múltiplos clientes
Arquivo contém:

{codigo = 2}, {codigo = 5}, {codigo = 9}
Saída Esperada:

Retorno: 10.

Caso de Teste 4

Cenário: Arquivo com códigos fora de ordem
Arquivo contém:

{codigo = 15}, {codigo = 3}, {codigo = 22}, {codigo = 11}
Saída Esperada:

Retorno: 23.

Caso de Teste 5

Cenário: Registro com código inválido (zero ou negativo)
Arquivo contém:

{codigo = 0}, {codigo = -4}, {codigo = 2}
Procedimento:

Função procura o maior código positivo.
Saída Esperada:

Retorno: 3.

Relatório de Execução — gerarCodigoCliente()
Caso 1 — Resultado

Status: Aprovado
Comportamento observado: Retorno igual a 1 quando o arquivo não existe.

Caso 2 — Resultado

Status: Aprovado
Comportamento observado: Retorno igual a 8 conforme esperado.

Caso 3 — Resultado

Status: Aprovado
Comportamento observado: Maior código identificado corretamente (9), retorno 10.

Caso 4 — Resultado

Status: Aprovado
Comportamento observado: Maior código (22) detectado; retorno 23.

Caso 5 — Resultado

Status: Aprovado
Comportamento observado: Códigos inválidos ignorados; retorno 3.

## Plano de testes para o módulo de quartos

1. Função: excluirQuarto()
Planejamento dos Testes
Caso de Teste 1

Cenário: Exclusão de quarto existente e desocupado
Entrada:

Número: 105
Arquivo contém:

{numero=105, status="livre"}
Procedimento:

Função lista quartos.

Usuário fornece 105.

Registro é lido; não está ocupado.

Registro não é escrito no arquivo temporário.

Arquivo original substituído.
Saída Esperada:

"[✓] Quarto removido com sucesso."

Caso de Teste 2

Cenário: Tentativa de excluir quarto inexistente
Entrada:

Número: 999
Saída Esperada:

"[!] Quarto não encontrado."

Caso de Teste 3

Cenário: Tentativa de excluir quarto ocupado
Entrada:

Número: 210
Arquivo contém:

{numero=210, status="ocupado"}
Procedimento:

Registro lido.

Função detecta status "ocupado".

Exibe aviso.

Registro é mantido (gravado no temp).
Saída Esperada:

"[!] Não é possível excluir um quarto OCUPADO!"

Ao final, mensagem final deve indicar quarto não encontrado para remoção.

Caso de Teste 4

Cenário: Arquivo de quartos inexistente ou inacessível
Entrada:

Número qualquer
Saída Esperada:

"[!] Erro ao abrir arquivos."

Caso de Teste 5

Cenário: Arquivo com um único quarto, desocupado
Entrada:

Número do único quarto
Saída Esperada:

Remoção realizada

Arquivo resultante sem registros

Relatório de Execução — excluirQuarto()
Caso 1 — Resultado

Status: Aprovado
Comportamento observado: Quarto 105 removido e não preservado no temporário.

Caso 2 — Resultado

Status: Aprovado
Comportamento observado: Número 999 não encontrado; mensagem exibida.

Caso 3 — Resultado

Status: Aprovado
Comportamento observado: Quarto ocupado gerou aviso; registro mantido; remoção não realizada.

Caso 4 — Resultado

Status: Aprovado
Comportamento observado: Erro ao abrir arquivos exibido corretamente.

Caso 5 — Resultado

Status: Aprovado
Comportamento observado: Registro único removido; arquivo final vazio.

2. Função: listarQuartos()
Planejamento dos Testes
Caso de Teste 1

Cenário: Arquivo inexistente ou vazio
Procedimento:

fopen retorna nulo.
Saída Esperada:

"[!] Nenhum quarto cadastrado."

Caso de Teste 2

Cenário: Listagem com um registro
Arquivo contém:

{numero=101, qtdHospedes=2, valorDiaria=150.00, status="livre"}
Saída Esperada:

Cabeçalho

Linha única exibida com formatação adequada

Caso de Teste 3

Cenário: Listagem com múltiplos registros
Saída Esperada:

Todos os quartos exibidos na ordem de leitura

Caso de Teste 4

Cenário: Campos no limite
Arquivo contém:

Valores extremos, como:

capacidade muito alta (ex: 12)

valor com muitas casas decimais

status no limite de tamanho permitido
Saída Esperada:

Impressão formatada corretamente

Caso de Teste 5

Cenário: Arquivo com registros mistos (ocupado, livre, manutenção)
Saída Esperada:

Todos os status impressos sem falhas

Relatório de Execução — listarQuartos()
Caso 1 — Resultado

Status: Aprovado
Comportamento observado: Mensagem de arquivo vazio exibida.

Caso 2 — Resultado

Status: Aprovado
Comportamento observado: Registro único exibido com alinhamento correto.

Caso 3 — Resultado

Status: Aprovado
Comportamento observado: Todos os quartos impressos com o layout da tabela preservado.

Caso 4 — Resultado

Status: Aprovado
Comportamento observado: Valores extremos não quebraram o layout.

Caso 5 — Resultado

Status: Aprovado
Comportamento observado: Status variados impressos adequadamente.

## Plano de testes para o módulo de estadias

Função: cadastrarEstadia()
Planejamento dos Testes
Caso de Teste 1

Cenário: Cliente inexistente
Entradas:

Código do cliente: 999
Procedimento:

validarCliente(999) retorna falso.
Saída Esperada:

"[!] Cliente de código 999 não encontrado!"

Lista de clientes exibida.

Processo encerrado antes da escolha de datas.

Caso de Teste 2

Cenário: Datas inválidas (saída antes da entrada)
Entradas:

Cliente válido: 12

Data entrada: 10 05 2025

Data saída: 08 05 2025
Procedimento:

calcularDiferencaDias retorna valor ≤ 0.
Saída Esperada:

"[!] Período inválido. A saída deve ser depois da entrada."

Caso de Teste 3

Cenário: Número de hóspedes igual a zero
Entradas:

Cliente válido

Datas válidas

Hóspedes: 0
Saída Esperada:

"[!] Número de hóspedes deve ser maior que zero."

Caso de Teste 4

Cenário: Arquivo de quartos inacessível
Entradas:

Cliente válido

Datas válidas

Hóspedes válidos
Procedimento:

fopen(ARQUIVO_QUARTOS, "rb+") retorna nulo.
Saída Esperada:

"[!] Não foi possível acessar cadastro de quartos."

Caso de Teste 5

Cenário: Não há quarto compatível com a quantidade de hóspedes
Arquivo de quartos contém:

Todos ocupados ou capacidade insuficiente
Saída Esperada:

"[!] Nenhum quarto disponível para X hóspede(s)."

Caso de Teste 6

Cenário: Quarto disponível encontrado e marcado como ocupado
Arquivo de quartos contém:

Um quarto "desocupado"

q.qtdHospedes >= hospedes
Procedimento:

Leitura do quarto.

Alteração do status para "ocupado".

fseek para regravar o registro.

Geração e gravação da estadia no arquivo de estadias.
Saída Esperada:

"[✓] Estadia registrada (ID X) no quarto Y para Z diária(s)."

Caso de Teste 7

Cenário: Falha ao gravar a estadia
Procedimento:

fopen(ARQUIVO_ESTADIAS, "ab") retorna nulo.

Quarto já está marcado como ocupado, mas estadia não grava.
Saída Esperada:

"[!] Erro ao gravar estadia."

Caso de Teste 8

Cenário: Múltiplos quartos; função deve escolher o primeiro compatível
Arquivo contém:

Quarto 201 — desocupado, capacidade 4

Quarto 305 — desocupado, capacidade 2
Entradas:

Hóspedes: 2
Saída Esperada:

Deve escolher o quarto 201, não o 305.

Relatório de Execução — cadastrarEstadia()
Caso 1 — Resultado

Status: Aprovado
Comportamento observado: Cliente inexistente encerrou o fluxo corretamente.

Caso 2 — Resultado

Status: Aprovado
Comportamento observado: Datas inválidas foram detectadas com a mensagem prevista.

Caso 3 — Resultado

Status: Aprovado
Comportamento observado: Valor zero de hóspedes bloqueou o cadastro.

Caso 4 — Resultado

Status: Aprovado
Comportamento observado: Função interrompeu ao não conseguir abrir cadastro de quartos.

Caso 5 — Resultado

Status: Aprovado
Comportamento observado: Nenhuma acomodação compatível; aviso exibido.

Caso 6 — Resultado

Status: Aprovado
Comportamento observado: Quarto alterado para "ocupado"; estadia gravada com sucesso.

Caso 7 — Resultado

Status: Aprovado
Comportamento observado: Falha ao gravar estadia produziu a mensagem correta.

Caso 8 — Resultado

Status: Aprovado
Comportamento observado: Primeiro quarto compatível foi selecionado.
