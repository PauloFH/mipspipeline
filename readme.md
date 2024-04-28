#  MIPS-like em SystemC
###  Descrição do Trabalho:
 Implementar um modelo de processador (Parte de Controle/Parte Operativa)  "MIPS-like" o seguinte conjunto de instruções:
AND —> operação booleana AND

OR —> operação booleana OR

XOR —> operação booleana XOR

NOT —> operação booleana NOT

CMP —> comparação

ADD —> soma

SUB —> subtração

LD —> leitura em memória

ST —> armazenamento em memória

J —> salto incondicional

JN —> salto condicional; salta se (N)egativo

JZ —> salto condicional; salta se (Z)ero

### Decisões de projeto:
 Três modos de endereçamento de operandos (registrador, memória e imediato);

### O trabalho consiste de:

#### Implementação do modelo da arquitetura em linguagem para descrição de hardware (SystemC);

#### Resultados de simulações da execução de instruções de pelo menos 3 algoritmos na arquitetura.

#### análises de desempenho (ciclos de relógio necessários à execução das instruções) em função dos comportamentos do pipeline. Entende-se por comportamentos do pipeline, os tratamentos implementados para as dependências de dados e de controle;

 

### Apresentação dias 30/04 e 02/05 em sala de aula, exemplificando o funcionando do modelo de processador implementado. A apresentação deve mostrar:

#### resultados de simulação (telas ou demonstração).

 

### Entrega dia 30/04/24 via tarefa SIGAA.
 

## Metodologia de Projeto:

### 1. PARTE OPERATIVA

Implementar os componentes individualmente e testá-los individualmente.

ULA, Banco de Registradores, Memória de Dados, Memória de Instruções, Somador, PC, buffers

### 2. PARTE DE CONTROLE

Implementar o Controle através de Máquina de Estados e testar individualmente

### 3. INTEGRAÇÃO

Integrar a Parte Operativa com a Parte de Controle



## projeto criado usando Visual Studio Code Template for SystemC
- Creditos do template usado: https://github.com/fmuller-pns/systemc-vscode-project-template.git

Segue abaixo, recomendações do desenvolvedor do template para facilitar depuração, documentação, buildagem e execução.


#### 9. Building and running project
In the Menu, Run `Start Debugging` or `Run Without Debbuging`

To exit monitoring, typing `Ctrl+AltGr+]`

## Useful Commands 

#### Open external terminal from Visual Studio Code to perform commands

  * using keyboard shortcut: `Ctrl+Shift+C`
  * or pressing `F1` key and typing `external`

#### Open integrated terminal from Visual Studio Code to perform commands

  * using keyboard shortcut: `Ctrl+Shift+`<sup>2</sup>
  * or pressing `F1` key and typing `integrated`

#### Clean project
```bash
make clean
```

#### Build and run the project
```bash
make run
```
To exit monitoring, typing `Ctrl+AltGr+]`

#### For help
```bash
make help
```

## Using Tasks for SystemC to run, debug Project and so on

1. In the menu, select `Run Task...`
2. Select the task you want to launch:
- `SystemC - Build`: build the project
- `SystemC - Run`: Run the project
- `SystemC - Run GTKWave`: Run GTKWave
- `SystemC - Clean`: Clean project (Full clean)  
- `SystemC - Doxygen - HTML doc.`: Generate HTML documentation with Doxygen
