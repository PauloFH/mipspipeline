#include <systemc.h>
#include "DataMemory.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> memWrite, enable;
    sc_signal<sc_int<32>> write_data, address, readData;

    DataMemory dataMemory("dataMemory");
    dataMemory.clk(clk);
    dataMemory.memWrite(memWrite);
    dataMemory.enable(enable);
    dataMemory.write_data(write_data);
    dataMemory.address(address);
    dataMemory.readData(readData);

    memWrite = true;
    enable = true;
    write_data = 10;
    address = 100;

    sc_start(1, SC_NS);

    assert(readData.read() == 0); // Since memory is not initialized, readData should be 0

    memWrite = false;
    enable = true;
    write_data = 20;
    address = 100;

    sc_start(1, SC_NS);

    assert(readData.read() == 20); // After writing to memory, readData should be equal to write_data

    memWrite = true;
    enable = true;
    write_data = 30;
    address = 100;

    sc_start(1, SC_NS);

    assert(readData.read() == 30); // After writing to memory again, readData should be updated

    cout << "Test passed!" << endl;

    return 0;
}