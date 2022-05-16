#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <windows.h>


#include "Auxiliary_functions.c"

#define MAX 100000
#define HASHSIZE 8
#define GARSIZE 10



//Encryption
void encr();
void createHash();
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


int decrInputErrors();


void menu(char _encr[], char _decr[]){
	WORD Attributes = 0;
	SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("\n\n\t\t::::Menu::::\n");
	ResetConsoleColour(Attributes);
	printf("\tSelect [1]Encryption [2]Decryption\n\t       [3]About [4]Exit\n");
	int choice;
	do{
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
		printf("\t> ");
		ResetConsoleColour(Attributes);
		scanf("%d", &choice);
	}
	while(choice < 1 || choice > 4);

	char buffer[MAX];
	memset(buffer, 0, strlen(buffer));
	
	switch(choice){
		case 1:
			encr(buffer, _encr);
			menu(_encr, _decr);
		case 2:
			decr(buffer, _decr);
			menu(_encr, _decr);
		case 3:
			getFile("about.txt", buffer);
			printf("\n%s\n", buffer);
			menu(_encr, _decr);
		case 4:
			exit(0);
		default:
			printf("\tWTF");
	}
}

//========MAIN========
int main(){
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	srand(time(NULL));
	
	char _encr[MAX];
	char _decr[MAX];

	printf("\t=============ENCRYPTION-DECRYPTION=============\n\n");
	menu(_encr, _decr);


	system("pause");
	return 0;
}
//========END OF MAIN========


void createHash(char buffer[], char chash[]){
	//strncpy(hash, "1A2BCD65", 8);
	
	int max_now = 0;
	int now = 0;
	char strings[10][MAX/10];
	int hs[MAX/10];
	char string[10];
	int i;
	int x = MAX/16;
	char iot[20];
	char temp_string[MAX] = "";
	char hs2[MAX/10];
	
	for(i=0;i<=MAX;i+=10){
		int h = buffer[i] + buffer[i+1] + buffer[i+2] + buffer[i+3] + buffer[i+4] + buffer[i+5] + buffer[i+6] + buffer[i+7] + buffer[i+8] + buffer[i+9];
		hs[now] = h>>13-i;
		hs2[now] = h^hs[now];
		now++;
		max_now++;	
	}
	
	
	for(i=0;i<=max_now;i++){
		if(hs2[i]<0) hs2[i]=fabs(hs2[i]);
		itoa(hs2[i],iot,16);
		strcat(temp_string,iot);
	}
	
	
	strncpy(chash,temp_string, 8);
	caps(chash);
}


void encr(char buffer[], char _encrypted[]){
	WORD Attributes = 0;
	SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("\n\t=======Encryption=======\n");
	ResetConsoleColour(Attributes);
	
	
	memset(buffer, 0, strlen(buffer));
	chooseInput(buffer);
	//printf("\nInitial text:\n%s\n", buffer);

	char HASH[8];
	createHash(buffer, HASH);
	//printf("HASH NUM: %d", hashNum(HASH));
	swap(buffer, hashNum(HASH)); 
	//printf("\nSwap text: %s\n", buffer);

	s2h(buffer);
	//printf("\nHex text: %s\n", buffer);

	ccEncr(buffer, hashNum(HASH)); 
	//printf("\nCCE text: %s\n", buffer);

	//Add Hash & Garbage
	char sHash[16], garbage[GARSIZE];
	//itoa(HASH, sHash, 10);
	garbageGenerator(garbage);
	allinone(_encrypted, HASH, buffer, garbage);

	chooseOutput(_encrypted, "Encrypted");
	//printf("F: %s", _encrypted);
}

void decr(char buffer[], char _decrypted[]){
	WORD Attributes = 0;
	SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("\n\t=======Decryption=======\n");
	ResetConsoleColour(Attributes);
	
	
	memset(buffer, 0, strlen(buffer));
	chooseInput(buffer);
	
	//Get Hash & remove garbage
	//char shash[HASHSIZE];
	char HASH[HASHSIZE];

	switch(decrInputErrors(buffer)){
		case 0: break;
		case -1: return;
	}

	getHash(buffer, HASH, HASHSIZE);

	cleanBuffer(buffer);

	//int HASH = atoi(shash);

	ccDecr(buffer, hashNum(HASH));
	//printf("\nCCD text: %s\n", buffer);

	h2s(buffer);
	//printf("\nHEX: %s", buffer);

	swap(buffer, hashNum(HASH));
	//printf("\nSwap: %s", buffer);
	
	memset(_decrypted, 0, MAX);
	strncpy(_decrypted, buffer, strlen(buffer));
	chooseOutput(_decrypted, "Decrypted");
	
	/*//Generate hash
	char NHASH[HASHSIZE];
	//memset(NHASH, 0, HASHSIZE);
	createHash(_decrypted, NHASH);
	printf("Nhash: %s", NHASH);
	//Validate
	if(strcmp(NHASH, HASH) == 0){
		chooseOutput(_decrypted, "Decrypted");
	}
	else{
		printf("\tERROR MESSAGE: Invalid hash");
	}*/
	
	
}



void h2s(char io[]){
	int len = strlen(io);
  	char string[MAX];
  	memset(string, 0, strlen(string));
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


void swap(char P[], int hashN){
	int messageL = strlen(P);
	int repeats = messageL / hashN;

	if (messageL % hashN == 0 || messageL % hashN == 1)
	{
		int n1 = 0;
	    int n2 = hashN - 1;
	    int counter = 0;
	do
	{
		swapKout(P, n1, n2);
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
			swapKout(P, n1, n2);
			n1 = n1 + hashN;
			n2 = n2 + hashN;
			counter++;
		}
		while (counter < repeats);
		n2 = messageL - 1;
		swapKout (P, n1, n2);
	}
}

void dummyDecr(char buffer[], char _decrypted[]){
	ccDecr(buffer, 2);
	//printf("\nCCD text: %s\n", buffer);

	h2s(buffer);
	//printf("\nHEX: %s", buffer);

	swap(buffer, 2);
	//printf("\nSwap: %s", buffer);

	//Generate hash
	//Validate
	memset(_decrypted, 0, MAX);
	strncpy(_decrypted, buffer, strlen(buffer));

	chooseOutput(_decrypted, "Decrypted");
}

int decrInputErrors(char buffer[]){
	char temp[MAX];
	switch(isAcceptable(buffer)){
		case 0:
			return 0;
			break;
		case 1:
			printf("\tERROR MESSAGE: Empty File\n");
			return -1;
			break;
		case 2:
			dummyDecr(buffer, temp);
			return -1;
			break;			
	}
}
