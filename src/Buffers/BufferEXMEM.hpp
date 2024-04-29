#include <systemc.h>

SC_MODULE(BufferEXMEM) {
    sc_in<bool> clk;
    sc_in<T> inputData;
    sc_in<bool> inM;
    sc_in<bool> inWB;
    sc_in<bool> inEX;
    sc_out<bool> outEx;
    sc_out<bool> outM;
    sc_out<bool> outWB;
    sc_out<T> outputData;

    T storedData;
    bool storedControlSignal;

    void bufferProcess() {
        while (true) {
            wait(); // Aguarda por mudanças no clock

            // Armazena os dados de entrada e o sinal de controle recebidos
            storedData = inputData.read();
            storedControlSignal = controlSignal.read();

            // Envia os dados armazenados para o próximo estágio
            outputData.write(storedData);

            // Você pode usar o sinal de controle armazenado como necessário no próximo estágio
            // Por exemplo, controlar a habilitação de operações, condições de desvio, etc.
        }
    }

    SC_CTOR(Buffer) {
        // Inicializa os sinais de saída
        outputData.initialize(0); // Pode ser inicializado com um valor padrão se necessário

        // Criação do processo SC_THREAD para o buffer
        SC_THREAD(bufferProcess);

        // O processo é sensível à borda de subida do clock
        sensitive << clk.pos();
    }
};
