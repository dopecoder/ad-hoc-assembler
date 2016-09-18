#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define MAXBUFLEN 100000

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

char binaryData[MAXBUFLEN];
char rawBinaryData[MAXBUFLEN];
char hexData[MAXBUFLEN];
char hexBuff[MAXBUFLEN];
char buffer[MAXBUFLEN];
char rawBuffer[MAXBUFLEN];

int line_num(const char * filename); /* To count the number of lines in a file */
void bufferProcessor(char * buffer, expressionData * dataStore, const int bufferSize,const int maxOperands); /* To sort the opcode and operand into a struct */
void binaryEquivalent( const expressionData * data, const struct mnemonicString mnemonics, const struct registers Registers, const struct mode modes, const int numOfLines,
 char * binaryData, const int * excludedNo);
int isEmpty( const char * string); /* To check whether the string is empty */
void formattedBinaryEquivalent( const expressionData * data, const struct mnemonicString mnemonics, const struct registers Registers, const struct mode modes, const int numOfLines,
 char * binaryData, const int * excludedNo);
void intermediateDataPrint( const char * intermediateAdd, char * binaryData);
void appendEOL( char * binaryData, const int nos);
void charPrinter( const char * data, const char * msg);
void binaryToHex( const char * buffer, char * hexData);

void main()
{
	int i = 0, j = 0;
	int excludeNos[10];
	char ch;
	int * ptrToNos = excludeNos;
	const char * fn = "assembler.txt";
	char * fileName;
	const int maxOperands = 4;
	char source[MAXBUFLEN + 1];
	expressionData data[100];
	int numOfLines=0;
	//puts("Enter the file name containing the assembly code : ");
    //scanf("%s",&fileName);
	FILE *fp = fopen("assembler.txt", "r+");
	if (fp != NULL) {
    size_t newLen = fread(source, sizeof(char), MAXBUFLEN, fp);
    if (newLen == 0) {
        fputs("Error reading file", stderr);
    } else {
        source[++newLen] = '\0';
    }

		fclose(fp);
		numOfLines = line_num(fn);
		printf("%d\n",numOfLines);
    for(i = newLen; i<MAXBUFLEN; i++)
    {
     source[i]='\0';
    }

		puts("File buffer being printed.");
    for(i = 0; i<MAXBUFLEN; i++)
    {
     printf("%c",source[i]);
    }

		bufferProcessor(source, data, MAXBUFLEN, maxOperands);
		for(i = 0; i<numOfLines; i++)
		{	if(isEmpty(data[i].opcode) && isEmpty(data[i].operand1) && isEmpty(data[i].operand2) && isEmpty(data[i].operand3) && isEmpty(data[i].operand4))
			{
				*ptrToNos=i;
				ptrToNos++;
				continue;
			}
			else
			{
				printf("The opcode is   : %s\n",data[i].opcode);
				printf("The operand1 is : %s\n",data[i].operand1);
				printf("The operand2 is : %s\n",data[i].operand2);
				printf("The operand3 is : %s\n",data[i].operand3);
				printf("The operand4 is : %s\n",data[i].operand4);
			}
		}
		/*
		printf("%c\n",data[0].operand1[0]);
		printf("%c\n",data[0].operand1[1]);
		printf("%c\n",data[0].operand1[2]);
		printf("%c\n",data[0].operand2[0]);
		printf("%c\n",data[0].operand2[1]);
		printf("%c\n",data[0].operand2[2]);
		if(strcmp(data[0].operand1, "R3")==0)
		{
			puts("Awesome!");
		}
		else
		{
			puts("okay!lets see.");
		}

		if(data[0].operand1[0] == 'R')
		{
			puts("Awesome!");
		}
		else{
			puts("okay!lets see.");
		}

		if(data[1].operand1[0] == 'R'||data[1].operand1[1] == 'R'){
			puts("Awesome! this is.");
		}
		else{
			puts("okay!lets see.");
		}

		if(data[1].operand2[0] == '#'||data[1].operand2[1] == '#'){
			puts("Awesome! this is.");
		}
		else{
			puts("okay!lets see.");
		}*/

		//struct mnemonicString mnemonics;
		//mnemonics = {"001101", "001010", "000000", "000001", "000010", "000011", "000100", "000101", "001111", "010000", "010001"};
		//struct registers Registers;
		//Registers = {"001", "010", "011", "100", "101", "000"};
		//struct mode modes;
		//modes = {"00", "01", "10"};
		binaryEquivalent(data, mnemonics, Registers, modes, numOfLines, rawBinaryData, ptrToNos);
                formattedBinaryEquivalent(data, mnemonics, Registers, modes, numOfLines, binaryData, ptrToNos);

		for(i=0; i<1024; i++)
		{
			/*if(binaryData[i]=='\0')
			{
				break;
			}*/

			/*if(i%4==0&&i!=0)
			{
				printf("\t");
			}*/
            if(buffer[i] == '\0')
            {
                printf("It has null char in %dth segment",i);
                break;
            }

			printf("%c",buffer[i]);
		}

		/*printf("%s", binaryData);
		printf("\n");*/

		//printf("%s", buffer);
		printf("\n");

		binaryToHex(rawBuffer, hexData);

		scanf("%c",&ch);
}
}


int line_num(const char * filename)
{
	puts("function : line_num - executing!\n");
	FILE *f;
	char c;
	int lines = 0;

	f = fopen( "assembler.txt", "r+");

	if(f == NULL)
	return 0;

	while((c = fgetc(f)) != EOF)
	if(c == '\n')
	lines++;

	fclose(f);

	/*if(c != '\n')
	lines++;*/

	return lines;
}

void bufferProcessor(char * buffer, expressionData * dataStore, const int bufferSize,const int maxOperands)
{
	puts("function : bufferProcessor - executing!\n");
	int tracker = 1;
	int i=0,n=0,j=0;
	for(i=0;buffer[i]!='\0';i++)
	{

		if(buffer[i]==',')
		{
			continue;
		}

		else if(buffer[i]=='\n')
		{
			j=0;
			tracker=1;
			n++;
		}

		else if(buffer[i]!=' ')
		{
			if(tracker==1)
			{
				dataStore[n].opcode[j] = buffer[i];
				j++;
			}

			else if(tracker==2)
			{
				dataStore[n].operand1[j] = buffer[i];
				j++;
			}

			else if(tracker==3)
			{
				dataStore[n].operand2[j] = buffer[i];
				j++;
			}

			else if(tracker==4)
			{
				dataStore[n].operand3[j] = buffer[i];
				j++;
			}

			else if(tracker==5)
			{
				dataStore[n].operand4[j] = buffer[i];
				j++;
			}
		}
		else if(buffer[i]==' ')
		{	if(tracker==(maxOperands+1)){tracker=1;}
			tracker++;
			j=0;
			continue;
		}

	}
}

void binaryEquivalent( const expressionData * data, const struct mnemonicString mnemonics, const struct registers Registers, const struct mode modes, const int numOfLines,
char * binaryData, const int * excludedNo)
{
	puts("function : binaryEquivalent - executing!\n");
	int i, appendCounter=0;

	for(i=0; i<numOfLines; i++)
	{


		if(strcmp(data[i].opcode, "MOV")==0)
		{
			strcpy(binaryData,mnemonics.MOV);
      charPrinter(binaryData, "This is MOV encountered");
		}
		else if(strcmp(data[i].opcode, "HLT")==0)
		{
			strcpy(binaryData,mnemonics.HLT);
		}
		else if(strcmp(data[i].opcode, "NEG")==0)
		{
			strcpy(binaryData,mnemonics.NEG);
		}
		else if(strcmp(data[i].opcode, "AND")==0)
		{
			strcpy(binaryData,mnemonics.AND);
		}
		else if(strcmp(data[i].opcode, "XOR")==0)
		{
			strcpy(binaryData,mnemonics.XOR);
		}
		else if(strcmp(data[i].opcode, "OR")==0)
		{
			strcpy(binaryData,mnemonics.OR);
		}
		else if(strcmp(data[i].opcode, "LSR")==0)
		{
			strcpy(binaryData,mnemonics.LSR);
		}
		else if(strcmp(data[i].opcode, "LSR")==0)
		{
			strcpy(binaryData,mnemonics.LSR);
		}
		else if(strcmp(data[i].opcode, "JMP")==0)
		{
			strcpy(binaryData,mnemonics.JMP);
		}
		else if(strcmp(data[i].opcode, "ADD")==0)
		{
			strcpy(binaryData,mnemonics.ADD);
		}
		else if(strcmp(data[i].opcode, "SUB")==0)
		{
			strcpy(binaryData,mnemonics.SUB);
		}
		else
		{
			printf("mnemonic not found on %dth iterative\n", i);
		}





		if(data[i].operand1[0] == '*'||data[i].operand1[1] == '*')
		{
				if(strcmp(data[i].operand1, "*R1")==0)
				{
					strcat(binaryData, Registers.R1);
		    	strcat(binaryData, modes.ptoperandMode);
          charPrinter(binaryData, "This is *R1 encountered");
				}
				else if(strcmp(data[i].operand1, "*R2")==0)
				{
					strcat(binaryData, Registers.R2);
		    	strcat(binaryData, modes.ptoperandMode);
				}
				else if(strcmp(data[i].operand1, "*R3")==0)
				{
					strcat(binaryData, Registers.R3);
		    	strcat(binaryData, modes.ptoperandMode);
				}
				else if(strcmp(data[i].operand1, "*R4")==0)
				{
					strcat(binaryData, Registers.R4);
		    	strcat(binaryData, modes.ptoperandMode);
				}
				else if(strcmp(data[i].operand1, "*R5")==0)
				{
					strcat(binaryData, Registers.R5);
                    strcat(binaryData, modes.ptoperandMode);
				}
				else
				{
					printf("operand 1 not found in %dth iterative\n",i);
          if(appendCounter==0)
					{
       		  appendEOL(binaryData, 10);
						//strcat(binaryData, "\n");
						appendCounter++;
					}
          charPrinter(binaryData, "This is Without operand encountered");
				}

		}
		else if(data[i].operand1[0] == 'R'||data[i].operand1[1] == 'R')
		{
			//puts("R str is getting executed!");
			if(strcmp(data[i].operand1, "R1")==0)
			{
				//puts("R1 str is getting executed!");
				strcat(binaryData, Registers.R1);
		    strcat(binaryData, modes.operandMode);
        charPrinter(binaryData, "This is R1 encountered");
			}
			else if(strcmp(data[i].operand1, "R2")==0)
			{
				//puts("R2 str is getting executed!");
				strcat(binaryData, Registers.R2);
		    strcat(binaryData, modes.operandMode);
			}
			else if(strcmp(data[i].operand1, "R3")==0)
			{
				//puts("R3 str is getting executed!");
				strcat(binaryData, Registers.R3);
		    strcat(binaryData, modes.operandMode);
			}
			else if(strcmp(data[i].operand1, "R4")==0)
			{
				//puts("R4 str is getting executed!");
				strcat(binaryData, Registers.R4);
		    strcat(binaryData, modes.operandMode);
			}
			else if(strcmp(data[i].operand1, "R5")==0)
			{
				//puts("R5 str is getting executed!");
				strcat(binaryData, Registers.R5);
		    strcat(binaryData, modes.operandMode);
			}
			else
			{
				printf("Unable to find the mode for operand 1 in %dth iterative\n",i);
        if(appendCounter==0)
				{
        	appendEOL(binaryData, 10);
					//strcat(binaryData, "\n");
					appendCounter++;
				}
        charPrinter(binaryData, "This is Without operand encountered");
			}
		}
		else if(data[i].operand1[0] == '#'||data[i].operand1[1] == '#')
		{
			strcat(binaryData, Registers.INTERMEDIATE);
			strcat(binaryData, modes.interMode);
			//strcat(binaryData, "\n");
			intermediateDataPrint(data[i].operand1, binaryData);
		}
		else
		{
			printf("operand 1 not found in %dth iterative\n",i);
      if(appendCounter==0)
			{
        appendEOL(binaryData, 10);
				//strcat(binaryData, "\n");
				appendCounter++;
			}
      charPrinter(binaryData, "This is Without operand encountered");
		}




		if(data[i].operand2[0] == '*'||data[i].operand2[1] == '*')
		{
				if(strcmp(data[i].operand2, "*R1")==0)
				{
					strcat(binaryData, Registers.R1);
		    	strcat(binaryData, modes.ptoperandMode);
					//strcat(binaryData, "\n");
				}
				else if(strcmp(data[i].operand2, "*R2")==0)
				{
					strcat(binaryData, Registers.R2);
		    	strcat(binaryData, modes.ptoperandMode);
					//strcat(binaryData, "\n");
				}
				else if(strcmp(data[i].operand2, "*R3")==0)
				{
					strcat(binaryData, Registers.R3);
		    	strcat(binaryData, modes.ptoperandMode);
					//strcat(binaryData, "\n");
				}
				else if(strcmp(data[i].operand2, "*R4")==0)
				{
					strcat(binaryData, Registers.R4);
		    	strcat(binaryData, modes.ptoperandMode);
					//strcat(binaryData, "\n");
				}
				else if(strcmp(data[i].operand2, "*R5")==0)
				{
					strcat(binaryData, Registers.R5);
		    	strcat(binaryData, modes.ptoperandMode);
					//strcat(binaryData, "\n");
				}
				else
				{
					printf("operand 2 not found in %dth iterative\n",i);
          if(appendCounter==0)
					{
       		 appendEOL(binaryData, 10);
					 appendCounter++;
					}

					//strcat(binaryData, "\n");
          charPrinter(binaryData, "This is Without operand encountered");
				}

		}
		else if(data[i].operand2[0] == 'R'||data[i].operand2[1] == 'R')
		{
			//puts("R str is getting executed!");
			if(strcmp(data[i].operand2, "R1")==0)
			{
				strcat(binaryData, Registers.R1);
                strcat(binaryData, modes.operandMode);
                //strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R2")==0)
			{
				strcat(binaryData, Registers.R2);
		    strcat(binaryData, modes.operandMode);
			  //strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R3")==0)
			{
				//puts("R3 str is getting executed!");
				strcat(binaryData, Registers.R3);
		    strcat(binaryData, modes.operandMode);
			  //strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R4")==0)
			{
				strcat(binaryData, Registers.R4);
		    strcat(binaryData, modes.operandMode);
			  //strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R5")==0)
			{
				strcat(binaryData, Registers.R5);
		    strcat(binaryData, modes.operandMode);
			  //strcat(binaryData, "\n");
			}
			else
			{
				printf("Unable to find the mode for operand 1 in %dth iterative\n",i);
				if(appendCounter==0)
				{
        appendEOL(binaryData, 10);
				appendCounter++;
				}

			  //strcat(binaryData, "\n");
        charPrinter(binaryData, "This is Without operand encountered");
			}
		}
		else if(data[i].operand2[0] == '#'||data[i].operand2[1] == '#')
		{
			strcat(binaryData, Registers.INTERMEDIATE);
			strcat(binaryData, modes.interMode);
			//strcat(binaryData, "\n");
      charPrinter(binaryData, "This is intermediate encountered");
			intermediateDataPrint(data[i].operand2, binaryData);
      charPrinter(binaryData, "This is intermediate data encountered");
		}
		else
		{
			printf("operand 2 not found in %dth iterative\n",i);
			if(appendCounter==0)
			{
				appendEOL(binaryData, 10);
				appendCounter++;
			}

		  //strcat(binaryData, "\n");
      charPrinter(binaryData, "This is Without operand encountered");
		}


		//strcat(binaryData, "\0");
		puts("function : binaryEquivalent - ended!\n");

		if(i==0)
		{
			strcpy(rawBuffer, binaryData);
		}
		else{
			strcat(rawBuffer, binaryData);
		}

	}
}


int isEmpty(const char * string)
{
	puts("function : isEmpty - executing!\n");
	int i = 0;
	while(string[i]!='\0')
	{
	  if(string[i]!=' ' || string[i]!='\n')
  	{
			return 0;
		}
	}
	return 1;
}


void formattedBinaryEquivalent( const expressionData * data, const struct mnemonicString mnemonics, const struct registers Registers, const struct mode modes, const int numOfLines,
 char * binaryData, const int * excludedNo)
{
	puts("function : binaryEquivalent - executing!\n");
	int i, appendCounter=0;
	FILE * outputFile = fopen("binaryOutput.txt","w");
	if(outputFile==NULL){puts("Error opening output file.");}

	for(i=0; i<numOfLines; i++)
	{


		if(strcmp(data[i].opcode, "MOV")==0)
		{
			strcpy(binaryData,mnemonics.MOV);
      charPrinter(binaryData, "This is MOV encountered");
		}
		else if(strcmp(data[i].opcode, "HLT")==0)
		{
			strcpy(binaryData,mnemonics.HLT);
		}
		else if(strcmp(data[i].opcode, "NEG")==0)
		{
			strcpy(binaryData,mnemonics.NEG);
		}
		else if(strcmp(data[i].opcode, "AND")==0)
		{
			strcpy(binaryData,mnemonics.AND);
		}
		else if(strcmp(data[i].opcode, "XOR")==0)
		{
			strcpy(binaryData,mnemonics.XOR);
		}
		else if(strcmp(data[i].opcode, "OR")==0)
		{
			strcpy(binaryData,mnemonics.OR);
		}
		else if(strcmp(data[i].opcode, "LSR")==0)
		{
			strcpy(binaryData,mnemonics.LSR);
		}
		else if(strcmp(data[i].opcode, "LSR")==0)
		{
			strcpy(binaryData,mnemonics.LSR);
		}
		else if(strcmp(data[i].opcode, "JMP")==0)
		{
			strcpy(binaryData,mnemonics.JMP);
		}
		else if(strcmp(data[i].opcode, "ADD")==0)
		{
			strcpy(binaryData,mnemonics.ADD);
		}
		else if(strcmp(data[i].opcode, "SUB")==0)
		{
			strcpy(binaryData,mnemonics.SUB);
		}
		else
		{
			printf("mnemonic not found on %dth iterative\n", i);
		}





		if(data[i].operand1[0] == '*'||data[i].operand1[1] == '*')
		{
				if(strcmp(data[i].operand1, "*R1")==0)
				{
					strcat(binaryData, Registers.R1);
		    	strcat(binaryData, modes.ptoperandMode);
          charPrinter(binaryData, "This is *R1 encountered");
				}
				else if(strcmp(data[i].operand1, "*R2")==0)
				{
					strcat(binaryData, Registers.R2);
		    	strcat(binaryData, modes.ptoperandMode);
				}
				else if(strcmp(data[i].operand1, "*R3")==0)
				{
					strcat(binaryData, Registers.R3);
		    	strcat(binaryData, modes.ptoperandMode);
				}
				else if(strcmp(data[i].operand1, "*R4")==0)
				{
					strcat(binaryData, Registers.R4);
		    	strcat(binaryData, modes.ptoperandMode);
				}
				else if(strcmp(data[i].operand1, "*R5")==0)
				{
					strcat(binaryData, Registers.R5);
                    strcat(binaryData, modes.ptoperandMode);
				}
				else
				{
					printf("operand 1 not found in %dth iterative\n",i);
          if(appendCounter==0)
					{
       		  appendEOL(binaryData, 10);
						strcat(binaryData, "\n");
						appendCounter++;
					}
          charPrinter(binaryData, "This is Without operand encountered");
				}

		}
		else if(data[i].operand1[0] == 'R'||data[i].operand1[1] == 'R')
		{
			//puts("R str is getting executed!");
			if(strcmp(data[i].operand1, "R1")==0)
			{
				//puts("R1 str is getting executed!");
				strcat(binaryData, Registers.R1);
		    strcat(binaryData, modes.operandMode);
        charPrinter(binaryData, "This is R1 encountered");
			}
			else if(strcmp(data[i].operand1, "R2")==0)
			{
				//puts("R2 str is getting executed!");
				strcat(binaryData, Registers.R2);
		    strcat(binaryData, modes.operandMode);
			}
			else if(strcmp(data[i].operand1, "R3")==0)
			{
				//puts("R3 str is getting executed!");
				strcat(binaryData, Registers.R3);
		    strcat(binaryData, modes.operandMode);
			}
			else if(strcmp(data[i].operand1, "R4")==0)
			{
				//puts("R4 str is getting executed!");
				strcat(binaryData, Registers.R4);
		    strcat(binaryData, modes.operandMode);
			}
			else if(strcmp(data[i].operand1, "R5")==0)
			{
				//puts("R5 str is getting executed!");
				strcat(binaryData, Registers.R5);
		    strcat(binaryData, modes.operandMode);
			}
			else
			{
				printf("Unable to find the mode for operand 1 in %dth iterative\n",i);
        if(appendCounter==0)
				{
        	appendEOL(binaryData, 10);
					strcat(binaryData, "\n");
					appendCounter++;
				}
        charPrinter(binaryData, "This is Without operand encountered");
			}
		}
		else if(data[i].operand1[0] == '#'||data[i].operand1[1] == '#')
		{
			strcat(binaryData, Registers.INTERMEDIATE);
			strcat(binaryData, modes.interMode);
			strcat(binaryData, "\n");
			intermediateDataPrint(data[i].operand1, binaryData);
			strcat(binaryData, "\n");
		}
		else
		{
			printf("operand 1 not found in %dth iterative\n",i);
      if(appendCounter==0)
			{
        appendEOL(binaryData, 10);
				strcat(binaryData, "\n");
				appendCounter++;
			}
      charPrinter(binaryData, "This is Without operand encountered");
		}




		if(data[i].operand2[0] == '*'||data[i].operand2[1] == '*')
		{
				if(strcmp(data[i].operand2, "*R1")==0)
				{
					strcat(binaryData, Registers.R1);
		    	strcat(binaryData, modes.ptoperandMode);
					strcat(binaryData, "\n");
				}
				else if(strcmp(data[i].operand2, "*R2")==0)
				{
					strcat(binaryData, Registers.R2);
		    	strcat(binaryData, modes.ptoperandMode);
					strcat(binaryData, "\n");
                }
				else if(strcmp(data[i].operand2, "*R3")==0)
				{
					strcat(binaryData, Registers.R3);
		    	strcat(binaryData, modes.ptoperandMode);
					strcat(binaryData, "\n");
				}
				else if(strcmp(data[i].operand2, "*R4")==0)
				{
					strcat(binaryData, Registers.R4);
		    	strcat(binaryData, modes.ptoperandMode);
					strcat(binaryData, "\n");
				}
				else if(strcmp(data[i].operand2, "*R5")==0)
				{
					strcat(binaryData, Registers.R5);
		    	strcat(binaryData, modes.ptoperandMode);
					strcat(binaryData, "\n");
				}
				else
				{
					printf("operand 2 not found in %dth iterative\n",i);
          if(appendCounter==0)
					{
       		 appendEOL(binaryData, 10);
					 appendCounter++;
					}

					strcat(binaryData, "\n");
          charPrinter(binaryData, "This is Without operand encountered");
				}

		}
		else if(data[i].operand2[0] == 'R'||data[i].operand2[1] == 'R')
		{
			//puts("R str is getting executed!");
			if(strcmp(data[i].operand2, "R1")==0)
			{
				strcat(binaryData, Registers.R1);
                strcat(binaryData, modes.operandMode);
                strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R2")==0)
			{
				strcat(binaryData, Registers.R2);
		    strcat(binaryData, modes.operandMode);
			  strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R3")==0)
			{
				//puts("R3 str is getting executed!");
				strcat(binaryData, Registers.R3);
		    strcat(binaryData, modes.operandMode);
			  strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R4")==0)
			{
				strcat(binaryData, Registers.R4);
		    strcat(binaryData, modes.operandMode);
			  strcat(binaryData, "\n");
			}
			else if(strcmp(data[i].operand2, "R5")==0)
			{
				strcat(binaryData, Registers.R5);
		    strcat(binaryData, modes.operandMode);
			  strcat(binaryData, "\n");
			}
			else
			{
				printf("Unable to find the mode for operand 1 in %dth iterative\n",i);
				if(appendCounter==0)
				{
        appendEOL(binaryData, 10);
				appendCounter++;
				}

			  strcat(binaryData, "\n");
        charPrinter(binaryData, "This is Without operand encountered");
			}
		}
		else if(data[i].operand2[0] == '#'||data[i].operand2[1] == '#')
		{
			strcat(binaryData, Registers.INTERMEDIATE);
			strcat(binaryData, modes.interMode);
			strcat(binaryData, "\n");
      charPrinter(binaryData, "This is intermediate encountered");
			intermediateDataPrint(data[i].operand2, binaryData);
			strcat(binaryData, "\n");
      charPrinter(binaryData, "This is intermediate data encountered");
		}
		else
		{
			printf("operand 2 not found in %dth iterative\n",i);
			if(appendCounter==0)
			{
				appendEOL(binaryData, 10);
				appendCounter++;
			}

		  strcat(binaryData, "\n");
      charPrinter(binaryData, "This is Without operand encountered");
		}


		//strcat(binaryData, "\0");
		puts("function : binaryEquivalent - ended!\n");

		if(i==0)
		{
			strcpy(buffer, binaryData);
		}
		else{
			strcat(buffer, binaryData);
		}

	}
	fputs(  buffer, outputFile);
	fclose(outputFile);
}



void intermediateDataPrint( const char * intermediateAdd, char * binaryData)
{
	puts("function : intermediateDataPrint - executing!");
	char hexIntermediate[10];
	//strcpy(hexIntermediate, intermediateAdd);
	int i,j,count=0;
	for(j=0; intermediateAdd[j]!='\0';j++)
	{
		puts("This is the fucking loop!");
		if(intermediateAdd[j]=='#')
		{
			continue;
		}
		hexIntermediate[i] = intermediateAdd[j];
		i++;count++;
	}
	i=0;j=0;
	if(count<4)
	{
		if(count==1)
		{
			strcat(binaryData, "000000000000");
		}
		else if(count==2)
		{
			strcat(binaryData, "00000000");
		}
		else if(count==3)
		{
			strcat(binaryData, "0000");
		}
	}

	while(hexIntermediate[i]){

				if(hexIntermediate[i]=='#'){continue;}

         switch(hexIntermediate[i]){
             case '0': strcat(binaryData,"0000"); break;
             case '1': strcat(binaryData,"0001"); break;
             case '2': strcat(binaryData,"0010"); break;
             case '3': strcat(binaryData,"0011"); break;
             case '4': strcat(binaryData,"0100"); break;
             case '5': strcat(binaryData,"0101"); break;
             case '6': strcat(binaryData,"0110"); break;
             case '7': strcat(binaryData,"0111"); break;
             case '8': strcat(binaryData,"1000"); break;
             case '9': strcat(binaryData,"1001"); break;
             case 'A': strcat(binaryData,"1010"); break;
             case 'B': strcat(binaryData,"1011"); break;
             case 'C': strcat(binaryData,"1100"); break;
             case 'D': strcat(binaryData,"1101"); break;
             case 'E': strcat(binaryData,"1110"); break;
             case 'F': strcat(binaryData,"1111"); break;
             case 'a': strcat(binaryData,"1010"); break;
             case 'b': strcat(binaryData,"1011"); break;
             case 'c': strcat(binaryData,"1100"); break;
             case 'd': strcat(binaryData,"1101"); break;
             case 'e': strcat(binaryData,"1110"); break;
             case 'f': strcat(binaryData,"1111"); break;
             default:  printf("\nInvalid hexadecimal digit %c\n",hexIntermediate[i]);break;
         }
         i++;
    }

	//strcat(binaryData, "\n");

}


void appendEOL(char * binaryData, const int nos)
{
  int i;
  for(i=0;i<nos;i++)
  {
    strcat(binaryData, "0");
  }
  strcat(binaryData, "\n");
}

void charPrinter( const char * data, const char * msg)
{
  int i;
  printf("%s :\n", msg);
  for(i=0;i<100;i++)
  {
    printf("%c",data[i]);
  }
  printf("\n");
}

void binaryToHex( const char * buffer, char * hexData)
{
    puts("the function : binaryToHex is executing.");
    int i=0,k=0,l=0,z=0,newLen;
	int nullPtrExec = 0;
	int newLineCount = 0;
	char tempBuff[MAXBUFLEN];
	char tempData[4];
	FILE * outputFile = fopen("hexOutput.txt", "w");
	FILE * binaryStorage = fopen("binaryOutput.txt", "r");
	if(outputFile==NULL)
	{
		puts("Error opening hex output file");
		nullPtrExec=1;
	}
	/*if(binaryStorage == NULL)
	{
        puts("Error opening binary storage file");
        nullPtrExec=1;
	}
	else
	{
        size_t newLen = fread(hexBuff, sizeof(char), MAXBUFLEN, binaryStorage);
        if (newLen == 0) {
            fputs("Error reading file", stderr);
        } else {
            hexBuff[++newLen] = '\0';
        }

        for(i = newLen; i<MAXBUFLEN; i++)
        {
            hexBuff[i]='\0';
        }
	}

    puts(hexBuff);

	while(buffer[l]!='\0')
	{
        if(hexBuff[l]!='\n')
        {
            tempBuff[z] = buffer[l];
            ++z;++l;
        }
        ++l;
	}

	for(i = z; i<MAXBUFLEN; i++)
        {
            tempBuff[i]='\0';
        }


    puts(tempBuff);*/
    puts("Printing buffer");
    puts(buffer);
	while(buffer[k]!='\0')
	{

        //if(buffer[k]=='\n'){k++;continue;}
        int i,j=k;
        if(k%4==0)
        {
            for(i=0;i<4;i++)
            {
                tempData[i] = buffer[j];
                ++j;
            }

        ++newLineCount;
        printf("The total length is %d\n",j);
        puts("the function : binaryToHex if statement is executing.");
        puts(tempData);

        if(strcmp(tempData, "0000")==0)
        {
            strcat(hexData, "0");
        }
        else if(strcmp(tempData, "0001")==0)
        {
            strcat(hexData, "1");
        }
        else if(strcmp(tempData, "0010")==0)
        {
            strcat(hexData, "2");
        }
        else if(strcmp(tempData, "0011")==0)
        {
            strcat(hexData, "3");
        }
        else if(strcmp(tempData, "0100")==0)
        {
            strcat(hexData, "4");
        }
        else if(strcmp(tempData, "0101")==0)
        {
            strcat(hexData, "5");
        }
        else if(strcmp(tempData, "0110")==0)
        {
            strcat(hexData, "6");
        }
        else if(strcmp(tempData, "0111")==0)
        {
            strcat(hexData, "7");
        }
        else if(strcmp(tempData, "1000")==0)
        {
            strcat(hexData, "8");
        }
        else if(strcmp(tempData, "1001")==0)
        {
            strcat(hexData, "9");
        }
        else if(strcmp(tempData, "1010")==0)
        {
            strcat(hexData, "A");
        }
        else if(strcmp(tempData, "1011")==0)
        {
            strcat(hexData, "B");
        }
        else if(strcmp(tempData, "1100")==0)
        {
            strcat(hexData, "C");
        }
        else if(strcmp(tempData, "1101")==0)
        {
            strcat(hexData, "D");
        }
        else if(strcmp(tempData, "1110")==0)
        {
            strcat(hexData, "E");
        }
        else if(strcmp(tempData, "1011")==0)
        {
            strcat(hexData, "F");
        }
        else if(strcmp(tempData, "1010")==0)
        {
            strcat(hexData, "a");
        }
        else if(strcmp(tempData, "1011")==0)
        {
            strcat(hexData, "b");
        }
        else if(strcmp(tempData, "1100")==0)
        {
            strcat(hexData, "c");
        }
        else if(strcmp(tempData, "1101")==0)
        {
            strcat(hexData, "d");
        }
        else if(strcmp(tempData, "1110")==0)
        {
            strcat(hexData, "e");
        }
        else if(strcmp(tempData, "1011")==0)
        {
            strcat(hexData, "f");
        }
        else
        {
            puts("Error encountered : Not Found.");
        }

        if(newLineCount%4==0&&i!=0)
        {
            if(hexData[strlen(hexData)]!='\n')
            {
                strcat(hexData, "\n");
            }
        }

      }// closing of if

      k++;
    }

        fputs(hexData, outputFile);

        if(nullPtrExec==0)
        {
            fclose(outputFile);
            fclose(binaryStorage);
        }
        puts("the function : binaryToHex is finshed.");
        //free(hexData);
        //return hexData;
}
