# Product Backlog

**Versão:** 2.1

**Última atualização:** 15-11-2025 | 14:33

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
- Exibir todas as funções especificadas no épico
- Menu deve corretamente permanecer em loop até que o usuário decida sair
- Usuário consegue navegar para cada funcionalidade corretamente
- Usuário consegue retornar ao menu principal caso haja necessidade
- Todas as informações deverão ser persistidas em arquivos binários

**Sprint:** [a definir]

**Prioridade:** [alta]

**Responsáveis:** [a definir]

--- 

# Changelog

### 1.0 | 14-11-2025 | 13:06 | Lucas
- criado texto inicial de explicação do documento e de formatação.

### 2.0 | 15-11-2025 | 14:01 | Lucas
- adicionei épico principal que engloba todas as funcionalidades que serão exibidas no menu principal e que deverão ser descritas depois. caso haja outras não há necesisdade de criar outro épico, só descrevê-las individualmente mesmo.

### 2.1 | 15-11-2025 | 14:33 | Lucas
- Adicionei primeira funcionalidade derivada do épico principal do sistema; funcionalidade de menu.
