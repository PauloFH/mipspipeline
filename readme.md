#  MIPS-like em SystemC

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
