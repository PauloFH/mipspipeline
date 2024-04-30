#include <systemc.h>

SC_MODULE(BufferEXMEM) {
  sc_in<bool> clk;
    sc_in<int> aluData;
    sc_in<int> ReadData;
    sc_in<int> addData;
    sc_in<int>muxData;
    sc_in<bool> inM;
    sc_in<bool> inWB;
    sc_out<bool> outM;
    sc_out<bool> outWB;
    sc_out<int> outputData1;
     sc_out<int> outputData2; 
    int storedData1,storedData2;
    bool internalM, internalWB;
    int storedData;

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
