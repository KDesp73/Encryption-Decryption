#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>


#define MAX 1000
#define HASHSIZE 4
#define GARSIZE 10


void getFile(char file[], char buffer[]){
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
	
	if(count == strlen(name))
		return true;
	else
		return false;
}
void askFile(char file[]){
	do{
		printf("Give file name: ");
		scanf("%s", file);
	}
	while(!checkName(file)); // && !checkName(file)!checkTXT(file)
	
	strcat(file, ".txt");
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
int hashNum(int hash){
	int digitsArr[MAX];
	digits(hash, digitsArr);
	
	for(int i; sizeof(digitsArr)/sizeof(int); i++){
		if(digitsArr[i] <= 1) continue;
		return digitsArr[i];
	}
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
	int i, j = 0;
	for(i = HASHSIZE; i < strlen(buffer) - GARSIZE - 1; i++){
		temp[j] = buffer[i];
		j++;
	}
	strcpy(buffer, temp);
}
bool isAcceptableSize(char buffer[]){
	if(strlen(buffer) < HASHSIZE + GARSIZE) return false;
	return true;
}
void writeFile(char buffer[], char filename[]){
	FILE *fp;
	fp = fopen(filename, "w+");
	fputs(buffer, fp);
	fclose(fp);
}


