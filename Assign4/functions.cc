#include "functions.h"
#include <iostream>
using namespace std;
void caesar_shift(int numberShift, char *Temp, size_t howManyRead)
{
	for(size_t index = 0; index < howManyRead; index++)
	{
		int charNum;
		if(Temp[index] >= 97 && Temp[index]<= 122) // checks the if the character letter between a and z
		{			//a				//  z
			// Letter to number:     char - 'a'
			// Example:              'k' - 'a' = 107 - 97 = 10
			charNum = Temp[index] - 97;
			// charNum = 10
			charNum = charNum + numberShift;
			// charNum = 10 + numberShift
							 // 2
			charNum = charNum % 26;
			// just in case it goes over 26, it will use % to loop back to a
			charNum = charNum + 97;
			// Number to letter: charNum + 'a'
			Temp[index] = charNum;
			// Number to letter:     charNumb + 'a'
			// Example:              12 + 'a' = 12 + 97 = 109 = 'm'
		}

		if(Temp[index] >= 65 && Temp[index] <= 90) // checks the letter if the character letter is between A and Z
		{			//A					//Z
			// Letter to number:     char - 'A'
			// Example:              'K' - 'A' = 75 - 65 = 10
			charNum = Temp[index] - 65;
			// Shift, loop around Z: (number + shift) mod 26
			charNum = charNum + numberShift;
			// Example:              (10 + 2) % 26 = 12
			charNum = charNum % 26;
			// Number to letter:     number + 'A'
			charNum = charNum + 97;
			Temp[index] = charNum;
			// Example:              12 + 'A' = 12 + 65 = 77 = 'M'
			//Temp[index] = 65 + ((Temp[index] - 65 + numberShift) % 26);
								//^was 'A'				//^was 'A'
		}
	}
}
// shifts the characters up or down the ascii chart
void bin_shift(int shift_amount, char *bytes, size_t bytes_length)
{
	for(size_t index = 0; index < bytes_length; index++) 
	{
		bytes[index] = bytes[index] + shift_amount; // shifts the character shift_amount position on that ascii table.
	}
}

void change_to_hex(char *bytes, char *hex_digits, size_t bytes_length)
{
	char hex_accepted_value[] = "0123456789abcdef"; // initionalize the possible hex values;
	for(size_t index = 0; index < bytes_length; index++) 
	{
		// take first nibble, convert to a char, and store in hex_digits
		hex_digits[2*index] = hex_accepted_value[(bytes[index] & 0xf0) >> 4]; 
		// we have to set hexbuffer twice as 
		//  much since we are returning more than 2  
		//H= 	  0100 1000	   & 1111 0000
		//=0110 0000|
		// 
		//=>> 0110| 0000 <= this gets deleted
		//
		// take second nibble, convert to a char, and store in hex_digits
		hex_digits[2*index+1] = hex_accepted_value[(bytes[index] & 0x0f)];
	}	// H=     	0100 1000    & 0000 1111 
}		// H=       0000 1000

void convert_to_bin(char *bytes, char *bit_stream, size_t bytes_length){
	// loop over each byte
	char bin_accepted_values[] = "01";
	for(size_t index = 0; index < bytes_length; index++)  {
		// compare each bit to 1 or 0 using binary anding (& symbol)
		// shifts the bit to the least significant position to result
		//  in 1 or a 0.
	    bit_stream[8*index+0] = bin_accepted_values[(bytes[index] & 128) >> 7];
	    bit_stream[8*index+1] = bin_accepted_values[(bytes[index] &  64) >> 6];
	    bit_stream[8*index+2] = bin_accepted_values[(bytes[index] &  32) >> 5];
	    bit_stream[8*index+3] = bin_accepted_values[(bytes[index] &  16) >> 4];
	    bit_stream[8*index+4] = bin_accepted_values[(bytes[index] &   8) >> 3];
	    bit_stream[8*index+5] = bin_accepted_values[(bytes[index] &   4) >> 2];
	    bit_stream[8*index+6] = bin_accepted_values[(bytes[index] &   2) >> 1];
	    bit_stream[8*index+7] = bin_accepted_values[(bytes[index] &   1) >> 0];
	}
} 
