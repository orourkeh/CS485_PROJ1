#include <stdio.h>

#define MEMORY_SIZE 131072//4026*32
void readBinary(char*);
unsigned int memRead(unsigned int);
unsigned int varRead(unsigned int);


int memory[MEMORY_SIZE];

struct operation
{
	unsigned int opCode;
	unsigned int var0;
	unsigned int var1;
	unsigned int var2;
};

struct operation* programCounter[];//List of all op codes and paramters

int main(int argc, char* argv[] )
{
	if(argc < 2)
	{
		printf("Usage: main [binary filename]\n");
	}
	//add check for .capexe extension
	readBinary(argv[1]);
	//turns all bits to 0
	for(int i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = 0;
	}
}

void readBinary(char* filename)
{
	printf("%s", filename);
	FILE* binaryFile;
	binaryFile = fopen(filename, "rb");
	if(binaryFile == NULL)
	{
		printf("Could not open file %s", filename);
		return;	
	}
	else
	{
		for(int i = 0; i <4; i++)
		{
			printf("\n");
			unsigned int word;
			fread(&word, sizeof(word), 1, binaryFile);
		//	programCounter[0]->opCode = word;
			printf("%x\n", word);
		}//read opcode then send paramters to fucntion
	}
}


unsigned int varRead(unsigned int var)
{
	if(var >= 0x8)//if memory adress
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
	return 0;
}
void memWrite(unsigned int adress, unsigned int value)
{
}
void add(struct operation op)
{
	unsigned int value0 = varRead(op.var0);
	unsigned int value1 = varRead(op.var1);
	memWrite(op.var3, value0 + value1);
}
void sub(struct operation op)
{
        unsigned int value0 = varRead(op.var0);
        unsigned int value1 = varRead(op.var1);
        memWrite(op.var3, value0 - value1);
}
void or(struct operation op)
{
        unsigned int value0 = varRead(op.var0);
        unsigned int value1 = varRead(op.var1);
        memWrite(op.var3, value0 | value1);
}
void and(struct operation op)
{
	unsigned int value0 = varRead(op.var0);
        unsigned int value1 = varRead(op.var1);
        memWrite(op.var3, value0 & value1);
}
