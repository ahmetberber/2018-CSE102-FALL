/*  Ahmet Hilmi Berber  */
/*      171044027       */ 
/*     CSE102 HW03      */

#include<stdio.h>
#include<string.h>

#define MAX_WORD_LENGTH 10
#define MAX_LENGTH_EACH_ROW 250
#define MAX_LENGTH_NUMBER_OF_ROW 100
#define FIRST_INDEX 0
#define SUCCESS_HORIZONTAL 1
#define SUCCESS_VERTICAL 2

int findSmallestNumber(int arr[], int size);
int search(char* word,int size_of_word, int* vertical_coordinate, int* horizontal_coordinate);

int main(){
      FILE* fin = fopen("input1.txt","r");
      FILE* fout = fopen("output.txt","w");
      char word[MAX_WORD_LENGTH];
      int size_of_word,vertical_coordinate,horizontal_coordinate;
      while(fscanf(fin,"%s",word)!=EOF){/* I read the words one by one from "input1.txt" file */
            size_of_word=strlen(word);
            if(search(word,size_of_word,&vertical_coordinate,&horizontal_coordinate)==SUCCESS_HORIZONTAL)
                  fprintf(fout,"%s (%d,%d) Horizontal\n",word,vertical_coordinate,horizontal_coordinate);
            else if(search(word,size_of_word,&vertical_coordinate,&horizontal_coordinate)==SUCCESS_VERTICAL)
                  fprintf(fout,"%s (%d,%d) Vertical\n",word,vertical_coordinate,horizontal_coordinate);

      }
      fclose(fin);
      fclose(fout);
      return 0;
}
/* Function that finds the minimum value in the array */
int findSmallestNumber(int arr[], int size){
      int min_number=arr[FIRST_INDEX],i;
      for(i=1;i<size;i++)
            if(arr[i]<min_number)
                  min_number=arr[i];
      return min_number;
}
/* Function that finds the location and orientation of the word in the text file */
int search(char* word,int size_of_word, int* vertical_coordinate, int* horizontal_coordinate){
      FILE* fin = fopen("input2.txt","r");
      char row[MAX_LENGTH_EACH_ROW],whole_text_file[MAX_LENGTH_NUMBER_OF_ROW][MAX_LENGTH_EACH_ROW];
      int row_size[MAX_LENGTH_EACH_ROW],i,j,smallest_row,number_of_rows=0,flag=0,letter_counter=0,size=0;
      /* READ TEXT FILE */
      while(fscanf(fin,"%s",row)!=EOF){/* I read the whole text row by row from "input2.txt" file and assigned to the "whole_text_file" varibale */
            row_size[number_of_rows]=strlen(row);/* I hold the all row's size's on the "row_size" variable */
            for(i=0;i<row_size[number_of_rows];i++)
                  whole_text_file[number_of_rows][i]=row[i];
            number_of_rows++;/* and This is variable which holds number of rows */
      }
      /* HORIZONTAL CHECK */
      for(i=0;i<number_of_rows;i++){
            for(j=0;j<row_size[i];j++){
                  if(whole_text_file[i][j]==word[flag]){/* I checked the character in the location and the first character of the word */
                        flag=j;
                        while(whole_text_file[i][flag]==word[letter_counter] && size!=size_of_word){/* If it is the same, I checked the length of the word horizontally */
                              size++;
                              flag++;
                              letter_counter++;
                        }
                        if(size==size_of_word){/* If the length of the word is equal to the controlled length, I've return the true value which "SUCCESS_HORIZONTAL" */
                              *vertical_coordinate=j+1; 
                              *horizontal_coordinate=i+1; 
                              return SUCCESS_HORIZONTAL;
                        }
                        else{
                              letter_counter=0,size=0,flag=0;/* If it is not true, I reseted the values and kept checking */ 
                        }
                  }
            }
      }
      /* VERTICAL CHECK */
      size=0,letter_counter=0,flag=0;/* I reset the initial values of these variables */
      smallest_row = findSmallestNumber(row_size,number_of_rows); /* I found the smallest row of the text because If we check words vertically, we must reference the smallest row in the text */
      for(i=0;i<smallest_row;i++){
            for(j=0;j<number_of_rows;j++){
                  if(whole_text_file[j][i]==word[flag]){/* I checked the character in the location and the first character of the word */
                        flag=j; 
                        while(whole_text_file[flag][i]==word[letter_counter] && size!=size_of_word){/* If it is the same, I checked the length of the word vertically */
                              size++;
                              flag++;
                              letter_counter++;
                        }
                        if(size==size_of_word){/* If the length of the word is equal to the controlled length, I've return the true value which "SUCCESS_VERTICAL" */
                              *vertical_coordinate=j+1; 
                              *horizontal_coordinate=i+1; 
                              return SUCCESS_VERTICAL;
                        }
                        else{
                              letter_counter=0,size=0,flag=0;/* If it is not true, I reseted the values and kept checking */
                        }
                  }
            }
      }
      fclose(fin);
}