#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void change( int **);
int main()
{
//	int len;
//	char * name, buffer[1000];
//	scanf("%999s" , buffer);
//	len = strlen(buffer);
////	printf("%d" , len);
//	name = malloc ( sizeof(char) * (len+1));
//	for ( int i=0;i< len+1;i++)
//	{
//		printf("%c", buffer[i]); 
//	}
//
//	memcpy(name , buffer, sizeof(char) * (len+1));
//	printf("%s" , name);
	int **matrix;
	
	int i = 0;
	for ( int r=0;r<4;r++)
	{
		for ( int c=0;c<4;c++)
		{
			matrix[r][c] = i;
			i++;
		}
	}

	printf("Before change:\n");
	for ( int r= 0 ;r<4;r++)
	{
		for ( int c=0;c<4;c++)
		{
			printf("%d ", matrix[r][c]);
		}
		printf("\n");
	}

	printf("After change:");

	int (*poit_arr)[] 
	change( matrix);
	for ( int r= 0 ;r<4;r++)
	{
		for ( int c=0;c<4;c++)
		{
			printf("%d ", matrix[r][c]);
		}
		printf("\n");
	}

	return 0;
}

void change( int ** matrix)
{
	int i = 10;
	for ( int r=0;r< 4;r++)
	{
		for ( int c=0;c<4;c++)
		{
			matrix[r][c] = i;
			i++;
		}
	}
}
