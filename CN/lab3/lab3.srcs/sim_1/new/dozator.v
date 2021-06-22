`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/26/2021 08:41:32 PM
// Design Name: 
// Module Name: dozator
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


module dozator();
reg clk, reset, b1, b2, b3;
wire eb1, eb2, eb;
detectare d(clk, reset, b1, b2, b3, eb1, eb2, eb);
initial begin
    clk = 0;
    reset = 1;
    #10 reset = 0;
    #10 b1 = 1; b2 = 0; b3 = 0;
    #100 b3 = 1;
    #100 b1 = 0; b2 = 1; b3 = 0;
    
end
always
    #10 clk = ~clk;
endmodule
