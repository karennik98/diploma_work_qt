module name(out, data, clk);
input A;
input B;
input C;
input E;
input D;
output Q;

not G1 ( X1, B);
nand G5 ( X4, C, X2);
nand G2 (X3, C, X1);
or G4 ( X2, D, E);
or G3 ( Q, A, X3, X4);

endmodule
