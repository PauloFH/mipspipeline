#include <systemc.h>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
SC_MODULE(InstructionMemory)
{
    sc_in<bool> clk;
    sc_in<bool> enable;
    sc_in<bool> write;
    sc_in<int> address;
    sc_out<sc_uint<40>> instruction;
    int internInstruction;
    sc_uint<40> memory[1024];
   
    void fetchInstruction()
    {
        while (true)
        {
            wait();
            if (enable.read())
            {
                instruction.write(memory[address.read()]);
            }
        }
    }

public:
    map<string, sc_uint<9>> jumpLocations = {};
    void convertAsmInInstructions()
    {
        if (sc_argc() < 2)
        {
            cerr << "Uso: ./my_program <nome_do_arquivo>" << endl;
            return;
        }

        const char *filename = sc_argv()[1];
        vector<string> documentLines = readDocument(filename);
        vector<sc_uint<40>> dataoutput;
 
       cout << "Linhas de código '" << filename << "':" <<endl;

        for (const auto &line : documentLines)
        {
            cout << line << endl;
            sc_uint<40> intValue = convertInstructionTobin(line);
            dataoutput.push_back(intValue);
        }

        cout << "conversão de linha de codigo resultam nas seguintes instrucoes:" << endl;
        for (int i = 0; i < dataoutput.size(); i++){   
            memory[i] = dataoutput[i];
            cout << "linha de codigo "<< i <<" virou instrução: "<< dataoutput[i] << endl;
        }
    }
  vector<string> readDocument(const std::string &filename)
{
    vector<string> lines;
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        sc_uint<9> ct = 0b000000000;
        while (getline(file, line))
        {   if(line.size()>= 1){
            ct = ct + 0b000000001;
                if(line.find(":")){
                line.substr(0, line.size() -1);
                    jumpLocations.insert({line,ct});
            }
            lines.push_back(line); // Adiciona a linha lida ao vetor de linhas
            }
        }
        file.close();
    }
    else
    {
        cerr << "Erro ao abrir o arquivo '" << filename << "'" << endl;
    }
    return lines;
}




     sc_uint<40> convertInstructionTobin(string line){
    sc_uint<40> binaryValue = 0;
     map<string, int> opcodeValues = {
        {"and", 0b0001}, {"or", 0b0010}, {"xor", 0b0011}, {"not", 0b0100}, {"slt", 0b0101},
        {"add", 0b0110}, {"addi", 0b0111}, {"sub", 0b1000}, {"lw", 0b1001},
        {"sw", 0b1010}, {"j", 0b1011}, {"jn", 0b1100},{"beq", 0b1101}, {"bne", 0b1110}
        
    };
    istringstream ss(line);
    string opcode, opd, op1, op2;
    ss >> opcode >> opd >> op1 >> op2;
     sc_uint<6> opcodeValue = 0b0000;
    if (opcodeValues.find(opcode) != opcodeValues.end()) {
        opcodeValue = opcodeValues[opcode];
    }else{
        cerr  << "opcode não localizado" << endl;
    }
    cout <<"o valor do ocode é: " << opcodeValue << endl;
    cout <<"registrador destino da instrução: "<< opd << endl;
    cout <<"registrador fonte da instrução: "<< op1 << endl;
    cout <<"registrador fonte 2/imediate/offset da instrução: "<< op2 << endl;
    binaryValue.range(31, 28) = opcodeValue;
    binaryValue.range(27, 22) =registradorToBinary(opcodeValue, opd,1); // Registrador destino
    binaryValue.range(21, 16) = registradorToBinary(opcodeValue, op1,2); // Registrador fonte 1
    binaryValue.range(15, 0) = registradorToBinary(opcodeValue, op2,3); // Registrador fonte 2 ou imediato

    return binaryValue;
}

sc_uint<9> registradorToBinary(sc_uint<4> opcd, string reg, int tp){
    if(reg == "$zero"){

    }  
    if(opcd == 0b1011 & tp == 1){
        if(tp == 1){
            sc_uint<9> jumpAddress = jumpLocations[reg];
            cout << "o salto para " <<reg <<" leva ao endereco: " << jumpAddress << endl;
        return jumpAddress;
        }else if(tp == 3){
            return 0b00000000;
        }else {
            return 0b0000000000000000;
        }
    }
    if(opcd == 0b0100){
            if(tp == 1 | tp == 2){
                sc_uint<9> regIntern = 0b000000000;
                reg.copy(,,);
            }else{
                    return 0b0000000000000000;
            }
    }

    return 0;
}

SC_CTOR(InstructionMemory)
{   convertAsmInInstructions();
    SC_METHOD(fetchInstruction);
    sensitive << clk.pos();
}

};
