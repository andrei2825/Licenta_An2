module summator_sim;
reg [15:0] a,b;
reg cin;
wire [15:0] sum;
wire cout;
 
  summator uut(.a(a), .b(b),.cin(cin),.sum(sum),.cout(cout));
 
initial begin
  a=0; b=0; cin=0;
  #30 a=5; b=8; cin=1;
  #30 a=8; b=8; cin=1;
  #30 a=3; b=7; cin=1;
  #30 a=10; b=10; cin=1;
end
 
initial
  $monitor( "A=%d, B=%d, Cin= %d, Sum=%d, Cout=%d", a,b,cin,sum,cout);
endmodule