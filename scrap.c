#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void display ( unsigned char hexa)
{
	printf("%02x" , hexa);
}

int main()
{
	display(0x05);
	return 0 ;
}
