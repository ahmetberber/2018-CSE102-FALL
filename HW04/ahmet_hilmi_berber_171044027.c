/*  Ahmet Hilmi Berber  */
/*      171044027       */ 
/*     CSE102 HW04      */

#include<stdio.h>
#include<math.h>
#include<string.h>

#define PLUS 1
#define MINUS 2
#define MAXSIZEPOLYNOMIAL 1000
#define MAXSIZEVALUES 100

void search(char* c, char* string, int* newString, int* size);
void sort(int *array, int size);
void removespaces(char* string, int* size);

int main(){
	int i,j,plusCounter,minusCounter,counterMonomial,counterValues=0,counterPolynomial=0,plus[MAXSIZEVALUES],minus[MAXSIZEVALUES],
	monomialIndexes[MAXSIZEVALUES],countM=0,lower=0,upper=0,flagSign=0,firstCounter,secondCounter,thirdCounter,flagUnknown=0,flag=0;
	double values[MAXSIZEVALUES],value,result,firstI,secondI,thirdI;
	char c,polynomial[MAXSIZEPOLYNOMIAL],firstC[MAXSIZEVALUES],secondC[MAXSIZEVALUES],thirdC[MAXSIZEVALUES];
	FILE *fin1=fopen("values.txt","r");
	FILE *fin2=fopen("polynomial.txt","r");
	FILE *fout=fopen("evaluations.txt","w");
	while(fscanf(fin1,"%lf",&value)!=EOF){/* Reading values from values.txt file */
		values[counterValues]=value;
		counterValues++;
	}
	while(fscanf(fin2,"%c",&c)!=EOF){/* Reading polynomial from polynomial.txt file */
		polynomial[counterPolynomial]=c;
		counterPolynomial++;
	}
	/* If there is a space in the polynomial, remove all of them with removespaces function */
	removespaces(polynomial,&counterPolynomial);
	/* I searched and found the minus and plus signs because I separated the polynomial to monomials */
	search("+",polynomial,plus,&plusCounter);
	search("-",polynomial,minus,&minusCounter);
	for(i=0;i<plusCounter;i++){/* and I assigned the minus and plus's indexes to the monomialIndexes variable */
		monomialIndexes[i]=plus[i];
	}
	for(j=plusCounter;j<plusCounter+minusCounter;j++){
		monomialIndexes[j]=minus[j-plusCounter];
	}
	/* I controlled the first index of polynomial array because is not put at the first index of the polynomial */
	if(polynomial[0]=='-'){/* If there is a minus sign at the first index of the polynomial, I didn't add the 0 to 
	the monomialIndexes array because the search function had already checked the minus sign */
		counterMonomial=plusCounter+minusCounter;
	}
	else{/* If there is not a minus sign at the first index of the polynomial, this means there are plus sign at the beggining.
	so I added the 0 to the monomialIndexes array because the search function has not checked the plus sign */
		monomialIndexes[plusCounter+minusCounter]=0;
		counterMonomial=plusCounter+minusCounter+1;/* and I increase the number of monomials which equal to counterMonomial */
	}
	sort(monomialIndexes,counterMonomial);/* because I will check the polynomial to monomial by monomial, I sorted the monomial indexes */
	for(i=0;i<counterValues;i++){
		result=0;/* these variable keeps the result which we'll calculate the end of program */
		countM=0;/* these variable keeps the monomial which we remain */
		while(countM<counterMonomial){
			/* I reset these firstC,secondC,thirdC values which equals to the coefficient or power of unknown variable */
			memset(firstC,0,strlen(firstC));
			memset(secondC,0,strlen(secondC));
			memset(thirdC,0,strlen(thirdC));
			lower=monomialIndexes[countM];/* I assigned the lower value to the mononmial's first index */
			if(countM==counterMonomial-1){/* If we are at the last monomial, then last monomial's last index(upper) equals to the length of the polynomial */
				upper=counterPolynomial;
			}
			else{/* If not, last index(upper) equals to the next monomial's first index which equals to it's sign */
				upper=monomialIndexes[countM+1];
			}
			if(countM==0){/* If we are start of the polynomial */
				if(polynomial[lower]=='-'){/* and if there is a minus sign here, this means we are gonna to subtraction */
					flagSign=MINUS;
				}
				else{
					flagSign=PLUS;/* and if there is no minus sign here, this means we are gonna to addition */
				}
			}
			else{/* If we are not start of the polynomial */
				if(polynomial[lower]=='-'){/* and if there is a minus sign here, this means we are gonna to subtraction */
					flagSign=MINUS;
				}
				else if(polynomial[lower]=='+'){/* and if there is a plus sign here, this means we are gonna to addition */
					flagSign=PLUS;
				}
			}
			if(countM!=0 || flagSign!=PLUS){/* at the beginning of the polynomial, if there is no plus sign at there, then we must start
			the first index, if there is minus sign here, then we must start after the sign */
				lower++;
			}
			flag=0;
			if(polynomial[lower]!='x'){/* If there is a coefficient of unknown variable */
				firstCounter=0;
				while(lower+firstCounter!=upper && flag==0){
					if(polynomial[lower+firstCounter]!='x'){/* just coefficient, no unknown variable */
						flagUnknown=1;
					}
					else{
						flagUnknown=0;/* coefficient with unknown variable */
						flag=1;
					}
					firstCounter++;
				}
				
				if(flagUnknown==1){/* If there is no unknown variable, turn till the next sign(upper) and take the fixed number */
					firstCounter=0;
					while(lower+firstCounter!=upper){
						firstC[firstCounter]=polynomial[lower+firstCounter];
						firstCounter++;
					}
					sscanf(firstC,"%lf",&firstI);/* Fıxed number equals to firstI variable */
					/* If there is no unknown variable, then there is no power too and it equals to firstI */
					if(flagSign==PLUS){
						result+=firstI;
					}
					else if(flagSign==MINUS){
						result-=firstI;
					}
				}
				else if(flagUnknown==0){/* If there a is unknown variable here, turn till the unknown variable and take the coefficient */
					firstCounter=0;
					while(polynomial[lower+firstCounter]!='x'){
						firstC[firstCounter]=polynomial[lower+firstCounter];
						firstCounter++;
					}
					sscanf(firstC,"%lf",&firstI);/* Coefficient equals to firstI variable */
					/* There is a unknown variable after the coefficient */
					secondCounter=1;
					if(polynomial[lower+firstCounter+secondCounter]=='^'){/* and If unknown variable has a power, turn till the next sign(upper) and take the power */
						while(lower+firstCounter+secondCounter+1!=upper){
							secondC[secondCounter-1]=polynomial[lower+firstCounter+secondCounter+1];
							secondCounter++;
						}
						sscanf(secondC,"%lf",&secondI);/* Power equals to secondI variable */
					}
					else{/* If there is no power, it equals to 1 */
						secondI=1;
					}
					if(flagSign==PLUS){
						result+=firstI*pow(values[i],secondI);
					}
					else if(flagSign==MINUS){
						result-=firstI*pow(values[i],secondI);
					}
				}
			}
			else if(polynomial[lower]=='x'){/* If there is no coefficient of unknown variable */
				thirdCounter=1;
				if(polynomial[lower+thirdCounter]=='^'){/* If unknown variable has a power, turn till the next sign(upper) and take the power */
					while(lower+thirdCounter+1!=upper){
						thirdC[thirdCounter-1]=polynomial[lower+thirdCounter+1];
						thirdCounter++;
					}
					sscanf(thirdC,"%lf",&thirdI);/* Power equals to thirdI variable */
				}
				else{/* If there is no power, it equals to 1 */
					thirdI=1;
				}
				if(flagSign==PLUS){
					result+=pow(values[i],thirdI);
				}
				else if(flagSign==MINUS){
					result-=pow(values[i],thirdI);
				}
			}
			countM++;
		}
		fprintf(fout,"%.2f\n",result);
	}
	fclose(fin1);
	fclose(fin2);
	fclose(fout);
      return 0;
}
/* This function searches the given input(char* c) and find the location of input at the given string */
void search(char* c, char* string, int* newString, int* size){ 
	size_t s=strlen(string); 
	int counter=0,i,j;
	for(i=0;i<s;i++){
		if(string[i]==c[0]){
			newString[counter]=i;
			counter++;
		}
	}
	*size=counter; 
}
/* This function sorts the numbers at the given array in ascending order */
void sort(int *array, int size){
	int i,j,swap;
	for(i=0;i<size;i++){
		for(j=i+1;j<size;j++){
			if (array[i]>array[j]){
				swap=array[i];
				array[i]=array[j];
				array[j]=swap;
			}
		}
	}
}
/* This function deletes all the spaces of the given string */
void removespaces(char* string, int* size){
	int i,j=0;
	for(i=0;string[i]!='\0';i++){
		if(string[i]!=' '){
			string[j++]=string[i];
		}
	}
	string[j]='\0';
	*size=strlen(string);
}