`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/23/2021 09:18:42 AM
// Design Name: 
// Module Name: numaratorSim
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


module numaratorSim();
reg clk;
reg reset;
reg pauza;
wire [5:0] valoare_bin;
wire carry_out;
numarator num(clk, reset, pauza, valoare_bin, carry_out);
initial begin
clk = 0;
reset = 1;
pauza = 0;
#50 reset = 0;
//#50 pauza = 1;
//#50 pauza = 0;
end
always
#25 clk = ~clk;
endmodule
