`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2021 07:29:11 PM
// Design Name: 
// Module Name: top
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


module top(a, b, c, d, e, f, clk, clr);
    input [15:0] a, b, c, d, e;
    input clk, clr;
    output [15:0] f;
    wire [15:0] r, ax, bx, cx, dx, ex, fx, i1, i2, i3, ax2, bx2, cx2, dx2, ex2, fx2, f2, ax3, bx3, cx3, dx3, ex3, fx3, ax4, bx4, cx4, dx4, ex4, fx4;
    ffd         inst1(a, b, c, d, e, clr, clk, ax, bx, cx, dx, ex); 
    inmultire   inst2(ax, bx, i1);
    inmultire   inst3(dx, ex, i2);
    ffd         inst4(i1, bx, cx, i2, ex, clr, clk, ax2, bx2, cx2, dx2, ex2);
    adunare     inst5(ax2, cx2, i3);
    ffd         inst6(ax2, bx2, cx2, dx2, i3, clr, clk, ax3, bx3, cx3, dx3, ex3);
    scadere     inst7(ex3, dx3, fx3);
    ffd         inst8(ax3, bx3, cx3, dx3, fx3, clr, clk, ax4, bx4, cx4, dx4, f);
endmodule
