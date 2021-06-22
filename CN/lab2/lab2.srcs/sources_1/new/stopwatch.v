`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/30/2021 09:47:57 AM
// Design Name: 
// Module Name: stopwatch
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


module stopwatch(clk, reset, pause, BCD00, BCD01, BCD10, BCD11);
input clk, reset, pause;
wire carry_out1, carry_out2;
wire [5:0] valoare_bin1, valoare_bin2;
output [3:0] BCD00, BCD01, BCD10, BCD11;
numarator num1(clk, reset, pause, valoare_bin1, carry_out1);
numarator num2(carry_out1, reset, pause, valoare_bin2, carry_out2);

bin2bcd bin1(valoare_bin1, BCD10, BCD11);
bin2bcd bin2(valoare_bin2, BCD00, BCD01);

endmodule
