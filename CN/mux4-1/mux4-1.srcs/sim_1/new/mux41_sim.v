`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/16/2021 08:48:44 AM
// Design Name: 
// Module Name: mux41_sim
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


module mux41_sim();
reg[3:0] a, b, c, d;
reg s1, s2;
reg [3:0] y;

mux41 sim(a, b, c, d, s1, s2, y);

initial begin
a = 'b0000; b = 'b1001; c = 'b1010; d = 'b1111;
s1 = 0; s2 = 0;
#40 s1 = 1; s2 = 0;
#40 s1 = 0; s2 = 1;
#40 s1 = 1; s2 = 1;
$finish;
$stop;
end
endmodule
