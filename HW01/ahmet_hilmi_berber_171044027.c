/*  Ahmet Hilmi Berber  */
/*		171044027		*/ 
/*	   CSE102 HW01		*/

#include<stdio.h>

#define number_of_points 10/*i have defined a macro which you can easily try coordinates in different numbers*/
#define small_number 0.000000000001/*i have defined a small value with macro to minimize the error of the occurrence of 0 in the denominator*/

int main(){
	double avg_class1_x,avg_class1_y;/*the variables avg_class1_x and avg_class1_y are the coordinates of the midpoint of class1*/
	double avg_class2_x,avg_class2_y;/*the variables avg_class2_x and avg_class2_y are the coordinates of the midpoint of class2*/
	double mid_x,mid_y,slope_of_line,user_x,user_y;/*the variables mid_x and mid_y are the coordinates of the midpoint of class1 and class2*/
	double sum_class1_x=0,sum_class1_y=0,sum_class2_x=0,sum_class2_y=0,avg_x,avg_y,x,y;
	int i;
	/*calculating class1's middle point's coordinates*/
	for(i=0;i<number_of_points;i++){
		scanf("%lf%lf",&x,&y);
		sum_class1_x+=x;
		sum_class1_y+=y;
	} 
	avg_class1_x=sum_class1_x/number_of_points;
	avg_class1_y=sum_class1_y/number_of_points;
	/*calculating class2's middle point's coordinates*/
	for(i=0;i<number_of_points;i++){
		scanf("%lf%lf",&x,&y);
		sum_class2_x+=x;
		sum_class2_y+=y;
	}
	avg_class2_x=sum_class2_x/number_of_points;
	avg_class2_y=sum_class2_y/number_of_points;
	/*calculating middle point's coordinates..*/
	mid_x=(avg_class1_x+avg_class2_x)/2;
	mid_y=(avg_class1_y+avg_class2_y)/2;
	/*calculating slope of line*/
	if(avg_class2_y-avg_class1_y==0)/*undefine status*/
		slope_of_line=(-1)/small_number;
	else if(avg_class2_x-avg_class1_x==0)/*0 status*/
		slope_of_line=0;
	else/*normal value status*/
		slope_of_line=(-1)/((avg_class2_y-avg_class1_y)/(avg_class2_x-avg_class1_x));
	printf("%lf\n",slope_of_line);
	/*determining which side the user enters*/
	/*here i used the inequality graphs in the coordinate plane to check if the user entered the point on the same side as the class1 or class2*/
	while(scanf("%lf%lf",&user_x,&user_y)==2)
		if(user_y>(slope_of_line)*(user_x-mid_x)+mid_y)
			if(avg_class1_y>(slope_of_line)*(avg_class1_x-mid_x)+mid_y)/*If the point is on the same side as class1, I have printed "class1". if not, I printed "class2"*/
				printf("class1\n");	
			else
				printf("class2\n");
		else/*else, I have printed "class1". if not, I printed "class2"*/
			if(avg_class1_y<(slope_of_line)*(avg_class1_x-mid_x)+mid_y)
				printf("class1\n");
			else
				printf("class2\n");
	return 0;
}
