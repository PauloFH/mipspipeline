#include <systemc.h>

SC_MODULE(Controller)
{

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

    sc_in<bool> clk;
    sc_in<sc_uint<32>> instruction;
    sc_in<bool> zero;
    sc_in<bool> reset;

    // Sinais do PC
    sc_out<bool> pcReset;
    sc_out<bool> pcEnable;
    sc_out<bool> PcLoad;
    sc_out<sc_uint<16>> pcjump;

    // Sinais dos Registradores
    sc_out<bool> regEnable;
    sc_out<bool> regWrite;

    // Sinais da Instruction Memory
    sc_out<bool> imEnable;
    sc_out<bool> imwrite;

    // Sinais da Data Memory
    sc_out<bool> dmEnable;
    sc_out<bool> dmWrite;
    sc_out<bool> memToReg;

    // Sinais BufferIFID
    sc_in<sc_uint<32>> Controller_instruction;
    sc_out<bool> enable_BufferIFID;
    sc_out<bool> write_BufferIFID;
    sc_out<bool> reset_BufferIFID;

    // Sinais  BufferIDEX
    sc_out<bool> enable_BufferIDEX;
    sc_out<bool> write_BufferIDEX;
    sc_out<bool> reset_BufferIDEX;
    sc_out<bool> branch;
    // Sinais BufferEXMEM

    sc_out<bool> enable_BufferEXMEM;
    sc_out<bool> write_BufferEXMEM;
    sc_out<bool> reset_BufferEXMEM;
    // Sinais BufferMEMWB
    sc_out<bool> enable_BufferMEMWB;
    sc_out<bool> write_BufferMEMWB;
    sc_out<bool> reset_BufferMEMWB;
    // Sinais do ALU
    sc_out<sc_uint<4>> aluOp;
    sc_out<bool> aluReset;
    sc_out<sc_uint<22>> addressOut;
    // locais
    sc_uint<32> label;
    sc_uint<4> opcode;
    sc_uint<6> opd;
    sc_uint<6> op1;
    sc_uint<16> op2;
    
    sc_out<int> stateOut;
    int state = 0;
    bool restart;


    
    void IF()
    {
        imEnable.write(true);
        pcEnable.write(true);
        enable_BufferIFID.write(true);
        enable_BufferIDEX.write(true);
        enable_BufferEXMEM.write(true);
        enable_BufferMEMWB.write(true);
    }
    void ID()
    {
        imEnable.write(false);
        pcEnable.write(false);
        regEnable.write(true);

        opcode = instruction.read().range(31, 28);
        label = instruction.read().range(27, 0);
        opd = instruction.read().range(27, 22);
        op1 = instruction.read().range(21, 16);
        op2 = instruction.read().range(15, 0);
    }
    void RE()
    {
        regEnable.write(true);
        regWrite.write(true);
        reset_BufferEXMEM.write(true);
        reset_BufferIDEX.write(true);
        reset_BufferMEMWB.write(true);
    }
    void updateState()
    {
        stateOut.write(state);

        if (opcode == beq_op)
        {
            branch.write(true);
        }
        else if(opcode == bne_op)
        {
            branch.write(false);
        }
        if(opcode == lw_op || opcode == sw_op)
        {
              addressOut.write(instruction.read().range(21, 0));
        }
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
        ID();
        state = 4;
        break;

        case 4:
            if (opcode == 9)
            { // Lw
                regEnable.write(true);
                regWrite.write(true);
                dmEnable.write(true);
                dmWrite.write(true);
                 aluOp.write(opcode);
                state = 5;
            }
            else if (opcode == 10)
            { // Sw
                dmEnable.write(true);
                dmWrite.write(false);
                regWrite.write(true);
                aluOp.write(opcode);
                state = 6;
            }
            else if (opcode == 11)
            { // J
                aluOp.write(opcode);
                pcEnable.write(false);
                pcjump.write(label);
                restart = true;
                state = 7;
            }
            else if (opcode == 12)
            { // bne
                aluOp.write(opcode);
                if (!zero.read())
                {
                    pcEnable.write(false);
                    pcjump.write(label);
                    aluReset.write(true);
                    restart = true;
                }
                state = 7;
            }
            else if (opcode == 13)
            { // beq
                aluOp.write(opcode);
                if (!zero.read())
                {
                    pcEnable.write(false);
                    pcjump.write(label);
                    aluReset.write(true);
                    restart = true;
                }
                state = 7;
            }
            else if (opcode >= 0 && opcode < 9)
            { // ALU
                aluOp.write(opcode);
                regWrite.write(false);
                regEnable.write(true);
                state = 9;
            }

            break;

        case 5: // LW STATE
            regEnable.write(true);
            regWrite.write(true);
            state = 9;
            break;

        case 6: // SW STATE
            dmEnable.write(true);
            dmWrite.write(true);
            state = 9;
            break;

        case 7:
            state = 2;
            break;

        case 8:
            regEnable.write(true);
            regWrite.write(true);
            state = 9;
            break;

        case 9:
            regEnable.write(false);
            regWrite.write(false);
            break;
        default:
            break;
        }
    }

    SC_CTOR(Controller)
    {
        SC_METHOD(updateState);
        sensitive << clk.pos();
    }
};
