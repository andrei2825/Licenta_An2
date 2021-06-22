`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2021 08:26:33 PM
// Design Name: 
// Module Name: sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sim;
reg [15:0] a, b, c, d, e;
reg clk, clr;
wire [15:0] res;

top simulare(a, b, c, d, e, res, clk, clr);
initial begin
 clk = 1;
    forever #10 clk = ~clk;
end
initial begin
//    #20 a = 0; b = 0; c = 0; d = 0; e = 0;
    #20 clr = 0;
    #20 a = 1; b = 2; c = 3; d = 4; e = 5;
    #20 a = 0; b = 3; c = 2; d = 5; e = 1;
    #20 a = 1; b = 5; c = 3; d = 9; e = 2;
    #20 a = 4; b = 2; c = 7; d = 1; e = 9;
    #20 a = 1; b = 3; c = 5; d = 7; e = 8;

end

endmodule
