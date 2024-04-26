#include <systemc.h>
#include <iostream>
using namespace std;
SC_MODULE(InstructionMemory){
sc_in<char[9]> instruction;
void function(){
     cout << "Hello World!";
      cout << instruction;
}
SC_CTOR(InstructionMemory){
    function();
}
};
