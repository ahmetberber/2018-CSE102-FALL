/*  Ahmet Hilmi Berber  */
/*      171044027       */
/*     CSE102 HW07      */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define IDENTIFIERSIZE 11
#define AND 'A'
#define OR 'O'
#define FLIPFLOP 'F'
#define INPUT 'I'
#define NOT 'N'
#define MAX 250

struct gate{
      char identifier[IDENTIFIERSIZE];/* this variable holds the string which belongs to the output of the logical operation's identifier */
      char inp1[IDENTIFIERSIZE];/* this variable holds the string which belons to the first input of the logical operation's identifier */
      char inp2[IDENTIFIERSIZE];/* this variable holds the string which belons to the second input of the logical operation's identifier if it is exist */
      int value;/* this variable holds the output number of logical operation */
      int input1;/* this variable holds the first input number of logical operation */
      int input2;/* this variable holds the second input number of logical operation if it is exist */
      int former;/* this variable holds the former output of the FLIPFLOP gate */
      int type;/* this variable holds the string which belongs to the operator of logical operation at each row */
      struct gate* inp1_link;/* this variable points to the first input of gate */
      struct gate* inp2_link;/* this variable points to the second input of gate */
};

int and(int x, int y);
int or(int x, int y);
int flipflop(int x, int y);
int not(int x);

int main(){
      FILE* fin1 = fopen("circuit.txt","r");
      FILE* fin2 = fopen("input.txt","r");
      FILE* fout = fopen("output.txt","w");
      int counter=0, letterCounter=0, flag=0, gateCounter=1, inputCounter=0, i=0, k=0;
      char* strInput = (char*)malloc(sizeof(char)*MAX);/* this variable holds to the each row at "input.txt" */
      char* strCircuit = (char*)malloc(sizeof(char)*MAX);/* this variable holds to the each row at "circuit.txt" */
      struct gate* gates=(struct gate*)malloc(sizeof(struct gate));
      while(fgets(strCircuit,MAX,fin1)!=NULL){/* circuit.txt */
            if(strCircuit[strlen(strCircuit)-1]=='\n'){
                  strCircuit[strlen(strCircuit)-2]='\0';
            }
            if(strCircuit[k]==INPUT){
                  strCircuit+=6;/* increment the string pointer to number of letters "INPUT" word */
                  while(strCircuit[k]!='\0'){
                        inputCounter++;/* this variable holds to the identifier number of inputs */
                        char* tempStr = (char*)malloc(sizeof(char)*IDENTIFIERSIZE);
                        while(strCircuit[k]!=' ' && strCircuit[k]!='\0'){/* get the input identifiers until the whitespace or null(end of the line) */
                              tempStr[letterCounter]=strCircuit[k];
                              letterCounter++;
                              k++;
                        }
                        for(i=0;i<strlen(tempStr);i++)
                              gates[gateCounter-1].identifier[i]=tempStr[i];/* fill the gate struct of identifiers */
                        gates[gateCounter-1].type=1;/* assume that INPUT gate's type is 1 */
                        gates[gateCounter-1].inp1_link=NULL;
                        gates[gateCounter-1].inp2_link=NULL;
                        gates=(struct gate*)realloc(gates,sizeof(struct gate)*(++gateCounter));/* and each gate, i reallocate one more gate structure */
                        k++;/* skip the whitespace after the identifier string */
                        if(strCircuit[k]=='\n'){
                              break;
                        }
                        else{
                              letterCounter=0;/* reset the number of identifier's letter */
                        }
                  }
                  k=0,letterCounter=0;/* reset the values */
            }
            else if(strCircuit[k]==AND || strCircuit[k]==OR){
                  if(strCircuit[k]==AND){
                        strCircuit+=4;/* increment the string pointer to number of letters "AND" word */
                        gates[gateCounter-1].type=2;/* assume that AND gate's type is 2 */
                  }
                  else if(strCircuit[k]==OR){
                        strCircuit+=3;/* increment the string pointer to number of letters "OR" word */
                        gates[gateCounter-1].type=3;/* assume that OR gate's type is 3 */
                  }
                  while(strCircuit[k]!='\0'){
                        char* tempStr = (char*)malloc(sizeof(char)*IDENTIFIERSIZE);
                        while(strCircuit[k]!=' ' && strCircuit[k]!='\0'){/* get the input and output identifiers until the whitespace or null(end of str) */
                              tempStr[letterCounter]=strCircuit[k];
                              letterCounter++;
                              k++;
                        }
                        if(flag==0){/* take the output identifier */
                              for(i=0;i<strlen(tempStr);i++)
                                    gates[gateCounter-1].identifier[i]=tempStr[i];/* fill the gate struct of identifier */
                              flag=1;
                              k++;
                              letterCounter=0;
                        }
                        else if(flag==1){/* take the first input identifiers */
                              for(i=0;i<strlen(tempStr);i++)
                                    gates[gateCounter-1].inp1[i]=tempStr[i];/* fill the gate struct of first input */
                              flag=2;
                              k++;
                              letterCounter=0;
                        }
                        else if(flag==2){/* take the second input identifiers */
                              for(i=0;i<strlen(tempStr);i++)
                                    gates[gateCounter-1].inp2[i]=tempStr[i];/* fill the gate struct of second input */
                              flag=0;
                              k++;
                              letterCounter=0;
                        }
                        if(strCircuit[k]=='\n'){
                              break;
                        }
                  }
                  gates[gateCounter-1].inp1_link=NULL;
                  gates[gateCounter-1].inp2_link=NULL;
                  gates=(struct gate*)realloc(gates,sizeof(struct gate)*(++gateCounter));/* and, reallocate one more gate structure */
                  k=0,letterCounter=0;/* reset the values */           
            }
            else if(strCircuit[k]==NOT){
                  strCircuit+=4;/* increment the string pointer to number of letters "NOT" word */
                  gates[gateCounter-1].type=4;/* assume that AND gate's type is 4 */
                  while(strCircuit[k]!='\0'){
                        char* tempStr = (char*)malloc(sizeof(char)*IDENTIFIERSIZE);
                        while(strCircuit[k]!=' ' && strCircuit[k]!='\0'){/* get the input and output identifiers until the whitespace or null(end of str) */
                              tempStr[letterCounter]=strCircuit[k];
                              letterCounter++;
                              k++;
                        }
                        if(flag==0){/* take the output identifier */
                              for(i=0;i<strlen(tempStr);i++)
                                    gates[gateCounter-1].identifier[i]=tempStr[i];/* fill the gate struct of identifier */
                              flag=1;
                              k++;
                              letterCounter=0;
                        }
                        else if(flag==1){/* take the first input identifiers */
                              for(i=0;i<strlen(tempStr);i++)
                                    gates[gateCounter-1].inp1[i]=tempStr[i];/* fill the gate struct of input */
                              flag=0;
                              k++;
                              letterCounter=0;
                        }
                        if(strCircuit[k]=='\n'){
                              break;
                        }
                  }
                  gates[gateCounter-1].inp1_link=NULL;
                  gates[gateCounter-1].inp2_link=NULL;
                  gates=(struct gate*)realloc(gates,sizeof(struct gate)*(++gateCounter));/* and, reallocate one more gate structure */
                  k=0,letterCounter=0;/* reset the values */
            }
            else if(strCircuit[k]==FLIPFLOP){
                  strCircuit+=9;
                  gates[gateCounter-1].type=5;
                  while(strCircuit[k]!='\0'){
                        char* tempStr = (char*)malloc(sizeof(char)*IDENTIFIERSIZE);
                        while(strCircuit[k]!=' ' && strCircuit[k]!='\0'){/* get the input identifiers until the whitespace or null(end of str) */
                              tempStr[letterCounter]=strCircuit[k];
                              letterCounter++;
                              k++;
                        }
                        if(flag==0){/* take the output identifier */
                              for(i=0;i<strlen(tempStr);i++)
                                    gates[gateCounter-1].identifier[i]=tempStr[i];/* fill the gate struct of identifier */
                              flag=1;
                              k++;
                              letterCounter=0;
                        }
                        else if(flag==1){/* take the first input identifiers */
                              for(i=0;i<strlen(tempStr);i++)
                                    gates[gateCounter-1].inp1[i]=tempStr[i];/* fill the gate struct of input */
                              flag=0;
                              k++;
                              letterCounter=0;
                        }
                        if(strCircuit[k]=='\n'){
                              break;
                        }
                  }
                  gates[gateCounter-1].former=0;/* and set 0 the former_out at the initializing */ 
                  gates[gateCounter-1].inp1_link=NULL;
                  gates[gateCounter-1].inp2_link=NULL;
                  gates=(struct gate*)realloc(gates,sizeof(struct gate)*(++gateCounter));
                  k=0,letterCounter=0;/* reset the values */
            }
      }
      for(k=inputCounter;k<gateCounter-1;k++){
            if(gates[k].type==2/* AND */ || gates[k].type==3/* OR */){
                  for(i=0;i<gateCounter-1;i++){
                        if(strcmp(gates[i].identifier,gates[k].inp1)==0){/* search and link the first input of gate */
                              gates[k].inp1_link=&gates[i];
                        }
                  }
                  for(i=0;i<gateCounter-1;i++){
                        if(strcmp(gates[i].identifier,gates[k].inp2)==0){/* search and link the second input of gate */
                              gates[k].inp2_link=&gates[i];
                        }
                  }
            }
            else if(gates[k].type==4 /* NOT */){  
                  for(i=0;i<gateCounter-1;i++){
                        if(strcmp(gates[i].identifier,gates[k].inp1)==0){/* search and link the first input of gate */
                              gates[k].inp1_link=&gates[i];
                        }
                  }
            }
            else if(gates[k].type==5/* FLIPFLOP */){  
                  for(i=0;i<gateCounter-1;i++){
                        if(strcmp(gates[i].identifier,gates[k].inp1)==0){/* search and link the first input of gate */
                              gates[k].inp1_link=&gates[i];
                        }
                  }
            }
      }
      int arr[inputCounter];/* initialize the array which holds the inputs each row */
      while(fgets(strInput,1024,fin2)!=NULL){/* input.txt */
            i=0,counter=0;
            while(strInput[i]!='\n'){
                  if(strInput[i]=='1' || strInput[i]=='0'){
                        sscanf(&strInput[i],"%d",&arr[counter]);/* take the 0 and 1 numbers from file */
                        counter++;
                  }
                  i++;
            }
            for(i=0;i<inputCounter;i++){
                  gates[i].value=arr[i];/* fill the INPUT gate's values from arr variable */
            }
            for(i=inputCounter;i<gateCounter-1;i++){
                  if(gates[i].type==2){/* AND */
                        gates[i].input1=gates[i].inp1_link->value;/* initialize the first input of AND gate */
                        gates[i].input2=gates[i].inp2_link->value;/* initialize the second input of AND gate */
                        gates[i].value=and(gates[i].input1,gates[i].input2);/* initialize the value of AND gate */
                  }
                  else if(gates[i].type==3){/* OR */
                        gates[i].input1=gates[i].inp1_link->value;/* initialize the first input of OR gate */
                        gates[i].input2=gates[i].inp2_link->value;/* initialize the second input of OR gate */
                        gates[i].value=or(gates[i].input1,gates[i].input2);/* initialize the value of OR gate */
                  }
                  else if(gates[i].type==4){/* NOT */
                        gates[i].input1=gates[i].inp1_link->value;/* initialize the input of NOT gate */
                        gates[i].value=not(gates[i].input1);/* initialize the value of NOT gate */
                  }
                  else if(gates[i].type==5){/* FLIPFLOP */
                        gates[i].input1=gates[i].inp1_link->value;/* initialize the input of FLIPFLOP gate */
                        gates[i].input2=gates[i].former;/* initialize the formet_out of FLIPFLOP gate */
                        gates[i].value=flipflop(gates[i].input1,gates[i].input2);/* initialize the value of FLIPFLOP gate */
                        gates[i].former=gates[i].value;/* update the former_out value */
                  }
            }
            fprintf(fout,"%d\n",gates[i-1].value);/* print the output of circuit of the output.txt file */
      }
      fclose(fin1);
      fclose(fin2);
      fclose(fout);
      return 0;
}
/* logical and operator */
int and(int x, int y){
      if(x==1 && y==1)
            return 1;
      else if((x==0 && y==0) || (x==0 && y==1) || (x==1 && y==0))
            return 0;
}
/* logical or operator */
int or(int x, int y){
      if(x==0 && y==0)
            return 0;
      else if((x==1 && y==1) || (x==0 && y==1) || (x==1 && y==0))
            return 1;
}
/* logical flipflop operator */
int flipflop(int x, int y){
      if((x==0 && y==0) || (x==1 && y==1))
            return 0;
      else if((x==1 && y==0) || (x==0 && y==1))
            return 1;
}
/* logical not operator */
int not(int x){
      if(x==0)
            return 1;
      else
            return 0;
}