// #include "Vrom.h"
// #include "Vcounter.h"
#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);  // Remember args
    Vsinegen* top = new Vsinegen;  // Create instance

    // Tracing
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99); // Annotating signals to trace
    tfp->open ("sinegen.vcd"); // Open the dump file

    if (vbdOpen()!=1) return -1;
    vbdHeader("Lab 1: Counter");

    top->clk = 1; // initial clock
    top->rst = 0; // reset
    top->en = 1; // disable counter
    top->incr = 1; // increment by 1

    // run simulation for 1,000,000 cycles
    for (i = 0; i < 1000000; i++) {

        for (clk = 0; clk < 2; clk++) {
            tfp -> dump(2*i+clk);
            top -> clk = !top ->clk; // evaluate clock
            top ->eval();
        }

        vbdPlot(int(top->dout), 0, 255);
        vbdCycle(i+1);

        //top->rst = (i < 2) | (i == 15);
        top->en = vbdFlag();

        top->incr = vbdValue();

        // either simulation finished, or 'q' is pressed
        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
        exit(0);                // ... exit if finish OR 'q' pressed
    }

    vbdClose();
    tfp->close();
    exit(0);
    
}