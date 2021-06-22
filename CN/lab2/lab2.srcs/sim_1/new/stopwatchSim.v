`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/30/2021 09:54:18 AM
// Design Name: 
// Module Name: stopwatchSim
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


module stopwatchSim();

reg clk, reset, pause;
wire [3:0] BCD00, BCD01, BCD10, BCD11;

stopwatch s(clk, reset, pause, BCD00, BCD01, BCD10, BCD11);
initial begin
    clk = 0;
    reset = 1;
    pause = 0;
    #50
    #50 reset = 0;
end
always
    #10 clk = ~clk;
endmodule
