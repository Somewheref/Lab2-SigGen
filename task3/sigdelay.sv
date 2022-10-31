module sigdelay #(
    parameter   A_WIDTH = 8,
                D_WIDTH = 8
)
(
    input logic clk,
    input logic rst,
    input logic wr,
    input logic rd,
    input logic [A_WIDTH-1:0] offset,
    //input logic [A_WIDTH-1:0] wr_addr,
    input logic [D_WIDTH-1:0] mic_signal,
    output logic [D_WIDTH-1:0] delayed_signal
);

logic [A_WIDTH-1:0] counter_addr;

counter addrCounter (
    .clk(clk),
    .rst(rst),
    .count(counter_addr)
);

ram2ports sineRom(
    .clk(clk),
    .wr_en(wr),
    .rd_en(rd),
    .wr_addr(counter_addr),
    .rd_addr(counter_addr - offset),
    .din(mic_signal),
    .dout(delayed_signal)
);

endmodule
