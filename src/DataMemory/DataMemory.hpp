#include <systemc.h>

#define MEMORY_SIZE 4096

SC_MODULE(DataMemory)
{
    sc_in<bool> clk;
    sc_in<bool> memWrite;
    sc_in<bool> enable;
    sc_in<sc_int<32>> write_data;
    sc_in<sc_int<32>> address;
    sc_out<sc_int<32>> readData;

    sc_uint<16> internoAdress;

    sc_int<32> memory[MEMORY_SIZE];

    void memoryOperation()
    {
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Data Memory" << endl
             << "clk: " << clk.read() << endl
             << "memWrite: " << memWrite.read() << endl
             << "enable: " << enable.read() << endl
             << "write_data: " << write_data.read() << endl
             << "address: " << address.read() << endl;
        cout << "-----------------------------------------------------------------------" << endl;

        internoAdress = address.read();
        sc_uint<16> localAddres = 0;

        if (enable.read() == true)
        {

            if (memWrite.read() == true)
            {
                localAddres = internoAdress;
                readData.write(memory[localAddres]);
            }
            else
            {
                localAddres = internoAdress;
                memory[localAddres] = write_data.read();
            }
        }
        //cout << "Data Memory data" << endl;
        //for (int i = 0; i < MEMORY_SIZE; ++i)
        //{
       //     cout << "memory[" << i << "]: " << memory[i] << endl;
       // }
    }
    SC_CTOR(DataMemory)
    {
        for (int i = 0; i < MEMORY_SIZE; ++i)
        {
            memory[i] = 0;
        }
        SC_METHOD(memoryOperation);
        sensitive << clk.value_changed();
    }
};
