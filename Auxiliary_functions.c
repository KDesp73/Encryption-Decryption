#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <ctype.h>


#define MAX 200000

#define HASHSIZE 8
#define GARSIZE 10

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif


bool checkInt(char input[]){
	int i;
	for(i = 0; i < strlen(input); i++){
        if(isdigit(input[i])==0)
            return false;
    }
    return true;
}

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

void addEnding(char filename[]){
	printf("\tType of file: [1].txt [2].jpg [3].png [4].pdf\n");
	printf("\t> ");
	char in[1];
	int inInt;
	do{
		scanf("%s", in);
		inInt = atoi(in);
	}
	while(checkInt(in) && (inInt < 1 || inInt > 4));
	
	switch(inInt){
		case 1: strcat(filename, ".txt");break;
		case 2: strcat(filename, ".jpg");break;
		case 3: strcat(filename, ".png");break;
		case 4: strcat(filename, ".pdf");break;					
	}
}

void askFile(char filename[]){
	do{
		printf("\tGive file name: ");
		scanf("%s", filename);
	}
	while(!checkName(filename)); // && !checkName(filename)!checkTXT(filename)
	
	//strcat(filename, ".txt");
	addEnding(filename);
	printf("\n\tFile name: %s\n", filename);
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
/*For int hash
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
	int count = 0;
	memset(temp, 0, MAX);
	printf("\tGive text: ");
	do{
		memset(temp, 0, strlen(temp)); //Empty array
		fgets(temp, MAX, stdin);
		
		if(count > 0 && !checkInput(temp)){
			printf("\tGive text: ");
		}
		
		count++;
	}
	while(!checkInput(temp));
	
	strcpy(buffer, temp);
}

void chooseInput(char buffer[]){
	char input[1];
	int choice;
	
	WORD Attributes = 0;
	printf("\n\tSelect Input Method: [0]Return [1]File [2]Text\n");
	do{	
		do{
			SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("\t> ");
			ResetConsoleColour(Attributes);
			scanf("%s", input);
		}
		while (!checkInt(input));
		choice = atoi(input);
	}
	while(choice < 0 || choice > 2);

	switch(choice){
		case 0:
			return;
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
	WORD Attributes = 0;
	printf("\n\tSelect Output Method: [1]Create File [2]Print text [3]Both\n");
	do{
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
		printf("\t> ");
		ResetConsoleColour(Attributes);
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
			if(strlen(out) > 50){
				printf("\n\t%s Text:\n%s\n", msg, out);
			}
			else{
				printf("\n\t%s Text:\n\t%s\n", msg, out);
			}
			break;
		case 3:
			if(strlen(out) > 50){
				printf("\n\t%s Text:\n%s\n", msg, out);
				askFile(filename);
				writeFile(out, filename);
			}
			else{
				printf("\n\t%s Text:\n\t%s\n", msg, out);
				askFile(filename);
				writeFile(out, filename);
			}
			break;
		default:
			printf("\t\tERROR MESSAGE: OUTPUT -> DO-WHILE -> CHOICE");
			exit(1);
	}
	memset(filename, 0, strlen(filename));
}

void caps(char hash[]){
	 for(int i= 0; i < strlen(hash); i++){
	 	hash[i] = toupper(hash[i]);
	 }
}

void about(){
	WORD Attributes = 0;
	printf("\n\n+---------------------------------------------------+\n");
	SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("		      -ABOUT-\n");
	ResetConsoleColour(Attributes);
	printf("\n");
	printf("   Made by: 	Georgalis Thanasis\n");
	printf("		Giantselidis Konstantinos\n");
	printf("		Despoinidis Konstantinos\n");
	printf("		Mokas Konstantinos\n");
	printf("\n");
	printf("	    Department of Information and \n");
	printf("	     Electronic Engineering | IHU \n");
	printf("\n");
	printf("		     @2021-22\n");
	printf("\n");
	printf("+---------------------------------------------------+\n");
}


void logo(){
	printf("\t      ______  _____    \n");
	printf("\t     /\\  ___\\/\\  __-.  \n");
	printf("\t     \\ \\  __\\\\ \\ \\/\\ \\ \n");
	printf("\t      \\ \\_____\\ \\____- \n");
	printf("\t       \\/_____/\\/____/ \n");
	printf("\n");
	printf("\t   =ENCRYPTION-DECRYPTION=\n");
}

bool verify(char a[], char b[]){
	return strcmp(a, b);
}
