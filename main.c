#include <stdio.h>

#define MEMORY_SIZE 4026//4026*32
void readBinary(char*);
unsigned int memRead(unsigned int);
unsigned int varRead(unsigned int);


unsigned int memory[MEMORY_SIZE];
typedef struct
{
	unsigned int opCode;
	unsigned int var0;
	unsigned int var1;
	unsigned int var2;
}operation;

void add(operation*);
void sub(operation*);
void or(operation*);
void and(operation*);
void and(operation*);
void xor(operation*);
void not(operation*);
void slr(operation*);
void sll(operation*);
void mprint(operation*);
void mprintchars(operation*);



int main(int argc, char* argv[] )
{
	if(argc < 2)
	{
		printf("Usage: main [binary filename]\n");
		return 1;
	}
	//add check for .capexe extension
	//turns all bits to 0
	for(int i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = 0;
	}
	readBinary(argv[1]);
}

void readBinary(char* filename)
{
	FILE* binaryFile;
	binaryFile = fopen(filename, "rb");
	if(binaryFile == NULL)
	{
		printf("Could not open file %s", filename);
		return;	
	}
	else
	{
		unsigned int opSize = 0;
		unsigned int word = NULL;
		while(fread(&word, sizeof(word), 1, binaryFile))//need to get number of lines 
                {
                        fread(&word, sizeof(word), 1, binaryFile);//var 0
                        fread(&word, sizeof(word), 1, binaryFile);//var1
                        fread(&word, sizeof(word), 1, binaryFile);//var2
			opSize++;
                }//I can't figure out C dyn arrays
		fclose(binaryFile);
		
		operation opList[opSize];
		int counter = 0;
		fopen(filename, "rb");
		while(fread(&word, sizeof(word), 1, binaryFile))
		{
				
			opList[counter].opCode = word;
			fread(&word, sizeof(word), 1, binaryFile);//var 0
			opList[counter].var0 = word;
			fread(&word, sizeof(word), 1, binaryFile);//var1
			opList[counter].var1 = word;
			fread(&word, sizeof(word), 1, binaryFile);//var2
			opList[counter].var2 = word;
			counter++;
		}
		for(int i = 0; i < opSize; i++)
		{
			//printf("\n%x %x %x %x", opList[i].opCode, opList[i].var0, opList[i].var1, opList[i].var2);
			switch(opList[i].opCode)
			{
				case 0x0:
					add(&opList[i]);break;
				case 0x1:
					sub(&opList[i]);break;
				case 0x2:
					or(&opList[i]);break;
				case 0x3:
					and(&opList[i]);break;
				
                                case 0x4:
                                        xor(&opList[i]);break;
				
                                case 0x5:
                                        not(&opList[i]);break;
				
                                case 0x6:
                                        slr(&opList[i]);break;
				
                                case 0x7:
                                        sll(&opList[i]);break;
				
                                case 0x8:
                                        mprint(&opList[i]);break;
				
                                case 0x9:
                                        mprintchars(&opList[i]);break;

			}	
		}
	}
}


unsigned int varRead(unsigned int var)
{
	if(var >= 0x80000000)//if memory adress
        {
                return memRead(var);
        }
        else
        {
                return var;
        }
}
unsigned int memRead(unsigned int address)
{
	address -= 0x80000000;
	if(address <= MEMORY_SIZE)
	{
		return memory[address];
	}
	else
	{
		printf("Tried to read memory out of bound:%x>=%d", address, MEMORY_SIZE);
	}
}
void memWrite(unsigned int address, unsigned int value)
{
	address -= 0x80000000;
	if(address <= MEMORY_SIZE)
	{
		memory[address] = value;
	}
	else
	{
	        printf("Tried to write to memory space out of bound:%x>=%d", address,MEMORY_SIZE);
	}
}
void add(operation* op)
{
	unsigned int value0 = varRead(op->var0);
	unsigned int value1 = varRead(op->var1);
	memWrite(op->var2, value0 + value1);
}
void sub(operation* op)
{
        unsigned int value0 = varRead(op->var0);
        unsigned int value1 = varRead(op->var1);
        memWrite(op->var2, value0 - value1);
}
void or(operation* op)
{
        unsigned int value0 = varRead(op->var0);
        unsigned int value1 = varRead(op->var1);
        memWrite(op->var2, value0 | value1);
}
void and(operation* op)
{
	unsigned int value0 = varRead(op->var0);
        unsigned int value1 = varRead(op->var1);
        memWrite(op->var2, value0 & value1);
}
void xor(operation* op)
{
        unsigned int value0 = varRead(op->var0);
        unsigned int value1 = varRead(op->var1);
        memWrite(op->var2, value0 ^ value1);
}
void not(operation* op)
{
        unsigned int value0 = varRead(op->var0);
        memWrite(op->var2, ~value0);
}
void slr(operation* op)
{
        unsigned int value0 = varRead(op->var0);
        unsigned int value1 = varRead(op->var1);
        memWrite(op->var2, value0 >> value1);
}
void sll(operation* op)
{
        unsigned int value0 = varRead(op->var0);
        unsigned int value1 = varRead(op->var1);
        memWrite(op->var2, value0 << value1);
}

void mprint(operation* op)
{
	printf("0x%x\n", varRead(op->var0));
}
void mprintchars(operation* op)
{
	printf("%c", varRead(op->var0));
}

