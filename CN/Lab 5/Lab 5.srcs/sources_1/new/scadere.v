`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2021 07:27:19 PM
// Design Name: 
// Module Name: scadere
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


module scadere(a, b, d);
    input [15:0] a, b;
    output [15:0] d;
assign d = a - b;
endmodule
