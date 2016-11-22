#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include"sicAssembler.c"
FILE * fpsource,*fpinter;
char line[128],label[45],opcode[45], operand[45], operand_value[10];
long int locctr = 0 ,program_length = 0;
bool error_flag = false;
struct symtab *first = NULL;
int i=0,count=0,starting_add;
void tokenize()
{
	memset(line,' ',128);
	memset(label,' ',45);
	memset(opcode,' ',45);
	memset(operand,' ',45);
	memset(operand_value,' ',10);
	strcpy(line,read_next_input_line(fpsource));
        strcpy(label,get_label(line));
        strcpy(opcode,get_op_code(line,label));
        strcpy(operand,get_operand(line,label,opcode));
}
void main()
{
//opeing source code file
	fpsource= fopen("source.2pasm","r");
	if (fpsource==NULL)
	{
		printf("\nError opening the file.");
	}
//reading first input line
	fgets(line,128,fpsource);
//a getting values of label,opcode,operand
	strcpy(label,get_label(line));
	strcpy(opcode,get_op_code(line,label));
	strcpy(operand,get_operand(line,label,opcode));
//if the opcode is START
	if(strcmp(opcode,"START")==0)	
	{
		sscanf(operand,"%d",&starting_add);
//initializing location counter with the value of operand of start
		sscanf(operand,"%ld",&locctr);		
		fpinter = fopen("intermediate.txt","w");
//writing line in the intermediate file
		if(fputs(line,fpinter)==EOF)
		{
			printf("\nError writing in intermediate file.Exitting.");
			exit(0);
		}
//reading next input line
		tokenize();
	}
	else
		locctr = 0;
	while(strcmp(line,"END\n")!=0)
	{
		if(line[0]!='.')
		{
			if(label!=NULL)
			{
				if(search_symbol_table_for_label(label,first)!=-1)
				{
					//duplicate symbol
					error_flag = true;
					break;
				}
				else 
				{
					insert_label_locctr_into_symbol_table(label,locctr,&first);
				}				
			}
			if(search_op_code_table_for_opcode(opcode)!=-1)
			{
				locctr +=3;
			}
			else if(strcmp(opcode,"WORD")==0)
			{
				locctr +=3;
			}
			else if(strcmp(opcode,"RESW")==0)
			{
				locctr += 3*atoi(operand);
			}
			else if(strcmp(opcode,"RESB")==0)
			{
				locctr += atoi(operand);
			}
			else if(strcmp(opcode,"BYTE")==0)
			{
				if(operand[0]=='c'||operand[0]=='C')
				{
					while(operand[i]!='\0')
					{
						i++;
						count++;
					}
					locctr += (count-4);
					i=0;
					count=0;
				}
				else
				{
					while(operand[i]!='\0')
					{
						if(i>1&&(operand[i]!='\''))
						{
							operand_value[i-2] = operand[i];
						}
						i++;
					}
					locctr += strtol(operand_value,NULL,16);
					
				}
			}
			else
			{
				error_flag == true;
				break;
			}
		}
		write_line_to_intermediate_file(fpinter,line);
		tokenize();
	}	
	write_line_to_intermediate_file(fpinter,line);
	program_length = locctr - starting_add;
// Printing the symtab
	printf("\nHere it comes...");
	struct symtab *tmp=first;
	while(tmp!=NULL){
		printf("%s\t%ld\n", tmp->label, tmp->address);
		tmp=tmp->next;
	}
	printf("\nProgram length is %ld", program_length);
	if(error_flag) printf("There was an error!");
}
