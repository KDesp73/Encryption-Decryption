#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX 1000
#define HASHSIZE 4
#define GARSIZE 10

//Encryption
void encr();
int createHash();
void swap();
void s2h();
void ccEncr();
void addGarbage();

//Decryption
void decr();
void getHash();
void cleanBuffer();
void ccDecr();
void h2s();
//swap again

//Áuxiliary functions
void getTextFILE();
void getTextSTRING();
void putTextSTRING();
void putTextFILE();

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
void chooseInput(char buffer[]){
	int choice;
	printf("\nSelect Input Method: [1]File [2]Text\n");
	do{
		printf("> ");
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
			printf("chooseInput -> DO-WHILE -> CHOICE");
			exit(1);
	}
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
void chooseOutput(char _decrypted[], char msg[]){
	int choice;
	printf("Select Output Method: [1]Create File [2]Print text [3]Both\n");
	do{
		printf("> ");
		scanf("%d", &choice);
	}
	while(choice < 1 || choice > 3);
	
	char filename[50];
	switch(choice){
		case 1:
			askFile(filename);
			writeFile(_decrypted, filename);
			break;
		case 2:
			printf("%s Text: %s", msg, _decrypted);
			break;
		case 3:
			printf("%s Text: %s\n", msg, _decrypted);
			askFile(filename);
			writeFile(_decrypted, filename);
			break;	
		default:
			printf("OUTPUT -> DO-WHILE -> CHOICE");
			exit(1);
	}
	memset(filename, 0, strlen(filename));
}

//========MAIN========
int main(){
	srand(time(NULL));
	char buffer[MAX];
	char temp[MAX];
	
	encr(buffer, temp);
	memset(buffer, 0, strlen(buffer));
	memset(temp, 0, strlen(temp));
	decr(buffer, temp);
	
	system("pause");
	return 0;
}
//========END OF MAIN========


void encr(char buffer[], char _encrypted[]){
	printf("\n=======Encryption=======\n");
	memset(buffer, 0, strlen(buffer));
	chooseInput(buffer);
	printf("\nInitial text:\n%s\n", buffer);
	
	int HASH = createHash(buffer);
	printf("HASH NUM: %d", hashNum(HASH));
	swap(buffer, hashNum(HASH));
	printf("\nSwap text: %s\n", buffer);
	
	s2h(buffer);
	printf("\nHex text: %s\n", buffer);	
	
	ccEncr(buffer, hashNum(HASH));
	printf("\nCCE text: %s\n", buffer);
	
	//Add Hash & Garbage
	char sHash[16], garbage[GARSIZE];
	itoa(HASH, sHash, 10);
	garbageGenerator(garbage);
	allinone(_encrypted, sHash, buffer, garbage);
	
	chooseOutput(_encrypted, "Encrypted");
	//printf("F: %s", _encrypted);	
}

void decr(char buffer[], char _decrypted[]){
	printf("\n=======Decryption=======\n");
	memset(buffer, 0, strlen(buffer));
	chooseInput(buffer);
	
	//Get Hash & remove garbage
	char shash[HASHSIZE];
	
	if(!isAcceptableSize(buffer)) return;
	
	getHash(buffer, shash, HASHSIZE);
	cleanBuffer(buffer);
	
	int HASH = atoi(shash);
	
	ccDecr(buffer, hashNum(HASH));
	printf("\nCCD text: %s\n", buffer);
	
	h2s(buffer);
	printf("\nHEX: %s", buffer);
	
	swap(buffer, hashNum(HASH));
	printf("\nSwap: %s", buffer);
	
	//Generate hash
	//Validate
	
	strncpy(_decrypted, buffer, strlen(buffer));
	
	chooseOutput(_decrypted, "Decrypted");
}



void h2s(char io[]){
	int len = strlen(io);
  	char string[MAX];
  	int i=0, j=0;
	for (j = 0; j < len-1; j += 2) {
    	int val[1];
    	sscanf(io + j, "%2X", val);
    	string[i] = val[0];
    	string[i + 1] = '\0';
    	++i;
  	}
  	strcpy(io, string);
}


void ccDecr(char io[], int num){ //io -> input / output
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


void ccEncr(char io[], int num){ //io -> input / output
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


void s2h(char io[]){
  	int len = strlen(io);
	char temp[MAX];
	strncpy(temp, io, len);
	
	memset(io, 0, strlen(io)); //Empties Array
	
  	int j = 0;
	for (int i = 0; i < len; ++i){
		sprintf(io + j, "%02X", temp[i] & 0xff);
		j += 2;
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


int createHash(char buffer[]){
	return 1234;
}


void getTextFILE(char buffer[]){
	char filename[MAX-MAX/2];
	askFile(filename);
	//printf("FILE: %s", filename);
	
	getFile(filename, buffer);
}


void getTextSTRING(char buffer[]){
	char temp[MAX];
	memset(temp, 0, strlen(temp)); //Empty array
	printf("Give text: ");
	scanf("%s", temp);
	
	strncpy(buffer, temp, strlen(temp));
}
