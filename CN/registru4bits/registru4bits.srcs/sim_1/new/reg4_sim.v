`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/16/2021 09:38:20 AM
// Design Name: 
// Module Name: reg4_sim
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


module reg4_sim( );
reg [3:0] rin;
reg clk, load, clear;
wire [3:0] rout;
registru4 r1(rin, clk, load, clear, rout);

initial begin
clk = 0;
load = 0;
clear = 0;
rin = 4'b 1010;
#50 load = 1;
#50 clear = 1;
#50 clear = 0;
#50
$finish;
end
always
#25 clk = ~clk;


endmodule
