`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/22/2021 11:05:59 PM
// Design Name: 
// Module Name: bistabilD
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


module bistabilD(D, clk, reset, Q);
input [3:0] D;
input clk;
input reset;
output reg [3:0] Q;
always @(posedge clk or posedge reset) 
begin
 if(reset)
  Q <= 0; 
 else 
  Q <= D; 
end 
endmodule
