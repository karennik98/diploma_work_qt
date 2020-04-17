module orgate(out, a, b, c, d); 
input a, b, c, d; 
wire x, y; 
output out; 
or or1(.I0(x), .I1(a), .Z(b)); 
or or2(.I0(y), .I1(c), .Z(d)); 
or orfinal(.I0(out), .I1(x), .Z(y)); 
endmodule
