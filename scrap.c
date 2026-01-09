#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void display ( unsigned char hexa)
{



}
int main()
{
	int matrix[3][3]= {
		{1,2,3},
		{12,12,12},
		{7,66,7}
		};

	int (*p) [3] = &matrix[0];
//
//	for ( int i = 0 ; i < 3;i++)
//	{
//		printf("%d " , (*p)[i]);
//	}

	printf("%d\n", *(*(p + 2) + 2));
	printf("lala\n");
	for ( int r = 0 ; r< 9;r += 3)
	{
		for ( int i = 0 ; i< 3;i++)
		{
				printf("%d " , *( (*p + r) + i) );


		}

	printf("\n");
	}
	return 0 ;
}
