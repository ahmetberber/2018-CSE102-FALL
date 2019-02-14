/*  Ahmet Hilmi Berber  */
/*      171044027       */ 
/*     CSE102 HW02      */

#include<stdio.h>

double p1=0.5;/* These are global variables which you can easily change and test */
double p2=20;

int main(){
	/* Creating the file pointers.. */
	FILE* fin=fopen("input.txt","r"); /* I opened the input and output files here */
	FILE* fout=fopen("output.txt","w");
	/* Initializing the variables.. */
	double number,chunks[100][100],chunk_averages[100],whole_numbers[10000],temp[10000],avg=0,next_avg=0,sum=0,temp_avg,temp_size;
	int i,j,k,counter=0,chunk_counter=0,number_counter_chunk=1,size_of_chunk[100];
	/* Getting values from file.. */
	while(fscanf(fin,"%lf",&number)!=EOF){
		whole_numbers[counter]=number;/* Here I put all the numbers in the file into the array called "whole_numbers" */
		counter++;
	}
	/* Determine Chunks.. */
	chunks[0][0]=whole_numbers[0];/* The first number in the sequence belongs to the first chunk */
	for(i=0;i<counter;i++){
		sum+=whole_numbers[i];
		avg=sum/number_counter_chunk;
		next_avg=(sum+whole_numbers[i+1])/(number_counter_chunk+1);
		if(!(next_avg>avg*(1+p1) || next_avg<avg*(1-p1) || avg>whole_numbers[i+1]*p2 || avg<whole_numbers[i+1]/p2)){
			chunks[chunk_counter][number_counter_chunk]=whole_numbers[i+1];/* If the next number belongs to the chunk, I assigned it */
			number_counter_chunk++;/* and I increased that variable which defines to how many numbers have each chunk */
		}
		else{
			chunk_averages[chunk_counter]=avg;/* If the next number not belongs to the chunk, I terminated the chunk */
			size_of_chunk[chunk_counter]=number_counter_chunk;/* and I determined the size of each chunk and I assigned this values at "size_of_chunk" variable which is one dimensional array */
			chunk_counter++; /* and I increased that variable which determines how many chunks are in the file */
			if (chunk_counter == 100)/* I checked chunk size because maximum size of a chunk is 100 */
				break;
			avg=0,next_avg=0,number_counter_chunk=1,sum=0;/* and I reset all the variables */
			chunks[chunk_counter][number_counter_chunk-1]=whole_numbers[i+1];/* and initialized new chunk's first number */
		}
	}      
	/* Sorting chunks.. */
       for(i=0;i<chunk_counter;i++){
              for(j=i+1;j<chunk_counter;j++){
                     if(chunk_averages[i]>chunk_averages[j]){
							//////////////////////////////
                            temp_avg=chunk_averages[i];
                            chunk_averages[i]=chunk_averages[j];/* I sorted the average of each chunk*/
                            chunk_averages[j]=temp_avg;
							//////////////////////////////
                            for(k=0;k<size_of_chunk[i];k++)
                                   temp[k]=chunks[i][k];
                            for(k=0;k<size_of_chunk[j];k++)
                                   chunks[i][k]=chunks[j][k];/* I sorted each chunk one by one */
                            for(k=0;k<size_of_chunk[i];k++)
                                   chunks[j][k]=temp[k];
							/////////////////////////////
                            temp_size=size_of_chunk[i];
                            size_of_chunk[i]=size_of_chunk[j];/* I sorted the size of each chunk */
                            size_of_chunk[j]=temp_size;
                     }
              }
       }
       /* Printing chunks to output file.. */
	for(i=0;i<chunk_counter;i++){
		for(j=0;j<size_of_chunk[i];j++)
			fprintf(fout,"%lf ",chunks[i][j]);/* I printed sorted chunks in output file in ascending order */
		fprintf(fout,"\n");
	}
	fclose(fin);/* I closed the input and output files here */
	fclose(fout);
	return 0;	
}