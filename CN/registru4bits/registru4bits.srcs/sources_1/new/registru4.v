`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/16/2021 09:31:56 AM
// Design Name: 
// Module Name: registru4
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


module registru4(rin, clk, load, clear, rout);
input [3:0] rin;
input clk, load, clear;
output reg [3:0] rout;
//reg [3:0] rout;

always @(posedge clk)
begin
    if(clear)
        rout <= 0;
    else if (load)
        rout <= rin;
end

endmodule
