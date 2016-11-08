#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define listLength 10
struct symtab{
  char label[35];
  long address;
  symtab *next;
};

struct optab{
  char opcode[9];
  long hexcode;
};

char* read_next_input_line(FILE *f){
  char line[128];
  fgets(line, sizeof(line), f);
  return line;
}

char* get_label(char* line){
  char word[]=strtok(line, " ");
  if(search_op_code_table_for_opcode(word)==-1)
    return word;
  return NULL;
}

char* get_op_code(char* line, char* label){
  char word[]=strtok(line, " ");
  if(!label) return word;
  return strtok(NULL, " ");
}

char* get_operand(char* line, char* label, char* opcode){
 }

long search_symbol_table_for_label(char* label, struct symtab *first){
  while(first->next!=NULL)
    if(!strcmp(first->label, label))
      return first->address;
  return -1;
}

void insert_label_locctr_into_symbol_table(char* label, long locctr, struct symtab **first){
  struct symtab *tmp = (struct symtab*)malloc(sizeof(struct symtab));
  struct *traverse;
  tmp->next = NULL;
  tmp->address = locctr;
  if(!(*first)) *first = tmp;
  else {
    traverse=*first;
    while(traverse->next!=NULL) traverse=traverse->next;
    traverse->next=tmp;
  }
}

long search_opcode_table_for_opcode(char* opcodeProvided){
  int i=listLength;
  while(--i)
    if(opcodeList[i].opcode==opcodeProvided)
      return opcodeList[i].hexcode;
  return -1;
}

void write_line_to_intermediate_file(FILE *f, char* line){
  fprintf(f, "%s\n", line);
}
