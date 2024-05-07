#include <systemc.h>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <unordered_map>
#include <bitset>
using namespace std;
SC_MODULE(InstructionMemory)
{
    sc_in<bool> clk;
    sc_in<bool> enable;
    sc_in<bool> write;
    sc_in<sc_uint<16>> address;
    sc_out<sc_uint<32>> instruction;

    sc_uint<32> internInstruction;
    sc_uint<32> memory[1024];


        SC_CTOR(InstructionMemory)
    {
        convertAsmInInstructions();
        SC_THREAD(fetchInstruction);
        sensitive << clk.pos();
    }
    void fetchInstruction()
    {
        while (true)
        {
            wait();
            if (enable.read())
            {
                if (write.read())
                {
                    memory[address.read()] = instruction.read();
                }
                instruction.write(memory[address.read()]);
            }
            if(memory[address.read()] == 0b0){
                sc_stop();
            }
        }
    }

public:
    enum OpC
    {
        zero_op = 0b0000,
        and_op = 0b0001,
        or_op = 0b0010,
        xor_op = 0b0011,
        not_op = 0b0100,
        slt_op = 0b0101,
        cmp_op = 0b0101,
        add_op = 0b0110,
        addi_op = 0b0111,
        sub_op = 0b1000,
        lw_op = 0b1001,
        sw_op = 0b1010,
        j_op = 0b1011,
        beq_op = 0b1100,
        bne_op = 0b1101
    };
    map<string, sc_uint<16>> jumpLocations = {};

    void convertAsmInInstructions()
    {
        jumpLocations = {};
        if (sc_argc() < 2)
        {
            cerr << "Uso: ./my_program <nome_do_arquivo>" << endl;
            return;
        }

        const char *filename = sc_argv()[1];
        vector<string> documentLines = readDocument(filename);
        vector<sc_uint<32>> dataoutput;

        cout << "Linhas de código '" << filename << "':" << endl;

        for (const auto &line : documentLines)
        {
            cout << line << endl;
            sc_uint<32> intValue = convertInstructionTobin(line);
            dataoutput.push_back(intValue);
        }

        cout << "conversão de linha de codigo resultam nas seguintes instrucoes:" << endl;
        for (int i = 0; i < int(dataoutput.size()); i++)
        {
            memory[i] = dataoutput[i];
            cout << "linha de codigo " << i << " virou instrução: " << bitset<32>(dataoutput[i]) << endl;
        }
    }
    vector<string> readDocument(const std::string &filename)
    {
        vector<string> lines;
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            sc_uint<16> ct = 0b0000000000000000;
            while (getline(file, line))
            {
                if (line.size() >= 1)
                {
                    ct = ct + 0b0000000000000001;
                    if (line.find(":"))
                    {
                        line.substr(0, line.size() - 1);
                        jumpLocations.insert({line, ct});
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

    sc_uint<32> convertInstructionTobin(string line)
    {
        sc_uint<32> binaryValue = 0;
        map<string, int> opcodeValues = {
            {"and", 0b0001}, {"or", 0b0010}, {"xor", 0b0011}, {"not", 0b0100}, {"slt", 0b0101}, {"cmp", 0b0101}, {"add", 0b0110}, {"addi", 0b0111}, {"sub", 0b1000}, {"lw", 0b1001}, {"sw", 0b1010}, {"j", 0b1011}, {"beq", 0b1100}, {"bne", 0b1101}

        };
        line.erase(std::remove(line.begin(), line.end(), ','), line.end());
        istringstream ss(line);
        string opcode, opd, op1, op2;
        ss >> opcode >> opd >> op1 >> op2;
        sc_uint<4> opcodeValue = zero_op;
        if (opcodeValues.find(opcode) != opcodeValues.end())
        {
            opcodeValue = opcodeValues[opcode];
        }
        else
        {
            cerr << "opcode não localizado" << endl;
        }
        cout << "o valor do ocode é: " << opcodeValue << endl;
        binaryValue.range(31, 28) = opcodeValue;
        if ((opcodeValue == lw_op) | (opcodeValue == sw_op))
        {
            binaryValue.range(27, 22) = registradorToBinary(opcodeValue, opd, 1); // Registrador destino
            binaryValue.range(21, 0) = registradorToBinary(opcodeValue, op1, 2);  // registrador + offset
        }
        else if (opcodeValue == j_op)
        {
            binaryValue.range(27, 0) = registradorToBinary(opcodeValue, opd, 1); // Registrador destino
        }
        else
        {
            binaryValue.range(27, 22) = registradorToBinary(opcodeValue, opd, 1); // Registrador destino
            binaryValue.range(21, 16) = registradorToBinary(opcodeValue, op1, 2); // Registrador fonte 1
            binaryValue.range(15, 0) = registradorToBinary(opcodeValue, op2, 3);  // Registrador fonte 2 ou imediato
        }

        return binaryValue;
    }

    sc_uint<32> registradorToBinary(sc_uint<4> opcd, string reg, int tp)
    {
        std::unordered_map<std::string, sc_uint<6>> registradores = {
            {"$zero", 0b000000}, {"$at", 0b000001}, {"$v0", 0b000010}, {"$v1", 0b000011}, {"$a0", 0b000100}, {"$a1", 0b000101}, {"$a2", 0b000110}, {"$a3", 0b000111}, {"$t0", 0b001000}, {"$t1", 0b001001}, {"$t2", 0b001010}, {"$t3", 0b001011}, {"$t4", 0b001100}, {"$t5", 0b001101}, {"$t6", 0b001110}, {"$t7", 0b001111}, {"$s0", 0b010000}, {"$s1", 0b010001}, {"$s3", 0b010011}, {"$s4", 0b010100}, {"$s5", 0b010101}, {"$s6", 0b010110}, {"$s7", 0b010111}, {"$t8", 0b011000}, {"$t9", 0b011001}, {"$gp", 0b011100}, {"$sp", 0b11101}, {"$fp", 0b011110}, {"$ra", 0b011111}};
        if (reg == "$zero")
        {
            if (tp == 2)
            {
                return 0b000000;
            }
            else if (tp == 3)
            {
                return 0b0000000000000000;
            }
        }
        else if ((opcd == j_op))
        {
            cout << "instrução jump" << endl;
            sc_uint<16> jumpAddress = jumpLocations[reg];
            cout << "o salto para " << reg << " leva ao endereco: " << jumpAddress << endl;
            return jumpAddress;
        }
        else if (opcd == not_op)
        {
            cout << "instrução not" << endl;
            if ((tp == 1) | (tp == 2))
            {
                sc_uint<6> regIntern = 0b000000000;
                if (registradores.find(reg) != registradores.end())
                {
                    regIntern = registradores[reg];
                    return regIntern;
                    cout << reg << endl;
                }
                else
                {
                    cerr << "registrador não localizado" << endl;
                }
            }
            else
            {
                return 0b0000000000000000;
            }
        }
        else if (((opcd == beq_op) | (opcd == bne_op)) & (tp == 3))
        {
            cout << "instrução beq e bne" << endl;
            if (jumpLocations.find(reg) != jumpLocations.end())
            {
                sc_uint<16> regIntern = jumpLocations[reg];
            }
            else
            {
                cerr << "AVISO: MARCAÇÃO USADA NÃO DEFINIDA NO Sistema";
                // sc_stop(); encerra a execução
            }
        }
        else if ((opcd == addi_op) & (tp == 3))
        {
            cout << "instrução addi" << endl;
            sc_uint<6> regIntern = stoi(reg);
            return regIntern;
        }
        else if ((opcd == lw_op) | (opcd == sw_op))
        {
            sc_uint<6> registerIntern = 0b000000;
            sc_uint<16> offset;
            if (tp == 1)
            {
                sc_uint<6> regIntern = 0b000000000;
                if (registradores.find(reg) != registradores.end())
                {
                    regIntern = registradores[reg];
                    return regIntern;
                }
                else
                {
                    cerr << "registrador " << reg << " não localizado" << endl;
                }
            }
            else if (tp == 2)
            {
                size_t pos1 = reg.find('(');
                size_t pos2 = reg.find(')');
                if (pos1 != string::npos && pos2 != string::npos && pos2 > pos1)
                {
                    string strOffset = reg.substr(0, pos1);
                    offset = std::stoi(strOffset);
                    string registradorBase = reg.substr(pos1 + 1, pos2 - pos1 -1);
                    registerIntern = 0b000000;
                    if (registradores.find(registradorBase) != registradores.end())
                    {
                        registerIntern = registradores[registradorBase];
                        
                    }
                    else
                    {
                        cerr << "registrador não localizado" << endl;
                    }
                }
                else
                {
                    cerr << "formato de dado de lw/sw errado" << endl;
                }
                sc_uint<22> lwresult = 0;
                cout << endl
                     << "no lw/sw: " << endl
                     << " registrador destino/origem: " << registerIntern << " em biset: " << bitset<6>(registerIntern) << endl;
                cout << "o offset é : " << offset << " em bitset fica: " << bitset<16>(offset) << endl;
                lwresult.range(21, 16) = registerIntern;
                lwresult.range(15, 0) = offset;
                return lwresult;
            }
        }
        else
        {
            if ((tp == 1) | (tp == 2))
            {
                sc_uint<6> regIntern = 0b000000000;
                if (registradores.find(reg) != registradores.end())
                {
                    regIntern = registradores[reg];
                    return regIntern;
                    cout << reg << endl;
                }
                else
                {
                    cerr << "registrador não localizado" << endl;
                }
            }
            else
            {
                sc_uint<16> regIntern = 0b0000000000000000000;
                if (registradores.find(reg) != registradores.end())
                {
                    regIntern = registradores[reg];
                    return regIntern;
                    cout << reg << endl;
                }
                else
                {
                    cerr << "registrador não localizado" << endl;
                }
            }
        }
        return 0;
    }


};
