/*  Ahmet Hilmi Berber  */
/*      171044027       */ 
/*     CSE102 HW06      */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 105
#define START 0

void trim(char* str);
double recursive(char* string, char* tempStr, double cost, double numberOfParts);

int main(){
      char* object=(char*)malloc(sizeof(char)*SIZE);
      char* tempStr=(char*)malloc(sizeof(char)*SIZE);
      double startCost=0,eachCost,cost=0,parts=1;
      printf("Name the object:");
      scanf("%[^\n]s",object);
      tempStr=NULL;
      trim(object);
      cost = recursive(object,tempStr,startCost,parts);
      printf("total cost of %s is %.2f\n",object,cost);
      free(object);
      free(tempStr);
      return 0;
}
/* this function controls whitespaces and trims the string */
void trim(char* str){
	int i,j=0;
	for(i=0;str[i]!='\0';i++){/* if there are unnecessary whitespaces, delete them */
            if(str[i]==' '){/* unnecessary means more than 1 whitespaces between the values */  
                  if(str[i+1]!=' ' || str[i+1]=='\0'){
                        str[j++]=str[i];
                        i++;
                  }
            }
		if(str[i]!=' '){
			str[j++]=str[i];
		}
	}
      if(str[0]==' ' && str[j-2]==' '){/* if there are whitespaces at both start and end, delete them */
            str[j-2]='\0';
            char* temp=(char*)malloc(sizeof(char)*SIZE);
            strcpy(temp,str+1);
            strcpy(str,temp);
      }
      else if(str[0]==' '){/* if there is a whitespace only strat, delete it */
            char* temp=(char*)malloc(sizeof(char)*SIZE);
            strcpy(temp,str+1);
            strcpy(str,temp);
            str[strlen(str)-2]='\0';
      }
      else if(str[j-2]==' '){/* if there is a whitespace only end, delete it */
            str[j-2]='\0';
      }
      else{/* if there is no whitespaces at both start and end, put the NULL at the end of the string */
            str[j]='\0';      
      }
}

double recursive(char* string, char* tempStr, double cost, double numberOfParts){
      char* str=(char*)malloc(sizeof(char)*SIZE);
      char* numStr=(char*)malloc(sizeof(char)*SIZE);
      char* branch=(char*)malloc(sizeof(char)*SIZE);
      int i,defineFlag=0,branchStrCounter=0,numStrCounter=0;
      double eachCost,realNum;
      if(tempStr==NULL)
            printf("Define %s?:\n",string);
      else
            printf("Define %s in %s?:\n",string,tempStr);
      tempStr=string;
      scanf(" %[^\n]s",str);
      trim(str);/* string trimmed */
      for(i=0;str[i]!='\0';i++){/* if there is a 'char' in the string, this means user will enter the cost of component */
            if((str[i]<'0' || str[i]>'9') && str[i]!='.'){
                  defineFlag=1;
                  break;
            }
      }
      if(defineFlag==1){/* branching situation */
            i=0;
            while(str[i]!='\0'){
                  while(str[i]!=' '){/* get the number until whitespace  */
                        numStr[numStrCounter]=str[i];
                        numStrCounter++;
                        if(str[i]=='\0')
                              break;
                        i++;/* and Increment index */
                  }
                  i++;/* after whitespace increment */
                  while(str[i]!=' '){/* get the string until whitespace */
                        branch[branchStrCounter]=str[i];
                        branchStrCounter++;
                        if(str[i]=='\0')
                              break;
                        i++;/* and Increment index */
                  }
                  sscanf(numStr,"%lf",&realNum);/* cast the number (which is string) to double */
                  cost=recursive(branch,tempStr,cost,realNum);
                  memset(branch,0,SIZE);/* reset the values */
                  memset(numStr,0,SIZE);
                  numStrCounter=0,branchStrCounter=0;
                  if(str[i]!='\0')
                        i++;/* after whitespace increment */
            }
            free(numStr);
            free(branch);
            free(str);
            return cost*numberOfParts;/* return the total cost */
      }
      else{/* not branching, user enters the cost of component */
            sscanf(str,"%lf",&eachCost);
            cost+=eachCost*numberOfParts;/* and increment the cost */
      }
}                                       