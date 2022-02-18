
//Encryption - Decryption Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_array 50
#include <stdbool.h>
#include <float.h>

void allinone(char finalarray[]){

	strcpy(finalarray,"");
	strcat(finalarray,hash);
	strcat(finalarray,array);
}

int main(){
	/*char test[2][100] = {"fysdb","egdsf"};
	
	int secondd = 2, how_many_leters_in_=5, final_string_len=200;
	
	
	char finalstring[final_string_len];
	char tempstr[how_many_leters_in_];
	for (int i=0;i<=secondd;i++){
		strcpy(tempstr, "asd");
		printf("test: %c\n",tempstr);
		for (int j=0;j<how_many_leters_in_;j++){
			strcat(tempstr,test[i][j]);
			
		}
		strcat(finalstring, tempstr);
		
	}
	
	printf("%c\n",finalstring);*/
	
	
	int counter=200;
	char hash[16],array[counter];
	strcpy(hash,"2562825638012793");
	strcpy(array,"uhkdsciuhkjmaklsdhghjoljwnkncjd76 wiucfhuidsjxedc ");
	
	char finalarray[counter+16];
	allinone(finalarray);
	
	printf("%s\n",finalarray);
	
	
	
	system("pause");
}
