# Product Backlog

**Versão:** 2.8

**Última atualização:** 15-11-2025 | 18:51

**Autores:** Lucas, André e Ana

---

## Motivação do documento e demais explicações
Este arquivo contém todas os requisitos funcionais que serão elicitados durante desenvolvimento do projeto, acompanhados de:
- Critérios de aceite
- Prioridade
- Responsáveis
- Em qual sprint serão feitos

O documento será atualizado sempre que houver mudanças em alguma dessas categorias, atualizando, ao final do arquivo, o changelog. A formatação do changelog foi definida da seguinte forma:

### "nova-versão | data | horário | autor
- Descrição de mudança x
- Descrição de mudança y
- Descrição de mudança z

---

# Funcionalidades

## Épico: Menu principal do sistema
**Descrição:** Agrupar todas as funcionalidades relacionadas ao menu inicial do sistema, exibindo funções de cadastro, navegação e saída

**Funcionalidades íncluídas:**
- Exibir menu principal em loop, até que o usuário escolha opção de "Sair".
- Cadastrar cliente
- Cadastrar funcionário
- Cadastrar quarto
- Cadastrar estadia
- Pesquisas pelo código dos hóspedes
- Dar baixa nas estadias
- Todas as informações deverão ser persistidas em arquivos binários

### E01-F01: Exibir menu
**Descrição:** Ao iniciar o programa, o sistema deve exibir um menu exibindo opções de cadastro, pesquisa e saída. O menu deve permanecer em loop até que o usuário opte por sair.

**Critérios de aceite:** 
- Exibir todas as funções especificadas no épico.
- Menu deve corretamente permanecer em loop até que o usuário decida sair.
- Usuário consegue navegar para cada funcionalidade corretamente.
- Usuário consegue retornar ao menu principal caso haja necessidade.
- Todas as informações deverão ser persistidas em arquivos binários.

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

### E01-F02: Cadastrar cliente
**Descrição:** Essa função deve cadastrar o cliente, contendo as informações: código, nome, endereço e telefone.

**Critérios de aceite:**
- O sistema deve garantir que não haja dois clientes com o mesmo código.
- O sistema deve garantir qu não haja dois clientes com exatamente o mesmo nome.
- Telefone deve ser escrito no padrão (xx) xxxx-xxxx.
- Endereço e nome devem ser armazenados em string.

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

### E01-F03: Cadastrar funcionário
**Descrição:** Essa função deve cadastrar os funcionários do hotel, contendo: código, nome, telefone, cargo e salário.

**Critérios de aceite:** 
- O sistema deve garantir que não haja dois funcionŕios com o mesmo código.
- O sistema deve garantir que não haja dois funcionários com exatamente o mesmo nome.
- Telefone deve ser escrito no padrão (xx) xxxx-xxxx.
- Endereço e nome devem ser armaazenados em string.
- Salário deve ser guardado em inteiro

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

### E01-F04: Cadastrar quarto
**Descrição:** Essa função deve cadastrar um quarto, contendo: número do quarto, quantidade de hóspedes, valor da diária e status (desocupado ou ocupado).

**Critérios de aceite:**
- O sistema deve garantir que não haja dois quartos cadastrados com o mesmo número.

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

### E01-F05: Cadastrar estadia
**Descrição:** Essa função deve cadastrar uma estadia, recebendo: código do cliente, número do quarto, data de entrada, saída, e quantidade de hóspedes.

**Critérios de aceite:**
- O sistema deve identificar automaticamente um quarto que contenha a quantidade de hóspedes requisitada para estadia. 
- O quarto que o sistema encontrar há de ter status desocupado.
- O sistema deve calcular a quantidade de diárias pela subtração do tempo de entrada e saída.
- Um quarto não pode ter duas estadias ao mesmo tempo.
- Um cliente não pode fazer duas estadias ao mesmo tempo.

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

### E01-F06: Função que dá baixa nas estadias
**Descrição:** Essa função dá baixa nas estadias, calculando e mostrando o valor total que deverrá ser pago pelo cliente. Muda automaticamente o status do quarto para desocupado.

**Critérios de aceite:**
- Precisa receber corretamente o tempo de estadia do hóspede.
- Precisa calcular o valor total a ser pago pelo cliente.
- Precisa retornar esse valor corretamente na tela.
- Precisa automaticamente trocar o status de "ocupado" para "desocupado" dos respectivos quartos.

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

### E01-F07: Pesquisar clientes e funcionários
**Descrição:** Essa função permite que, por meio do nome ou código, seja possível exibir todas as informações de cadastro correspondentes a essa determinada pessoa.

**Critérios de aceite:**
- Deve ser possível pesquisar tanto por nome, quanto por código.
- O resultado por nome ou código deve ser o mesmo.
- Deverá ser exibido todas as informações de cadastro da pessoa em forma de lista.

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

### E01-F08: Listar todas as estadias de determinado cliente
**Descrição:** Por meio de nome ou código, essa função exibe na tela todas as estadias que foram alugadas por determinado cliente.

**Critérios de aceite:**
- Essa função deve aceitar nome ou código.
- O resultado para nome ou código tem que ser iguais.
- Essa função deve listar estadias ativas e estadias que já foram feitas pelo cliente.

**Sprint:** [a definir]

**Prioridade:** [a definir]

**Responsáveis:** [a definir]

--- 

# Changelog

### 1.0 | 14-11-2025 | 13:06 | Lucas
- Criado texto inicial de explicação do documento e de formatação.

### 2.0 | 15-11-2025 | 14:01 | Lucas
- Adicionei épico principal que engloba todas as funcionalidades que serão exibidas no menu principal e que deverão ser descritas depois. caso haja outras não há necesisdade de criar outro épico, só descrevê-las individualmente mesmo.

### 2.1 | 15-11-2025 | 14:33 | Lucas
- Adicionei primeira funcionalidade derivada do épico principal do sistema; funcionalidade de menu.

### 2.2 | 15-11-2025 | 14:43 | Lucas
- Adicionei funcionalidade de cadastrar cliente.

### 2.3 | 15-11-2025 | 14:48 | Lucas
- Adicionei funcionalidade de cadastrar funcionário.

### 2.4 | 15-11-2025 | 14:56 | Lucas
- Adicionei funcionalidade de cadastrar quarto.

### 2.5 | 15-11-2025 | 18:21 | Lucas
- Adicionei funcionalidade de cadastrar estadias.

### 2.6 | 15-11-2025 | 18:40 | Lucas
- Adicionei funcionalidade de dar baixa em estadias.

### 2.7 | 15-11-2025 | 18:45 | Lucas
- Adicionei funcionalidade de pesquisar por clientes ou funcionários, exibindo na tela todas as informações de cadastro deles.

### 2.8 | 15-11-2025 | 18:51 | Lucas
- Adicionei função de listar estadias de determinado cliente, por meio de seu nome ou código.
