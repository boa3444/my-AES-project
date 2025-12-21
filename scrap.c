#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int len;
	char * name, buffer[1000];
	scanf("%999s" , buffer);
	len = strlen(buffer);
//	printf("%d" , len);
	name = malloc ( sizeof(char) * (len+1));
	for ( int i=0;i< len+1;i++)
	{
		printf("%c", buffer[i]); 
	}

	memcpy(name , buffer, sizeof(char) * (len+1));
	printf("%s" , name);
	return 0;
}
