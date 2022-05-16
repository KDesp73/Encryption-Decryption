#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <ctype.h>


#define MAX 100000

#define HASHSIZE 8
#define GARSIZE 10

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif


void getFile(char file[], char buffer[]){
	memset(buffer, 0, strlen(buffer));
	FILE *fp;
    fp = fopen(file, "rb");
	size_t i;
	
	for (i = 0; i < MAX; ++i){
    	int c = getc(fp);
    	
    	if (c == EOF){
        	buffer[i] = 0x00;
        	break;
    	}	
    	buffer[i] = c;
	}
    fclose(fp);
}

bool checkName(char name[]){
	char characters[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_,!@#$%^&*()+=;:{[]}";
	
	int i,j, count;
	for(i=0; i<strlen(name); i++){
		for(j=0; j<strlen(characters); j++){
			if(name[i] == characters[j])
				count++;
		}
	}
	
	return count == strlen(name);
}

void askFile(char filename[]){
	do{
		printf("\tGive file name: ");
		scanf("%s", filename);
	}
	while(!checkName(filename)); // && !checkName(filename)!checkTXT(filename)
	
	strcat(filename, ".txt");
}

void digits(int num, int digits[]){
	int temp, numlength;
	int i, j, k;
	char snum[50];
	
	itoa(num, snum, 10);
	
	numlength = strlen(snum);
	
	i = numlength;
	while(num != 0){
		j = numlength - i;
		
		temp = num / (int)pow((double)10, (double)i-1);
		num = num % (int)pow((double)10, (double)i-1);
		
		digits[j] = temp;
		i--;
	}
}
/*
int hashNum(int hash){
	int digitsArr[MAX];
	digits(hash, digitsArr);
	
	for(int i; sizeof(digitsArr)/sizeof(int); i++){
		if(digitsArr[i] <= 1) continue;
		return digitsArr[i];
	}
}*/

int hashNum(char hash[]){
	char nums[] = "23456789";
	char *str = malloc(2);
	str[1] = '\0';
	for(int i = 0 ; strlen(hash); i++){
		for(int j = 0; strlen(nums); j++){
			if(hash[i] != nums[j]) break;
			str[0] = hash[i];
			//strnum+1 = '\0';
			return atoi(str);
		}
	}
	return -1;
}

void swapKout (char P[], int n1, int n2){
    char temp;
    while (n1 < n2){
	    temp = P[n2]; 
	    P[n2] = P[n1];
	    P[n1] = temp;
	    n2--;
	    n1++;
    }
}

int f(int x, int y){
	return x*y+x+y;
}

void allinone(char finalarray[], char hash[], char ogArray[], char garbage[]){
	memset(finalarray, 0, strlen(finalarray));
	strncat(finalarray, hash, HASHSIZE);
	strncat(finalarray, ogArray, strlen(ogArray));
	strncat(finalarray, garbage, GARSIZE);
}

void getHash(char buffer[], char hash[], int sizeofHash){
	memset(hash, 0, strlen(hash));
	for(int i = 0; i < sizeofHash; i++){
		hash[i] = buffer[i];
	}
}

void removeGarbage(char arr[], int sizeOfGar, int sizeOfHash){
	char arr1[MAX];
	int j = 0;
	for(int i = sizeOfHash; i < strlen(arr) - sizeOfGar - 1; i++){
		arr1[j] = arr[i];
		j++;
	}
	strcpy(arr, arr1);
}

bool checkLetter(char letter){
	char letters[] = "ABCDEF";
	int i;
	for(i=0;i<strlen(letters);i++){
		if(letter == letters[i])
			return true;
	}
	return false;
}

void garbageGenerator(char garbage[]){
	memset(garbage, 0, strlen(garbage));
	
	char hexChars[] = "0123456789ABCDEF";
	char num[] = "0123456789";

	for(int i = 0; i < GARSIZE; i++){
		garbage[i] = hexChars[rand()%strlen(hexChars)];
		if(checkLetter(garbage[i])){
			garbage[i+1] = num[rand()%strlen(num)];
		}
	}
}

void cleanBuffer(char buffer[]){
	char temp[MAX];
	memset(temp, 0, strlen(temp));
	int i, j = 0;
	for(i = HASHSIZE; i < strlen(buffer) - GARSIZE - 1; i++){
		temp[j] = buffer[i];
		j++;
	}
	strcpy(buffer, temp);
}

int isAcceptable(char buffer[]){
	if(strlen(buffer) == 0) return 1; //Empty file
	else if(strlen(buffer) < HASHSIZE + GARSIZE) return 2; //Make it do the decryption without removing garbage
	//else if(/*Not acceptable characters*/) return 3;
	else return 0; //OK
}

void writeFile(char buffer[], char filename[]){
	FILE *fp;
	fp = fopen(filename, "w+");
	fputs(buffer, fp);
	fclose(fp);
}

bool checkInput(char buffer[]){
	return strlen(buffer) > 2; //it's... stable
}

void getTextFILE(char buffer[]){
	char filename[100];
	
	do{
		askFile(filename);
		
		if(access(filename, F_OK) != 0)
			printf("\t\tERROR MESSAGE: File does not exist\n\n");
	}
	while(access(filename, F_OK) != 0); //checks if file exists
	
	memset(buffer, 0, strlen(buffer));
	getFile(filename, buffer);
}


void getTextSTRING(char buffer[]){
	char temp[MAX];
	memset(temp, 0, MAX);
	/*
	do{
		memset(temp, 0, strlen(temp)); //Empty array
		printf("\tGive text: ");
		fgets(temp, MAX, stdin);
	}*/
	while(!checkInput(temp)){
		memset(temp, 0, strlen(temp)); //Empty array
		printf("\tGive text: ");
		fgets(temp, MAX, stdin);
	}

	strcpy(buffer, temp);
}

void chooseInput(char buffer[]){
	int choice;
	printf("\n\tSelect Input Method: [1]File [2]Text\n");
	do{
		printf("\t> ");
		scanf("%d", &choice);
	}
	while(choice < 1 || choice > 2);

	switch(choice){
		case 1:
			getTextFILE(buffer);
			break;
		case 2:
			getTextSTRING(buffer);
			break;
		default:
			printf("\t\tERROR MESSAGE: chooseInput -> DO-WHILE -> CHOICE");
			exit(1);
	}
}
void chooseOutput(char out[], char msg[]){
	int choice;
	printf("\tSelect Output Method: [1]Create File [2]Print text [3]Both\n");
	do{
		printf("\t> ");
		scanf("%d", &choice);
	}
	while(choice < 1 || choice > 3);

	char filename[50];
	switch(choice){
		case 1:
			askFile(filename);
			writeFile(out, filename);
			break;
		case 2:
			printf("\t%s Text:\n\t%s", msg, out);
			break;
		case 3:
			printf("\t%s Text:\n\t%s\n", msg, out);
			askFile(filename);
			writeFile(out, filename);
			break;
		default:
			printf("\t\tERROR MESSAGE: OUTPUT -> DO-WHILE -> CHOICE");
			exit(1);
	}
	memset(filename, 0, strlen(filename));
}

/*
int main(){
	char buffer[MAX];
	for(int i = 0; i < 10; i++){
		printf("\nText: ");
		scanf("%s", buffer);
		
		if(strlen(buffer) > 1) printf("TRUE\n");
		else printf("\nFALSE\n");
	}
	
	
	system("pause");
	return 0;
}
*/

//COLORS
void SetConsoleColour(WORD* Attributes, DWORD Colour){
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

void caps(char hash[]){
	 for(int i= 0; i < strlen(hash); i++){
	 	hash[i] = toupper(hash[i]);
	 }
}


