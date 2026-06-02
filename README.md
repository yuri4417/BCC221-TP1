# Sistema de Gerenciamento Bancário

Projeto desenvolvido para a disciplina BCC221 - Programação Orientada a Objetos, utilizando a linguagem C++.

## Descrição

O sistema simula operações básicas de um banco, permitindo o gerenciamento de clientes, gerentes, transações bancárias, conta corrente e poupança, caderneta de poupança e cartões de crédito.

Os dados são armazenados em arquivos binários, possibilitando a persistência das informações entre execuções do programa.

## Funcionalidades

### Cadastro de Clientes

- Cadastro completo de clientes com nome, login, senha, data de nascimento e profissão.
- Definição automática de ID único para cada cliente.
- Associação obrigatória de um gerente durante o cadastro.
- Suporte a diferentes tipos de conta bancária.
- Armazenamento de remuneração, saldo e taxa de rendimento.

### Cadastro de Gerentes

- Cadastro de gerentes com informações pessoais e profissionais.
- Geração automática de ID único.
- Associação de múltiplos clientes ao gerente.
- Controle dos clientes sob responsabilidade de cada gerente.

### Criar Transação

- Realização de depósitos.
- Realização de saques com validação de saldo.
- Transferências entre clientes.
- Transferências para múltiplos destinatários em uma única operação.
- Validação por senha antes da confirmação da operação.
- Registro de data, horário e participantes da transação.

### Associar Gerente a Cliente

- Vinculação de clientes a gerentes já cadastrados.
- Alteração de gerente responsável por um cliente.
- Remoção automática do cliente da lista do gerente anterior.
- Controle da quantidade de clientes associados a cada gerente.

### Listar Cliente

- Exibição de todos os clientes cadastrados.
- Busca de cliente pelo nome.
- Visualização completa dos dados do cliente.
- Exibição de informações bancárias e gerente associado.

### Listar Gerente

- Exibição de todos os gerentes cadastrados.
- Busca de gerente pelo nome.
- Visualização dos dados completos do gerente.
- Exibição da lista de clientes associados.

### Exibir Extrato de um Cliente

- Consulta do histórico de transações do cliente.
- Exibição de depósitos, saques e transferências.
- Visualização de data, horário e valor das operações.
- Identificação de remetentes e destinatários envolvidos.

### Gerenciar Cartão de Crédito

- Criação de cartão de crédito por um gerente autorizado.
- Geração automática do número do cartão.
- Definição de limite inicial com base na renda do cliente.
- Bloqueio e desbloqueio do cartão.
- Alteração de limite de crédito.
- Pagamento de faturas.
- Compras parceladas com controle de parcelas futuras.
- Consulta das informações do cartão.
- Controle de limite disponível e faturas pendentes.

### Calcular rendimento da caderneta de poupança

- Aplicação automática do rendimento em contas poupança.
- Cálculo baseado na taxa cadastrada para cada cliente.
- Atualização do saldo após a aplicação do rendimento.
- Exibição do valor rendido para cada cliente.

### Salvar dados e sair

- Persistência dos dados em arquivos CSV.
- Salvamento de clientes, gerentes e transações.
- Armazenamento das informações dos cartões de crédito.
- Recuperação automática dos dados ao iniciar o sistema.
- Encerramento seguro da aplicação.
- Confirmação antes de sair.
- Liberação da memória alocada dinamicamente.

## Requisitos

- Linux
- Compilador GCC/G++ com suporte ao padrão C++17
- Make

Verificar instalação:

```bash
g++ --version
make --version
```

## Compilação

Na pasta raiz do projeto execute:

```bash
make
```

O executável será gerado com o nome:

```bash
main
```

## Execução

Após a compilação:

```bash
make run
```

ou

```bash
./main
```

## Limpeza dos Arquivos Objeto

Para remover arquivos compilados:

```bash
make clean
```
