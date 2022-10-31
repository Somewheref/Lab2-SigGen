module counter #(
    parameter WIDTH = 8
)(
    input logic clk,
    input logic rst,
    output logic [WIDTH-1:0] count
);

always_ff @(posedge clk) 
if (rst) begin
    count <= {WIDTH{1'b0}}; //E{A} = A with #E occurances
    //$display("Reset");
end
else begin
    count <= count + {{WIDTH-1{1'b0}}, 1'b1};
    // $display("count = %d", count);
end

endmodule
