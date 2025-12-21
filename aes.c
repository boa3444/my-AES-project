#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/rand.h>

void pkcs_padding( unsigned char ** , int *);

int main()
{
	unsigned char * user_input , buffer[1000];
        scanf("%s" , buffer);
	int len_input = strlen(buffer);
	user_input = malloc( sizeof( unsigned char ) * (len_input + 1)); // 1 for null terminator in buffer
	memcpy( user_input , buffer, sizeof(unsigned char) * (len_input + 1));

//	printf("User_input:%s\n", user_input);
	pkcs_padding(&user_input , &len_input); //padding the user_input

//	for ( int i = 0 ; i < len_input;i++)
//	{
//		printf("%02x ", user_input[i]);
//	}

//	Store the user_input in state_matrix
	unsigned char state_matrix[4][4];
	int i=0;
	for ( int c= 0;c<4;c++) //column wise
	{
		for ( int r=0;r<4;r++)
		{
			state_matrix[r][c]= user_input[i];
			i++;
		}
	}


	unsigned char iv[16];
	if ( RAND_bytes(iv , sizeof(iv)) == NULL)
	{
		printf("IV couldn't be generated\n");
		return 1;
	}


	return 0;
}

void pkcs_padding ( unsigned char ** poi_to_arr , int * len_arr)
{
	int temp ;
	unsigned char pad_len;
	for ( int num = 1;;num++)
	{
		temp = num * 16;
		if ( temp > *len_arr)
		{
			pad_len = temp- *len_arr;
			break;
		}
	}

	temp = *len_arr; //for later use in setting new values in array
	*len_arr += pad_len;
	unsigned char *temp_poi = realloc(*poi_to_arr, *len_arr);
	if ( temp_poi == NULL)
	{
		printf("Reallocation of input array failed\n");
		return;
	}

	*poi_to_arr=temp_poi;

	for ( int i = temp; i < *len_arr ; i++)
	{
		(*poi_to_arr)[i] = (unsigned char) pad_len;
	}

}
