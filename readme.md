#  MIPS-like em SystemC

## Informações sobre o projeto

Projeto recebe entradas de arquivo padrão do do mips, limitadas as instruções:

AND —> operação booleana AND \
OR —> operação booleana OR \
XOR —> operação booleana XOR \
NOT —> operação booleana NOT\
SLT —> comparação\
ADD —> soma\
SUB —> subtração\
LW —> leitura em memória de uma palavra\
SW —> armazenamento em memória de uma palavra\
J —> salto incondicional\
BNE  —> salto condicional; salta se não é igual\
BEQ —> salto condicional; salta se é igual

### Modelo de instrução: 

Nosso modelo de instrução  é modelado como:

| OPCODE | REG.D (RD) | REG.O 1(R1) | REG.O 2/ offset/imediate  |
|--------|------------|-------------|----------------------------|
| 4 bits | 6 bits | 6 bits | 16 bits|


 #
# Detalhes do trabalho

### 1. PARTE OPERATIVA

Implementar os componentes individualmente e testá-los individualmente.

ULA, Banco de Registradores, Memória de Dados, Memória de Instruções, Somador, PC, buffers

### 2. PARTE DE CONTROLE

Implementar o Controle através de Máquina de Estados e testar individualmente

### 3. INTEGRAÇÃO

Integrar a Parte Operativa com a Parte de Controle



## projeto criado usando Visual Studio Code Template for SystemC
 Creditos do template usado: https://github.com/fmuller-pns/systemc-vscode-project-template.git