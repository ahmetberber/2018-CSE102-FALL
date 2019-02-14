/*  Ahmet Hilmi Berber  */
/*      171044027       */
/*     CSE102 HW08      */

#include <stdio.h>

#define SIZE 512 /* you can change the array size if you want (array[SIZE][SIZE]) */
#define WATER -1 /* assume that water definition is -1 */
#define LAND -2  /* assume that land definition is -2 */

int arr[SIZE+2][SIZE+2];/* i incremented the dimensions because the borders have to also be water */

void mark(int y, int x, int islandCounter);
void findCoordinates(int island_no, FILE* fp);

int main(){
      FILE* fin = fopen("input.txt","r");
      FILE* fout = fopen("output.txt","w");
      int i, j, waterLevel, number, islandCounter=0, row=1, column=1, allIsland=0,allWater=0;
      for(i=0;i<SIZE+2;i++)
            for(j=0;j<SIZE+2;j++)
                  arr[i][j]=WATER;/* i marked whole array by water which is -1 */
      fscanf(fin,"%d",&waterLevel);
      while(fscanf(fin,"%d",&number)!=EOF){
            if(number>waterLevel){/* here i marked the land parts which is -2 */
                  arr[row][column]=LAND;
                  column++;
                  if(column==SIZE+1){
                        row++;
                        column=1;
                  }
                  allWater=1;
            }
            else{/* i have already marked the whole array to water, so not necessary to mark the water parts */
                  column++;
                  if(column==SIZE+1){
                        row++;
                        column=1;
                  }
                  allIsland=1;
            }
      }
      if(allIsland==0)/* if allIsland variable is 0, this means our array equals to 1 island_no */
            fprintf(fout,"%d\n%d %d\n",islandCounter+1,islandCounter,islandCounter);
      else if(allWater==0)/* if allWater variable is 0, this means there is no island_no in our array */
            fprintf(fout,"%d\n",islandCounter);
      else{
            for(i=0;i<SIZE+2;i++)
                  for(j=0;j<SIZE+2;j++)
                        if(arr[i][j]==LAND)
                              mark(i,j,++islandCounter);/* here i called the mark function which takes the land then determines and numarates the islands */ 
            fprintf(fout,"%d\n",islandCounter);/* i printed the number of islands to the output.txt file */
            for(i=1;i<=islandCounter;i++)
                  findCoordinates(i,fout);/* here i called the findCoordinates function to "number of islands" times which searches the island number and prints the coordinates of current island to the output.txt file */ 
      }
      fclose(fin);
      fclose(fout);
      return 0;
}

void mark(int y, int x, int islandCounter){
      if(arr[y][x+1]==LAND && arr[y][x+1]!=islandCounter){/* right check */   
            arr[y][x]=islandCounter;
            mark(y,x+1,islandCounter);
      }
      if(arr[y+1][x]==LAND && arr[y+1][x]!=islandCounter){/* down check */
            arr[y][x]=islandCounter;
            mark(y+1,x,islandCounter);
      }
      if(arr[y][x-1]==LAND && arr[y][x-1]!=islandCounter){/* left check */
            arr[y][x]=islandCounter;
            mark(y,x-1,islandCounter);
      }
      if(arr[y-1][x]==LAND && arr[y-1][x]!=islandCounter){/* up check */
            arr[y][x]=islandCounter;
            mark(y-1,x,islandCounter);
      }
      if(arr[y][x]!=islandCounter)/* if current land has not numarated, then numarate it */
            arr[y][x]=islandCounter;
}

void findCoordinates(int island_no, FILE* fp){
      int i,j;
      for(i=0;i<SIZE+2;i++)
            for(j=0;j<SIZE+2;j++)
                  if(arr[i][j]==island_no){
                        fprintf(fp,"%d %d\n",i-1,j-1);/* i printed the island's coordinates */
                        i=SIZE+2;j=SIZE+2;
                  }
}