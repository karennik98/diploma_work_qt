module orgate(out, a, b, c, d); 
input a, b, c, d;
wire x, y; 
output out; 
or or1(x, a, b);
or or2(y, c, d);
or orfinal(out, x, y);
endmodule
