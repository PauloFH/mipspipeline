#include <systemc.h>

#define MEMORY_SIZE 1024 // Tamanho da memória de dados (em número de palavras)

SC_MODULE(DataMemory) {
    sc_in<bool> clk; // Sinal de clock
    sc_in<bool> wr_en; // Sinal de habilitação de escrita
    sc_in<int> write_addr; // Endereço de escrita
    sc_in<int> write_data; // Dado a ser escrito
    sc_in<int> read_addr; // Endereço de leitura
    sc_out<int> read_data; // Dado lido

    int memory[MEMORY_SIZE]; // Memória de dados (simulada como um array de inteiros)

    // Construtor do módulo
    SC_CTOR(DataMemory) {
        // Inicializa a memória de dados com valores fictícios (para fins de exemplo)
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            memory[i] = rand() % 256; // Preenche a memória com valores aleatórios (dados de 8 bits)
        }

        // Processo sensível ao flanco de subida do clock
        SC_METHOD(memoryOperation);
        sensitive << clk.pos();
    }

    // Método para ler ou escrever na memória de dados
    void memoryOperation() {
        if (wr_en.read() == true) {
            // Escrita na memória
            int addr = write_addr.read();
            memory[addr] = write_data.read();
        } else {
            // Leitura na memória
            int addr = read_addr.read();
            read_data.write(memory[addr]);
        }
    }
};
