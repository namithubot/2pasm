#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define listLength 4
long search_op_code_table_for_opcode(char*);
struct symtab{
  char label[35];
  long address;
  struct symtab *next;
};

struct optab{
  char opcode[9];
  long hexcode;
}opcodeList[]={
	{"LDA",00},
	{"STA",23},
        {"ADD",01},
	{"SUB",05}
};

char line[128];
char word[23];
char* read_next_input_line(FILE *f){
  //char line[128];
  fgets(line, 128, f);
  return line;
}

char* get_label(char* line){
  //char word[23];
  strcpy(word, strtok(line, " "));
  // char * wordptr;
  //int i=0;
  //  wordptr = strchr(line,' ');
  //while(line[i]!=*wordptr)
  //{
  //word[i]=line[i];
  //	i++;
  //}
   if(search_op_code_table_for_opcode(word)==-1)
    return word;
  return NULL;
}

char* get_op_code(char* line, char* label){
  //char word[23];
  strcpy(word, strtok(line, " "));
  printf("%s", word);
  if(!label) return word;
  return strtok(NULL, " ");
}

char* get_operand(char* line, char* label, char* opcode){
	if(!strcmp(opcode, "RSUB")) return NULL;
  strcpy(word, strtok(line, " "));
  strcpy(word, strtok(NULL, " "));
  if(!label) return word;
  return strtok(NULL, " ");
 }

long search_symbol_table_for_label(char* label, struct symtab *first){
  if(first){
	while(first->next!=NULL)
    if(!strcmp(first->label, label))
      return first->address;
	}
  return -1;
}

void insert_label_locctr_into_symbol_table(char* label, long locctr, struct symtab **first){
  struct symtab *tmp = (struct symtab*)malloc(sizeof(struct symtab));
  struct symtab *traverse;
  tmp->next = NULL;
  tmp->address = locctr;
  if(!(*first)) *first = tmp;
  else {
    traverse=*first;
    while(traverse->next!=NULL) traverse=traverse->next;
    traverse->next=tmp;
  }
}

long search_op_code_table_for_opcode(char* opcodeProvided){
  int i=listLength;
  while(i--)
    if(opcodeList[i].opcode==opcodeProvided)
      return opcodeList[i].hexcode;
  return -1;
}

void write_line_to_intermediate_file(FILE *f, char* line){
  fprintf(f, "%s\n", line);
}
