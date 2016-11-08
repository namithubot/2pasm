#include<stdio.h>
void main()
{
	FILE * fpsource,fpinter;
	char line[128],label[45],opcode[45],operand[45];
	long int locctr,program_length;
	bool error_flag = false;
	struct symtab *first = NULL;
	int i=0,count=0,operand_value[10],starting_add;
//opeing source code file
	fpsource= fopen("source.2pasm","r");
	if (fp==NULL)
	{
		printf("\nError opening the file.");
	}
//reading first input line
	line = fgets(line,128,fpsource);
//getting values of label,opcode,operand
	label = get_label(line);
	opcode = get_op_code(line,label);
	operand = get_operand(line,label,opcode);
//if the opcode is START
	if(strcmp(opcode,"START")==0)	
	{
		starting_add = operand;
//initializing location counter with the value of operand of start
		locctr = operand;		
		fpinter = fopen("source.2pasm.temp","w");
//writing line in the intermediate file
		if(fputs(line,fpinter);)
			printf("\nError writing in intermediate file.");
//reading next input line
		line = read_next_inputline(fpsource);	
	}
	else
		locctr = 0;
	while(strcmp(opcode,"END")==0)
	{
		if(line[0]=='.')
		{
			line = read_next_inputline(fpsource);
			break;
		}
		else
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
					break;
				}				
			}
			if(search_opcode_table_for_opcode(opcode)!=-1)
			{
				locctr +=3;
				break;
			}
			else if(strcmp(opcode,"WORD")==0)
			{
				locctr +=3;
				break;
			}
			else if(strcmp(opcode,"RESW"))
			{
				locctr += 3*operand;
				break;
			}
			else if(strcmp(opcode,"RESB"))
			{
				locctr += operand;
				break;
			}
			else if(strcmp(opcode,"BYTE"))
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
						if(i>1&&(operand[i]!='''))
						{
							operand_value[i-2] = operand[i];
						}
						i++;
					}
					locctr += strtol(operand_value,NULL,16);
					break;
				}
			}
			else
			{
				error_flag == true;
				break;
			}
		}
		write_line_to_intermediate_file(fpinter,line);
		line = read_next_input_line(fpsource)
	}	
	write_line_to_intermediate_file(fpinter,line);
	program_length = locctr - starting_add;
}
