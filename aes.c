#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/rand.h>

void pkcs_padding( unsigned char ** , int *);

void SubBytes( unsigned char state[][4] );

void ShiftRows( unsigned char state[][4]);

unsigned char g_mult ( unsigned char , unsigned char);

void MixColumns ( unsigned char state[][4]);

void xor_4( unsigned char arr1[4] , unsigned char arr2[4], unsigned char resultant_arr[4]);
void KeyExpansion( unsigned char initial_key[16]);
void RotWord( unsigned char key_schedule_row[4]);
void SubWord( unsigned char key_schedule_row[4]);

void AddRoundKey ( int round_num , unsigned char state_matrix[4][4] );

static const uint8_t sbox[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};


unsigned char Rcon[11][4] = {
	{0x00, 0x00, 0x00, 0x00},
	{0x01, 0x00, 0x00, 0x00},
	{0x02, 0x00, 0x00, 0x00},
	{0x04, 0x00, 0x00, 0x00},
	{0x08, 0x00, 0x00, 0x00},
	{0x10, 0x00, 0x00, 0x00},
	{0x20, 0x00, 0x00, 0x00},
	{0x40, 0x00, 0x00, 0x00},
	{0x80, 0x00, 0x00, 0x00},
	{0x1B, 0x00, 0x00, 0x00},
	{0x36, 0x00, 0x00, 0x00}
	};

unsigned char key_schedule[44][4];

int main()
{
	unsigned char * user_input , buffer[1000];
        scanf("%s" , buffer);
	int len_input = strlen(buffer);
	user_input = malloc( sizeof( unsigned char ) * (len_input + 1)); // 1 for null terminator in buffer
	memcpy( user_input , buffer, sizeof(unsigned char) * (len_input + 1));

//	printf("User_input:%s\n", user_input);
	pkcs_padding(&user_input , &len_input); //padding the user_input

	unsigned char state_matrix[4][4];
	int i=0;

	unsigned char iv[16];
	unsigned char key[16];
	unsigned char cipher_buffer[len_input];
	unsigned char cipher_matrix[4][4];

	if ( (RAND_bytes(iv , sizeof(iv))) != 1)
	{
		printf("IV couldn't be generated\n");
		return 1;
	}

	if ( RAND_bytes(key , sizeof(key)) != 1)
	{
		printf("Couldnt generate the main key\n");
		return 1;
	}

	KeyExpansion( key);

	i=0;
	for ( int c=0;c<4;c++)
	{
		for ( int r = 0;r<4;r++)
		{
			cipher_matrix[r][c] = iv[i];
			i++;
		}
	}


	int j=0;
	i=0;
	int round = 1;
	//aes encryption:
	for ( int b=1;b<= (len_input/16);b++)
	{

		for ( int c=0;c<4;c++)
		{
			for ( int r=0;r<4;r++)
			{
				state_matrix[r][c] = user_input[j]; // creating new block from user_input
				state_matrix[r][c] ^= cipher_matrix[r][c]; // Pn XOR Cn-1
				j++;
			}
		}

		AddRoundKey(0, state_matrix);
		for ( ;round<= 9;round++)
		{
			SubBytes(state_matrix);
			ShiftRows(state_matrix);
			MixColumns(state_matrix);
			AddRoundKey(round , state_matrix);
		}

		SubBytes(state_matrix);
		ShiftRows(state_matrix);
		AddRoundKey(10 , state_matrix);

		//storing state into cipher_buffer

		for ( int c=0;c<4;c++)
		{
			for ( int r=0;r<4;r++)
			{
				cipher_buffer[i] = state_matrix[r][c];// Ciphertext = C1 || C2 || C3...
				cipher_matrix[r][c] = cipher_buffer[i]; //C1 C2 etc..
				i++;
			}
		}

	}

	printf("len_input: %d" , len_input);
	for ( int i = 0 ;i< len_input;i++)
	{
		printf("%02x " , cipher_buffer[i]);
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


void SubBytes( unsigned char state[][4])
{
//	column-wise operate kiya hai ( doesnt matter in this step)
	for  ( int c = 0;c<4;c++)
	{
		for ( int r=0;r<4;r++)
		{
			state[r][c] = sbox[state[r][c]];
		}
	}

}


void ShiftRows( unsigned char state[][4])
{
	int row_num=0;
	while ( row_num <4)
	{
		for ( int times = 0; times < row_num; times++)
		{

			for ( int c = 0;c<3;c++)
			{
				int temp = state[row_num][c+1];
				state[row_num][c+1]= state[row_num][c];
				state[row_num][c] = temp;
			}
		}

		row_num++;
	}
}

 

unsigned char g_mult ( unsigned char byte , unsigned char mult_with)
{
	unsigned char result;
	if ( mult_with == 1)
		return byte;
	else if ( mult_with == 2)
	{
		if ( byte & 0x80 )
			result= (byte << 1 ) ^ 0x1B;
		else
			result = byte << 1;
		return result;
	}

	else if ( mult_with == 3)
	{
		unsigned char temp = g_mult(byte , 2);
		result = temp ^ byte;
		return result;
	}

	else
		printf("Factor problem in GF(2^8) multiplication");
}

void MixColumns ( unsigned char state[][4])
{
	//manipulate column wise

	//IDEA1:
	//store the columns row-wise in a diff array
//
//	unsigned char array[4][4];
//	for ( int r = 0 ;r< 4;r++)
//	{
//		for (int c = 0 ;c< 4;c++)
//		{
//			array[c][r]= state[r][c];
//		}
//	}

//	for ( int r =0;r<4;r++)
//	{
//		for ( int c =0;c<4;c++)
//		{
//			printf("%d ", state[r][c]);
//		}
//		printf("\n");
//	}
//	printf("array mat:\n");
//	for ( int r =0;r<4;r++)
//	{
//		for ( int c =0;c<4;c++)
//		{
//			printf("%d ", array[r][c]);
//		}
//		printf("\n");
//	}

	//IDEA2: ( better idea)
	unsigned char temp[4];
	for (int c = 0; c < 4; c++)
	{
	    // Extract column into temp buffer
	    for (int r = 0; r < 4; r++)
	    {
	        temp[r] = state[r][c];
	    }

	    // Perform MixColumns transformation using temp values
	    state[0][c] = g_mult(temp[0], 0x02) ^ g_mult(temp[1], 0x03) ^ temp[2] ^ temp[3];
	    state[1][c] = temp[0] ^ g_mult(temp[1], 0x02) ^ g_mult(temp[2], 0x03) ^ temp[3];
	    state[2][c] = temp[0] ^ temp[1] ^ g_mult(temp[2], 0x02) ^ g_mult(temp[3], 0x03);
	    state[3][c] = g_mult(temp[0], 0x03) ^ temp[1] ^ temp[2] ^ g_mult(temp[3], 0x02);
	}
}


void RotWord( unsigned char key_schedule_row[4])
{
	//rotate word by 1 byte left
	unsigned char temp =key_schedule_row[0];

	key_schedule_row[0] = 	key_schedule_row[1];
	key_schedule_row[1] =	key_schedule_row[2];
	key_schedule_row[2]=	key_schedule_row[3];
	key_schedule_row[3] = temp;

}


void SubWord( unsigned char key_schedule_row[4])
{

	for ( int i = 0 ; i < 4;i++)
	{
		key_schedule_row[i] = sbox[key_schedule_row[i]];
	}

}
//
//void Rcon( unsigned char key_schedule_row[4])
//{
//	//call the function only if the word we are working with's index is i % 4 ==0
//
//
//
//}

void xor_4( unsigned char arr1[4] , unsigned char arr2[4], unsigned char resultant_arr[4])
{
	int common_length = 4;

	for ( int i=0;i<common_length;i++)
	{
		resultant_arr[i]= arr1[i] ^ arr2[i];
	}
}

void KeyExpansion( unsigned char initial_key[16])
{
//	unsigned char key_schedule [44][4];
	int i =0;
	unsigned char temp[4];
	for ( int r = 0 ; r < 4;r++)
	{
		for ( int c = 0 ; c< 4;c++)
		{
			key_schedule[r][c] = initial_key[i];
			i++;
		}
	}

	// int * and int (*) [4]
	for ( int r = 4;r< 44;r++)
	{
		if ( r % 4 == 0)
		{
			memcpy(temp,key_schedule[r-1], 4) ; //temp points at a word ( key_schedule's row )
			RotWord(temp);
			SubWord(temp);
			temp[0] ^= Rcon[r/4][0];
			xor_4(&key_schedule[r-4][0] ,temp, &key_schedule[r][0]);
		}

		else if ( r % 4 != 0)
		{
			xor_4(&key_schedule[r-4][0] , &key_schedule[r-1][0], &key_schedule[r][0]);
		}
	}

}

//understand the dynamics of expanded keys and how they are spreaded
// 4 words used in each round i.e. 4 rows


void AddRoundKey ( int round_num,  unsigned char state_matrix[4][4] )
{
	int w_ind = 0;
	for ( int reference = 0 ; reference < round_num; reference++)
	{
		w_ind +=4;
	}

	for ( int c = 0 ;c<4;c++)
	{
		for ( int r = 0 ; r< 4;r++)
		{
			state_matrix[r][c] ^= key_schedule[w_ind][r];

		}

		w_ind++;
	}
}


