/*  Ahmet Hilmi Berber  */
/*      171044027       */ 
/*     CSE102 HW05      */

#include<stdio.h>
#include<string.h>

#define HYPEN "-"
#define WHITESPACE ' '
#define OPENPARENTHESES '('
#define CLOSEPARENTHESES ')'
#define COMMA ','
#define STRINGLENGTH 250
#define NODELENGTH 10
#define START 0
#define NEXT 1

void printTree(char text[], char node[], FILE* fout, int hypenCounter, int charCounter, char temp, int flag);
void deleteSpacesFromStart(char* str);

int main(){
      /* openning the files */
      FILE* fin = fopen("input.txt","r");
      FILE* fout = fopen("output.txt","w");
      int size=0, hypen=0, counter=0, i, flag=0;
      char node[NODELENGTH], wholeText[STRINGLENGTH], temp, c;
      /* reading from file and assigning to the "wholeText" string */
      while(fscanf(fin,"%c",&c)!=EOF){
            wholeText[size]=c;
            size++;
      }
      wholeText[size]='\0';/* and putting the NULL end of the string */
      if(wholeText[size-1]!=WHITESPACE){/* if there is not whitespace at the end of the string */
            for(i=size-1;i>=0;i--){
                  if(wholeText[i]!=CLOSEPARENTHESES){/* i put the comma after the last node. because according to my algorithm, when the program checking the string character 
                  by character, each node creating after the comma and there is no comma after the last node! then i think i have to put the comma after the last node */
                        wholeText[i+1]=COMMA;
                        break;
                  }
            }
      }
      else{/* if there is a whitespace at the end of the string, there must be many spaces at there */
            for(i=size-1;i>=0;i--){ 
                  if(wholeText[i]!=CLOSEPARENTHESES && wholeText[i]!=WHITESPACE){/* same is here. but at the end of the string, closeparentheses and whitespaces
                  have to checked both. and i have to delete the spaces */
                        wholeText[i+1]=COMMA;/* i put the comma after the last node */
                        wholeText[i+2]='\0';/* and i put the NULL after the comma instead of delete all the whitespaces at the end of the string. 
                        because checking anything after the last comma is not neccessary */
                        break;
                  }
            }
      }
      if(wholeText[START]==WHITESPACE){/* if there is whitespace at the beginning of the string */
            deleteSpacesFromStart(wholeText);/* i deleted the whitespaces till the tree begins */ 
      }
      printTree(wholeText,node,fout,hypen,counter,temp,flag);
      fclose(fin);
      fclose(fout);
      return 0;
}

void printTree(char text[], char node[], FILE* fout, int hypenCounter, int charCounter, char temp, int flag){
      int i=0;
      if(text[START]=='\0'){
            return;
      }
      else{
            if(text[START]==OPENPARENTHESES){/* if there is a openparentheses here, i increment the hypenCounter */
                  if(temp==WHITESPACE){/* if there is whitespace before the openparentheses, i ignore it and reset the string */
                        memset(node,0,strlen(node));
                        charCounter=0;
                  }
                  hypenCounter++;
            }
            else if(text[START]==CLOSEPARENTHESES){/* if there is a openparentheses here, i decrement the hypenCounter */
                  hypenCounter--;
            }
            else if(text[START]==WHITESPACE){/* if there is a whitespace here, i assigned it to the node string */
                  node[charCounter]=text[START];
                  charCounter++;
            }
            else if(text[START]==COMMA){/* if there is a comma here, this means the node or node's element is over */
                  if(flag==1){/* if node is not empty */
                        if(temp==CLOSEPARENTHESES){/* if node is over(there is closeparentheses before the comma)*/
                              for(i=0;i<hypenCounter+1;i++){/* i printed 1 more hypen because the program already saw the closeparentheses and decrement the hypenCounter.*/ 
                                    fprintf(fout,HYPEN);
                              }
                        }
                        else{
                              for(i=0;i<hypenCounter;i++){/* if node's element is over */
                                    fprintf(fout,HYPEN);/* i printed the hypens */
                              }
                        }                        
                        for(i=0;i<charCounter;i++){/* i printed the actual node */
                              fprintf(fout,"%c",node[i]);
                        }
                        fprintf(fout,"\n");
                        charCounter=0,flag=0;/* and i reset the values */
                        memset(node,0,strlen(node));
                  }
                  else{/* if node is empty */
                        memset(node,0,strlen(node));/* i reset the values */
                        charCounter=0;
                  }
            }
            else{
                  flag=1;
                  node[charCounter]=text[START];/* if there is a node character, i assigned it to the node string */
                  charCounter++;
            }
            temp=text[START];/* i assigned to current character to the temp value for determine if node ends */
            printTree(&text[NEXT],node,fout,hypenCounter,charCounter,temp,flag);
      }
}
/* this function deletes the whitespaces at the beginning of the given string */
void deleteSpacesFromStart(char* str){
      int index=0,i;
      while(str[index]==WHITESPACE){
            index++;
      }
      if(index!=0){
            i=0;
            while(str[i+index]!='\0'){
                  str[i]=str[i+index];
                  i++;
            }
            str[i]='\0';
      }
}