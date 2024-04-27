#include <systemc.h>

SC_MODULE(ProgramCounter) {
    sc_in<bool> clk; // Sinal de clock
    sc_in<bool> reset; // Sinal de reset (opcional)
    sc_out<int> pc; // Saída: valor atual do Program Counter (PC)

    int current_address; // Endereço atual do Program Counter

    // Construtor do módulo
    SC_CTOR(ProgramCounter) {
        current_address = 0; // Inicializa o Program Counter com zero

        // Processo sensível ao flanco de subida do clock
        SC_METHOD(incrementPC);
        sensitive << clk.pos();

        // Processo sensível ao sinal de reset
        if (reset) {
            SC_METHOD(resetPC);
            sensitive << reset;
        }
    }

    // Método para incrementar o Program Counter no flanco de subida do clock
    void incrementPC() {
        current_address++; // Incrementa o Program Counter
        pc.write(current_address); // Escreve o valor atual do PC na saída
    }

    // Método para resetar o Program Counter quando o sinal de reset for ativado
    void resetPC() {
        current_address = 0; // Reinicia o Program Counter para zero
        pc.write(current_address); // Escreve o valor atual do PC na saída após o reset
    }
};
