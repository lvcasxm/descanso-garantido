# Product Backlog

**Versão:** 2.4

**Última atualização:** 15-11-2025 | 14:56

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

### 2.4 | 15-11-2025 | 14:56| Lucas
- Adicionei funcionalidade de cadastrar quarto.
