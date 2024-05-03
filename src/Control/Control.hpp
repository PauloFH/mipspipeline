#include <systemc.h>

SC_MODULE(Control) {
    sc_in<bool> clk;
    sc_in<sc_uint<32>> instr;
     sc_uint<4> opcode;
     sc_uint<4> op1;
     sc_uint<4> op2;
     sc_uint<4> opd;
    sc_in <bool> zero;
    sc_in <bool> negative;
    sc_in <bool> reset;

    sc_out<bool> Branch;
    sc_out<bool> memRead;
    sc_out<bool> memToReg;
    sc_out<bool> memWrite;
    sc_out<bool> aluSrc;

    sc_out<bool> pcReset;
    sc_out<bool> pcEnable;
    sc_out<bool> pcLoad;
    sc_out<int>  pcjump;
    
    sc_out<bool> imEnable;
    sc_out<bool> ri;
    sc_out<bool> imWrite;
    
    sc_out <bool> dmEnable;
    sc_out<bool> dmWrite;

    sc_out<bool> regWrite;
    sc_out<bool> regEnable;
    sc_out<bool> regDst;

    sc_out<bool> aluReset;
    sc_out<int>  aluOp;

    sc_out<bool> RBW;
    sc_out<bool> DM;
    int state = 0;
    bool restart;
    void ID(){
        imEnable.write(true);
        imWrite.write(false);
        pcEnable.write(true);
    }
    void IR(){
         imEnable.write(false);
         regWrite.write(true);
         regEnable.write(true);
         pcEnable.write(false);
    }
    void RE(){
             ri.write(false);
             regEnable.write(true);
             regWrite.write(true);
    }
    void updateState() {
        switch (state)
        {
        case 0: 
                ID();
                state = 1;
            break;
        case 1:
                IR();
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
            ID();
            break;
        case 4: 
            IR();
            if(opcode == 7){// LD
                regEnable.write(true);
                regWrite.write(true);
                dmEnable.write(true);
                dmWrite.write(true);
                RBW.write(true);
                DM.write(true);
                state = 6;
                
            }else if(opcode== 8){// ST
                dmEnable.write(true);
                dmWrite.write(false);
                RBW.write(true);
                state = 7;
            }else if(opcode == 9){//J
                pcEnable.write(false);
                pcLoad.write(true);
                pcjump.write(opd);
                restart = true;
                state = 8;
            }else if(opcode == 10){//JN
                if(negative.read()){
                    pcEnable.write(false);
                    pcLoad.write(true);
                    pcjump.write(opd);
                    aluReset.write(true);
                    restart = true;
                }
                state = 8;
            }else if(opcode == 11){//JZ
                if(zero.read()){
                    pcEnable.write(false);
                    pcLoad.write(true);
                    pcjump.write(opd);
                    aluReset.write(true);
                    restart = true;
                }
                state = 8;
            }else if(opcode > 0  && opcode< 7){//ALU
                RBW.write(false);
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
                 ri.write(false);
                state = 10;
                break;
            case 8:
                pcLoad.write(false);
                state = 2;
                break;
            case 9:
                regEnable.write(true);
                regWrite.write(true);
                ri.write(false);
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

    SC_CTOR(Control) {
        SC_METHOD(updateState);
        sensitive << clk.pos() << reset;
    }
};
