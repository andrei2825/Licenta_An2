`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2021 07:26:56 PM
// Design Name: 
// Module Name: inmultire
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


module inmultire(a, b, p);
    input [15:0] a, b;
    output [15:0] p;
assign p = a * b;
endmodule
