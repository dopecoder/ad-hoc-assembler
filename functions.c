typedef struct  
{
	char opcode[10];
	char operand1[100];
	char operand2[100]; 
	char operand3[100];
	char operand4[100];

}expressionData;

/*enum mnemonics{
	MOV = 0b001101;
	HLT = 0b001010;
	NEG = 0b000000;
	AND = 0b000001;
	XOR = 0b000010;
	OR  = 0b000011;
  LSR = 0b000100;
	LSL = 0b000101;
	JMP = 0b001111;
	ADD = 0b010000;
	SUB = 0b010001;
};*/

struct mnemonicString
{
	char * MOV;
	char * HLT;
	char * NEG;
	char * AND;
	char * XOR;
	char * OR;
  char * LSR;
	char * LSL;
	char * JMP;
	char * ADD;
	char * SUB;

}mnemonics = {"001101", "001010", "000000", "000001", "000010", "000011", "000100", "000101", "001111", "010000", "010001"};

/*enum mnemonicString{
	MOV = "001101";
	HLT = "001010";
	NEG = "000000";
	AND = "000001";
	XOR = "000010";
	OR  = "000011";
  LSR = "000100";
	LSL = "000101";
	JMP = "001111";
	ADD = "010000";
	SUB = "010001";

};*/

struct registers 
{
	char * R1;	
	char * R2;
	char * R3;
	char * R4;
	char * R5;
	char * INTERMEDIATE;

}Registers = {"001", "010", "011", "100", "101", "000"};

/*enum registers{
	R1 = "001";	
	R2 = "010";
	R3 = "011";
	R4 = "100";
	R5 = "101";
	INTERMEDIATE = "000";
};*/

struct mode 
{
	char * operandMode;
	char * ptoperandMode;
	char * interMode;

}modes = {"00", "01", "10"};

/*enum mode{
	operandMode   = "00";
	ptoperandMode = "01";
	interMode     = "10";
};*/


cc
