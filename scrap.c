//to reanalyze some concepts beforehand


#include <stdio.h>
#include <stdlib.h>


void divine( int array[][4])
{

	for ( int r = 0;r<3;r++)
	{
//		printf("%d ", array[r]);
		for ( int c=0;c<4;c++)
		{
			printf("%d " , array[r][c]); 
		}
		printf("\n");
	}

}

void display( int arr[][4])
{
	for ( int i=0;i<4;i++)
	{
		arr[i] += i;
	}
}

int main()
{
	int array[][4]={
		1,2,1,2,
		1,2,3,2,
		1,2,3,1
	};

	display( &array[0]);

	for ( int i = 0 ; i < 4;i++)
	{
		printf("%d " , array[0][i]);
	}
	return 0 ;
}
