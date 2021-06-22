`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/22/2021 11:11:33 PM
// Design Name: 
// Module Name: bistabilDSim
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


module bistabilDSim();
reg D;
reg clk;
reg reset;
wire Q;
bistabilD b(D, clk, reset, Q);
initial begin
  clk=0;
     forever #10 clk = ~clk;  
end 
initial begin 
 #50 reset=1;
 #50 D <= 0;
 #50 reset=0;
 #50 D <= 1;
 #50 reset=1;
 #50 D <= 0;
 #50 reset=0;
 #50 D <= 1;
end 
endmodule
