#include <systemc.h>

SC_MODULE(Controller) {

    enum  OpC {zero_op = 0b0000,and_op = 0b0001,or_op = 0b0010,xor_op = 0b0011,not_op = 0b0100,slt_op = 0b0101,cmp_op = 0b0101,add_op = 0b0110,
    addi_op = 0b0111,sub_op = 0b1000,lw_op = 0b1001,sw_op = 0b1010,j_op = 0b1011,beq_op = 0b1100,bne_op = 0b1101};

    sc_in<bool> clk;
    //
    sc_in<sc_uint<32>> instruction;
    sc_in <bool> zero;
    sc_in <bool> notequal;
    sc_in <bool> reset;

    //Sinais do PC
    sc_out<bool> pcReset;
    sc_out<bool> pcEnable;
    sc_out<bool> pcLoad;
    sc_out<sc_uint<16>> pcjump;

    //Sinais dos Registradores
    sc_out<bool> regEnable;
    sc_out<bool> regWrite;

    //Sinais da Instruction Memory
    sc_out<bool> imEnable;
    sc_out<bool> imwrite;

    // Sinais da Data Memory
    sc_out <bool> dmEnable;
    sc_out <bool> dmWrite;

    sc_out<bool> memToReg;

    //Sinais  BufferIDEX
    sc_out<bool> enable_BufferIDEX;
    sc_out<bool> write_Buffer_IDEX;
    //Sinais BufferEXMEM

    sc_out<bool> enable_BufferEXMEM;
    sc_out<bool> write_BufferEXMEM;
    
    //Sinais BufferMEMWB
    sc_out<bool> enable_BufferMEMWB;
    sc_out<bool> write_BufferMEMWB;

    //Sinais do ALU
    sc_in<sc_uint<4>>aluOp;
    sc_out<bool> aluReset;


    //locais
    sc_uint<32> label;
    sc_uint<4> opcode;
    sc_uint<6> opd;
    sc_uint<6> op1;
    sc_uint<16> op2;

    int state = 0;
    bool restart;

    void IF(){
        imEnable.write(true);
        pcEnable.write(true);
    }
    void ID(){
         imEnable.write(false);
         pcEnable.write(false);
    }
    void RE(){
             regEnable.write(true);
             regWrite.write(true);
    }
    void updateState() {

        opcode = instruction.read().range(31,28);
        label = instruction.read().range(27,0);
        opd = instruction.read().range(27,22);
        op1 = instruction.read().range(21,16);
        op2 = instruction.read().range(15,0);
       
        

        switch (state)
        {
        case 0: 
                IF();
                state = 1;
            break;
        case 1:
                ID();
                state = 2;
            break;
        case 2:
                if (!restart)
                {
                    RE();
                    state = 3;
                }
            break;
        case 3:
             regEnable.write(true);
             state = 4;
            IF();
            break;
        case 4: 
            ID();
            if(opcode == 7){// Lw
                regEnable.write(true);
                regWrite.write(true);
                dmEnable.write(true);
                dmWrite.write(true);
                regWrite.write(true);
                state = 6;
                
            }else if(opcode == 8){// Sw
                dmEnable.write(true);
                dmWrite.write(false);
                regWrite.write(true);
                state = 7;
            }else if(opcode == 9){//J
                pcEnable.write(false);
                pcLoad.write(true);
                pcjump.write(label);
                restart = true;
                state = 8;
            }else if(opcode == 10){//bne
                if(notequal.read()){
                    pcEnable.write(false);
                    pcLoad.write(true);
                    pcjump.write(label);
                    aluReset.write(true);
                    restart = true;
                }
                state = 8;
            }else if(opcode == 11){//beq
                if(zero.read()){
                    pcEnable.write(false);
                    pcLoad.write(true);
                    pcjump.write(label);
                    aluReset.write(true);
                    restart = true;
                }
                state = 8;
            }else if(opcode > 0  && opcode < 7){//ALU
                regWrite.write(false);
                regEnable.write(true);
                regWrite.write(false);
                state = 9;
            }

            break;
            case 6: //LD STATE
                regEnable.write(true);
                regWrite.write(true);
                state = 10;
            break;
            case 7: //ST STATE
                dmEnable.write(true);
                dmWrite.write(true);
                state = 10;
                break;
            case 8:
                pcLoad.write(false);
                state = 2;
                break;
            case 9:
                regEnable.write(true);
                regWrite.write(true);
                state = 10;
                break;
            case 10:
                regEnable.write(false);
                regWrite.write(false);
                break;
        default:
            break;
        }
        
    }

    SC_CTOR(Controller) {
        SC_METHOD(updateState);
        sensitive << clk.pos();
    }
};
