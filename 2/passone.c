#include<stdio.h>
#include<string.h>
void main()
{
  FILE *ip,*optab,*sym, *lenfile;
int lc,sa,l,op1,o,len;
char m1[20],la[20],op[20],otp[20];
 ip=fopen("input.2pasm","r");
 sym=fopen("symtab","w");
 lenfile=fopen("length", "w");
fscanf(ip,"%s %s %d",la,m1,&op1);
if(strcmp(m1,"START")==0)
 {
sa=op1;
lc=sa;
printf("\t%s\t%s\t%d\n",la,m1,op1);
 }
else
lc=0;
fscanf(ip,"%s %s",la,m1); 
while(!feof(ip))
 {
fscanf(ip,"%s",op);
printf("\n%d\t%s\t%s\t%s\n",lc,la,m1,op);
 if(strcmp(la,"-")!=0)
  {
fprintf(sym,"\n%d\t%s\n",lc,la);
  }
  optab=fopen("optab","r");
fscanf(optab,"%s %d",otp,&o);
while(!feof(optab))
  {
if(strcmp(m1,otp)==0)
   {
lc=lc+3;
break;
   }
fscanf(optab,"%s %d",otp,&o);
 }
fclose(optab);
if(strcmp(m1,"WORD")==0)
{
lc=lc+3;
}
else if(strcmp(m1,"RESW")==0)
{
op1=atoi(op);
lc=lc+(3*op1);
}
else if(strcmp(m1,"BYTE")==0)
 {
if(op[0]=='X')
lc=lc+1;
else
   {
len=strlen(op)-3;
lc=lc+len;
}
   }
else if(strcmp(m1,"RESB")==0)
   {
op1=atoi(op);
lc=lc+op1;
}
fscanf(ip,"%s%s",la,m1);
 }
if(strcmp(m1,"END")==0)
 {
printf("Program length =%d\n",lc-sa);
 fprintf(lenfile, "%d", lc-sa);
}
fclose(ip);
fclose(sym);
 fclose(lenfile);
}
