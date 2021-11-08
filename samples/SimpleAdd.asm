// push constant 7
@7
D=A
@SP
A=M
M=D
// increment stack pointer
@SP
M=M+1
// push constant 8
@8
D=A
@SP
A=M
M=D
// increment stack pointer
@SP
M=M+1
// add 
// get top most element
@SP
A=M-1
// set to D
D=M
// reduce stack pointer
@SP
M=M-1
// get top most element
@SP
A=M-1
// add to D
D=D+M
// store D in the stack
@SP
A=M
M=D