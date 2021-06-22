`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2021 07:27:50 PM
// Design Name: 
// Module Name: ffd
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


module ffd(a, b, c, d, e, clr, clk, ax, bx, cx, dx, ex);
    input  [15:0]  a, b, c, d, e, clr, clk;
    output [15:0]  ax, bx, cx, dx, ex;
    reg [15:0] ax, bx, cx, dx, ex;
always@(posedge clk)
    begin
        if(clr)
        begin
            ax <= 0;
            bx <= 0;
            cx <= 0;
            dx <= 0;
            ex <= 0;
        end
        else
        begin
            ax <= a;
            bx <= b;
            cx <= c;
            dx <= d;
            ex <= e;
        end
    end
endmodule
