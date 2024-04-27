#include <systemc.h>

#define MEMORY_SIZE 1024 // Tamanho da memória de instruções (em número de palavras)

SC_MODULE(InstructionMemory) {
    sc_in<bool> clk; // Sinal de clock
    sc_in<int> pc; // Program Counter (PC)
    sc_out<int> instruction; // Saída: instrução buscada

    int memory[MEMORY_SIZE]; // Memória de instruções (simulada como um array de inteiros)

    // Construtor do módulo
    SC_CTOR(InstructionMemory) {
        // Inicializa a memória de instruções com valores fictícios (para fins de exemplo)
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            memory[i] = rand() % 256; // Preenche a memória com valores aleatórios (instruções de 8 bits)
        }

        // Processo sensível ao flanco de subida do clock
        SC_METHOD(fetchInstruction);
        sensitive << clk.pos();
    }

    // Método para buscar a instrução da memória de instruções com base no PC atual
    void fetchInstruction() {
        int addr = pc.read(); // Obtém o valor atual do PC
        instruction.write(memory[addr]); // Lê a instrução da memória de instruções
    }
};
