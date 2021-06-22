`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/26/2021 06:56:57 PM
// Design Name: 
// Module Name: detectare
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


module detectare(clk, reset, b1, b2, b3, eb1, eb2, eb);
input clk, reset, b1, b2, b3;
output reg eb1, eb2, eb;
reg[2:0] state, nextstate;
localparam A = 3'b000, B = 3'b001, C = 3'b010, D = 3'b011,
           E = 3'b100, F = 3'b101, G = 3'b110;

always @(state, b1, b2, b3)
    case(state)
        A:  begin 
           if(b1) begin
                eb1 = 0;
                eb2 = 0;
                eb = 0;
                nextstate = B;
           end
           if(b2) begin
                eb1 = 1;
                eb2 = 0;
                eb = 1;
                nextstate = G;
           end
           if(b3) begin
                eb1 = 0;
                eb2 = 1;
                eb = 1;
                nextstate = F;
           end
        end
        B:  begin 
        if(b1) begin
                eb1 = 0;
                eb2 = 0;
                eb = 0;
                nextstate = C;
           end
           if(b2) begin
                eb1 = 1;
                eb2 = 0;
                eb = 1;
                nextstate = F;
            end
            if(b3) begin
                eb1 = 0;
                eb2 = 1;
                eb = 1;
                nextstate = E;
            end
        end
        C:  begin 
        if(b1) begin
                eb1 = 0;
                eb2 = 0;
                eb = 1;
                nextstate = A;
           end
           if(b2) begin
                eb1 = 1;
                eb2 = 0;
                eb = 1;
                nextstate = E;
            end
            if(b3) begin
                eb1 = 0;
                eb2 = 1;
                eb = 1;
                nextstate = D;
            end
        end
        D:   begin
                eb1 = 1;
                eb2 = 0;
                eb = 0;
                nextstate = E;
            end
        E:   begin
                eb1 = 1;
                eb2 = 0;
                eb = 0;
                nextstate = F;
            end
        F:   begin
                eb1 = 1;
                eb2 = 0;
                eb = 0;
                nextstate = G;
            end
        G:   begin
                eb1 = 1;
                eb2 = 0;
                eb = 0;
                nextstate = A;
            end
        default: nextstate = A;
    endcase
    
always @(posedge reset, posedge clk)
    if(reset) 
        state <= A;
    else
        state <= nextstate;
endmodule
