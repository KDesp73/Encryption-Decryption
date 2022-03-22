//Encr-Decr string input

#define _GNU_SOURCE
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX 500




bool checkLetter(char letter, char arr[]){
	int i;
	for(i=0;i<strlen(arr);i++){
		if(letter == arr[i])
			return true;
	}
	return false;
}

void randomGarbage(char garbage[]){
	char chars[] = "ABCDEF";
	char num[] = "0123456789";

	int i;
	for(i=0; i < 10; i++){
		if(i % 2 == 0){
			garbage[i] = chars[rand()%strlen(chars)];
		}
		else{
			garbage[i] = num[rand()%strlen(num)];
		}
	}
	
	/*int j;
	for(j = 0; j < strlen(garbage); i++){
		if(!checkLetter(garbage[j], "0123456789ABCDEF")){
			garbage[j] = '0';
		}
		else
			continue;
	}*/
}

void swapKout (char P[], int n1, int n2, int hashN){
    char temp;
    while (n1 < n2)
	{
	    temp = P[n2]; 
	    P[n2] = P[n1];
	    P[n1] = temp;
	    n2--;
	    n1++;
    }
}

void swap (char P[], int hashN){
	int messageL = strlen(P);
	int repeats = messageL / hashN;	
	
	if (messageL % hashN == 0 || messageL % hashN == 1)
	{
		int n1 = 0;
	    int n2 = hashN - 1;
	    int counter = 0;
	do
	{
		swapKout(P, n1, n2, hashN);
		n1 = n1 + hashN;
		n2 = n2 + hashN;
		counter++;
	}
	while (counter < repeats);
    }
	
	else
	{
		int n1 = 0;
	    int n2 = hashN - 1;
	    int counter = 0;
	do
	{
		swapKout(P, n1, n2, hashN);
		n1 = n1 + hashN;
		n2 = n2 + hashN;
		counter++;
	}
	while (counter < repeats);
	n2 = messageL - 1;
	swapKout (P, n1, n2, messageL % hashN);
	}
}
	
//Hex
void stringToHex(char string[]){
  	char hex[MAX];
	int len = strlen(string);

  	int i, j = 0;
	for (i = 0; i < len; ++i){
		sprintf(hex + j, "%02X", string[i] & 0xff);
		j += 2;
	}
	
	strcpy(string, hex);
}

int f(int x, int y){
	return x*y+x+y;
}

//caesars cypher
void caesarsCypherEncr(char io[], int num){ //io -> input / output
	char hexChars[] = "0123456789ABCDEF";
	
	int i, j, a;
    for (i = 0; i < strlen(io); i++){
        a = f(num, i)%16+1;
		for (j = 0; j < strlen(io);){  //Psaxnei ton characthra sto hexChars
            while (io[i] != hexChars[j]){        	
				j++;
            }
            break;
        }
        
        if(j + a >= strlen(hexChars)){  //Gia otan einai sto telos tou string, na phgainei apo thn arxh
            j -= strlen(hexChars);
            io[i] = hexChars[j + a];
        }
        //else if()
        else{
            io[i] = hexChars[j + a];
            j = 0;
        }
    }
}



void caesarsCypherDecr(char io[], int num){ //io -> input / output
	char hexChars[] = "0123456789ABCDEF";

	int i, j, a;
    for (i = 0; i < strlen(io); i++){
    	a = f(num, i)%16+1;
        for (j = 0; j < strlen(io);){  //Psaxnei ton characthra sto hexChars
            while (io[i] != hexChars[j]){
                j++;
    		}
            break;
        }
        
        if(j < a){  //Gia otan einai sthn arxh tou string, na phgainei sto telos
            j += strlen(hexChars);
            io[i] = hexChars[j - a];
        }
        else{
            io[i] = hexChars[j - a];
            j = 0;
        }
    }
}
	
//Hex decrypt
void hexToString(char hex[]){
	int len = strlen(hex);
  	char string[MAX];
  	int i=0, j=0;
	for (j = 0; j < len-1; j += 2) {
    	int val[1];
    	sscanf(hex + j, "%2X", val);
    	string[i] = val[0];
    	string[i + 1] = '\0';
    	++i;
  	}
  	strcpy(hex, string);
}
	

//Verify
bool stringsSame(char str1[], char str2[]){
	if(strcmp(str1, str2) == 0)
		return true;
	else
		return false;
}

void removeGarbage(char arr[], int sizeOfGar){
	char arr1[MAX];
	int i, j = 0;
	for(i = 0; i < strlen(arr) - sizeOfGar - 1; i++){
		arr1[j] = arr[i];
		j++;
	}
	strcpy(arr, arr1);
}


void input(char msg[], char io[]){	
	printf("\n%s: ", msg);
	scanf("%s", io);
}

void output(char msg[], char io[]){
	printf("%s: %s\n\n", msg, io);
}

void Encryption(){
	char io[MAX];
	input("Input message to encrypt", io);
	
	swap(io, 2);
	output("Io after swap", io);
	stringToHex(io);
	output("Io after hex", io);
	caesarsCypherEncr(io, 3);
	output("Io after caesars", io);
	
	char garbage[9]; 
	randomGarbage(garbage);
	output("Garbage", garbage);
	strcat(io, garbage);
	
	output("Encrypted message", io);
	printf("\n\n");
}

void Decryption(){
	char io[MAX];
	input("Input message to decrypt", io);
	
	removeGarbage(io, 10);
	
	caesarsCypherDecr(io, 3);
	output("Io after casars decr", io);
	hexToString(io);
	output("Io after hex", io);
	swap(io, 2);
	output("Io after swap", io);
	
	output("Decrypted message", io);
	printf("\n\n");
}

//Menu
void menu(){
	printf("\n\n-Main Menu-\n");
	printf("1. Encrypt\n");
	printf("2. Decrypt\n");
	printf("3. Exit\n");
	
	
	int choice;
	do{
		printf("> ");
		scanf("%d", &choice);
	}
	while(choice < 1 || choice > 3);
	
	switch(choice){
		case 1:
			Encryption();
			menu();
			break;
		case 2:
			Decryption();
			menu();
			break;
		case 3:
			printf("\n\nBye!\n\n");
			system("pause");
			exit(0);
			break;
	}
}

int main(){
	menu();
	
	system("pause");
	return 0;
}
