/*
 ============================================================================
 Name        : testc.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
void operation(float *ptr_num , char *ptr_operation , const int size);

int main(void) {

	float arr_num[]={12,5,2,10,3};
	char arr_operation[SIZE]={'+','*','-','/'};
	operation(arr_num,arr_operation,SIZE);
	printf("the result = %f \n",arr_num[0]);
	printf("the result = %f \n",arr_num[1]);
	printf("the result = %f \n",arr_num[2]);
	printf("the result = %f \n",arr_num[3]);
	printf("the result = %f \n",arr_num[4]);
	printf("the result = %d \n",arr_operation[0]);
	return EXIT_SUCCESS;
}

void operation(float *ptr_num , char *ptr_operation , const int size)
{
	int i=0,x=0;
	int count=0;
	for(;i<size-count;i++)
	{
		if(ptr_operation[i]=='*' || ptr_operation[i]=='/')
		{
			switch(ptr_operation[i])
			{
			case '*':
				ptr_num[i]=ptr_num[i] * ptr_num[i+1];
				break;
			case '/':
				ptr_num[i]=ptr_num[i] / ptr_num[i+1];
				break;
			}
			count++;/*this count to count number of operation(* or /) */
			for(int j=i;j<size-count;j++)
			{
				ptr_num[j+1]=ptr_num[j+2];
				ptr_operation[j]=ptr_operation[j+1];

			}
			i--;/*to start from the same index of operation*/

		}

	}
	for(;x<size-count;x++)
	{

		switch(ptr_operation[x])
		{
		case '+':
			ptr_num[x] = ptr_num[x] + ptr_num[x+1];
			break;
		case '-':
			ptr_num[x] = ptr_num[x] - ptr_num[x+1];
			break;
		}
		count++;/*to add number of operation (+ or -)*/
		for(int j=x;j<size-count;j++)
		{
			ptr_num[j+1]=ptr_num[j+2];
			ptr_operation[j]=ptr_operation[j+1];

		}
		x--;/*to start from the same index of operation*/
	}

	//return ptr_num[0];
	for(int t=0;t<size;t++)
	{
		ptr_num[t+1]=0;
		ptr_operation[t]=0;
	}

}
