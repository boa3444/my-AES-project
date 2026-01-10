//to reanalyze some concepts beforehand
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display( int array[3])
{
	for ( int r = 0 ;r<3;r++)
	{
		printf("%d ", array[r]);
	}

}

int main()
{
	int matrix[3][3]= {
		{1,2,3},
		{12,12,12},
		{7,66,7}
		};

	int (*p) [3] = &matrix[2];
//	for (int i = 0 ; i< 3 ;i++)
//	{
//		for ( int ind = 0 ; ind < 3;ind++)
//		{
//			printf("%d " , *(*(p+i) + ind));
//		}
//		printf("\n");
//	}
//	printf("lala\n");
//	for ( int r = 0 ; r< 3;r++)
//	{
//		for ( int i = 0 ; i< 3;i++)
//		{
//				printf("%d " , *( (*p + r) + i) );
//
//
//		}
//
//		printf("\n");
//	}

	display(*p);
	return 0 ;
}
