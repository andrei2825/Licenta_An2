`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/23/2021 09:08:23 AM
// Design Name: 
// Module Name: numarator
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


module numarator(clk, reset, pauza,  valoare_bin, carry_out);
input clk;
input reset;
input pauza;
output reg [5:0] valoare_bin;
output reg carry_out;
always @(posedge clk or posedge reset)
begin
    if(reset)
        begin
        valoare_bin <= 0;
        carry_out <= 0;
        end
    else
        begin
        if (~pauza)
            begin
            valoare_bin <= valoare_bin + 1;
            carry_out <= 0;
            if(valoare_bin >= 59)
                begin
                carry_out <= 1;
                valoare_bin <= 0;
                end
            end
        end
end
endmodule
