#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>


#include "Auxiliary_functions.c"

#define MAX 1000
#define HASHSIZE 8
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

//Auxiliary functions
void getTextFILE();
void getTextSTRING();

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
void chooseOutput(char out[], char msg[]){
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
			writeFile(out, filename);
			break;
		case 2:
			printf("%s Text:\n%s", msg, out);
			break;
		case 3:
			printf("%s Text:\n%s\n", msg, out);
			askFile(filename);
			writeFile(out, filename);
			break;
		default:
			printf("OUTPUT -> DO-WHILE -> CHOICE");
			exit(1);
	}
	memset(filename, 0, strlen(filename));
}

void menu(char _encr[], char _decr[]){
	printf("\n\n\t\t::::Menu::::\n");
	printf("\tSelect [1]Encryption [2]Decryption\n\t       [3]About [4]Exit\n");
	int choice;
	do{
		printf("\t> ");
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
			printf("WTF");
	}
}

//========MAIN========
int main(){
	srand(time(NULL));
	char _encr[MAX];
	char _decr[MAX];

	printf("=============ENCRYPTION-DECRYPTION=============\n\n");
	menu(_encr, _decr);


	system("pause");
	return 0;
}
//========END OF MAIN========


int createHash(char buffer[]){
	return 11111112;
}


void encr(char buffer[], char _encrypted[]){
	printf("\n=======Encryption=======\n");
	memset(buffer, 0, strlen(buffer));
	chooseInput(buffer);
	//printf("\nInitial text:\n%s\n", buffer);

	int HASH = createHash(buffer);
	//printf("HASH NUM: %d", hashNum(HASH));
	swap(buffer, hashNum(HASH));
	//printf("\nSwap text: %s\n", buffer);

	s2h(buffer);
	//printf("\nHex text: %s\n", buffer);

	ccEncr(buffer, hashNum(HASH));
	//printf("\nCCE text: %s\n", buffer);

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
	//printf("\nCCD text: %s\n", buffer);

	h2s(buffer);
	//printf("\nHEX: %s", buffer);

	swap(buffer, hashNum(HASH));
	//printf("\nSwap: %s", buffer);

	//Generate hash
	//Validate
	memset(_decrypted, 0, MAX);
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


void getTextFILE(char buffer[]){
	char filename[100];
	
	do{
		askFile(filename);
		
		if(access(filename, F_OK) != 0)
			printf("File does not exist\n\n");
	}
	while(access(filename, F_OK) != 0); //checks if file exists
	
	
	getFile(filename, buffer);
}


void getTextSTRING(char buffer[]){
	char temp[MAX];
	memset(temp, 0, MAX);
	do{
		memset(temp, 0, strlen(temp)); //Empty array
		printf("Give text: ");
		fgets(temp, MAX, stdin);
	}
	while(!checkInput(temp));

	strncpy(buffer, temp, strlen(temp));
}
