`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/16/2021 08:47:49 AM
// Design Name: 
// Module Name: mux4-1
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


module mux41(d0, d1, d2, d3, s1, s2, y);

input [3:0] d0, d1, d2, d3;
input s1, s2;
output [3:0]y;

assign y = s2 ? (s1 ? d3 :d2)
                : (s1?d1:d0);

endmodule
