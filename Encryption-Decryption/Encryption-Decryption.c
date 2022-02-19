//Encryption - Decryption Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX 500

//Get file
int fcounter(char filename[50]){
	char c;
	int i=0, j=0;
	FILE *fp;
	fp=fopen(filename,"r");
	c=fgetc(fp);
	int counter =0;
	
	//Emfanish periexomenou arxeiou
	while(c!=EOF)
	{
	    //printf("%c", c);
	    c=fgetc(fp);
	    counter++;
	}
	
	fclose(fp);
	return counter;
}

void getWholeFile(char file[], char buffer[]){
	FILE *fp;
    fp = fopen(file, "rb");
	int maxSize = 200;//fcounter(file);
	
	size_t i;

	for (i = 0; i < maxSize; ++i){
    	int c = getc(fp);
    	
    	if (c == EOF){
        	buffer[i] = 0x00;
        	break;
    	}
    	
    	buffer[i] = c; //Pairnei olo to arxeio mazi me hash kai skoypidia
	}
	
    fclose(fp);
}

//create hash
int find_first_number(char string[]){
	int n = 16;//sizeof(string);
	//printf("Size of string: %d\n",n);
	char numbers[] = "23456789";

	//int finall_num = 3;
	int i,j;
	for(i=0;i<n;i++){
		for (j=0;j<=7;j++){
			if(numbers[j] == string[i]){
				//printf("num: %c, str: %c\n",numbers[j], string[i]);
				return j+2;
			}
		}
	}
}

void hash(char array[], int counter, char chash[]){
	char list[100];
	int intlist[100];
	int lcounter=0;
	
	int i;
	for(i=0;i<=100;i++){
		intlist[i] = 0;
	}

	int j;
	bool flag;
	
	int h;
	for(h=0;h<=counter;h++){
		j=0;
		flag = false;
		while(flag == false && j<=lcounter){
			
			if(array[h] == list[j]){
				intlist[j] += 1;
				flag = true;
			}
			j++;
		}
		if(flag == false){
			list[lcounter] = array[i];
			intlist[lcounter] += 1;
			lcounter++;
		}
	}
	
	int lsum=0;
	
	int k;
	for(k=0;k<=lcounter;k++){
		//printf("%c : %d\n",list[i],intlist[i]); // emfanizei poses fores emafanistike o kathe xaraktiras
		lsum += intlist[k];
	}
	
	double hash=0;
	double x;

	x = (double)lsum/(lsum-lcounter);
	if(counter<=2) x = 1.0000000000000000001;
	
	hash += x/(1+x);
	//printf("\n\nBefore loop\nx = %lf\nHash = %lf\n",x,hash);	
	
	int a;
	for(a=0;a<=lcounter;a++){
		//hash += x/(1+exp(x*-1));
		hash += x/(1+x);
	}
	
	hash = fabs(hash);
	hash = hash*pow(10, 16);
	
	
	//printf("\n\nx = %lf\nHash = %lf\n",x,hash);
    //printf("\n\nFinal Hash = %.0lf\n\n",hash);

	snprintf(chash, 30, "%f", hash);
	chash[strcspn(chash, ".")] = 0;
	
	
	int pos1[] = {1,3,4,6,8,0};
	int pos2[] = {6,8,1,3,4,9};
	char swap;
	
	int b;
	for(b=0;b<7;b++){
		swap = chash[pos1[b]];
		chash[pos1[b]] = chash[pos2[b]];
		chash[pos2[b]] = swap;
	}
	//printf("\n\nPreFinal Hash = %s\n\n",chash);	
	
}

void randomGarbage(char garbage[]){
	char randomBullshit[] = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
	
	int i;
	for(i=0; i < 10; i++){
		garbage[i] = randomBullshit[rand()%strlen(randomBullshit)];
	}
}

//Put hash in file
void allinone(char finalarray[], char hash[], char ogArray[], char garbage[]){
	strcpy(finalarray, "");
	strcat(finalarray, hash);
	strcat(finalarray, ogArray);
	strcat(finalarray, garbage);
}

//Encryption
	//Giants function
void swap(char io[], int num, int size){
	while(size % num != 0){
		strcat(io, " ");
		size++;
	}
	printf("Contents 0: %s\n", io);
	int i,j;
	char temp;
	for(i=0; i<size/num; i+=num){
		for(j=0; j<num; j++){
			temp = io[j+i];
			io[i+j] = io[size - num + j - i]; 
			io[size - num + j - i] = temp;	
		}
	}
	printf("Contents 1: %s\n", io);
}
	
	//Hex
void stringToHex(char string[], char hex[]){
  	int len = strlen(string);

  	int i, j = 0;
	for (i = 0; i < len; ++i){
		sprintf(hex + j, "%02X", string[i] & 0xff);
		j += 2;
	}
}

	//caesars cypher
void caesarsCypherEncr(char io[], int num){ //io -> input / output
	char hexChars[] = "0123456789ABCDEF";
	
	int i, j;
    for (i = 0; i < strlen(io); i++){
        for (j = 0; j < strlen(io);){  //Psaxnei ton characthra sto hexChars
            while (io[i] != hexChars[j]){        	
				j++;
            }
            break;
        }
        
        if(j + num >= strlen(hexChars)){  //Gia otan einai sto telos tou string, na phgainei apo thn arxh
            j -= strlen(hexChars);
            io[i] = hexChars[j + num];
        }
        //else if()
        else{
            io[i] = hexChars[j + num];
            j = 0;
        }
    }
}
	
	
//Decryption
	//Get Hash
void getHashFromFile(char file[], char hash[], int sizeofHash){
	FILE *fp;
	fp = fopen(file, "r");
	
	if (fp == NULL) {
        printf("File can't be opened\n");
    }
	
	fgets(hash, sizeofHash+1, fp); //Pairnei tous 1ous 64 xarakthres
   
   fclose(fp);
}
	
int fileSize(char contents[]){
	return strlen(contents);
}

int realFileSize(char contents[], int sizeofHash, int sizeofGarbage){
	return fileSize(contents) - sizeofHash - sizeofGarbage;
}

void createRealFile(char newFileName[], char ogFileContents[], int sizeofHash, int sizeofGarbage, int sizeofFile, int sizeofRealFile){
	FILE *nfp = fopen(newFileName, "w+");
	
	char newFileContents[MAX];
	
	int i,j=0;
	for(i = sizeofHash; i < sizeofFile - sizeofGarbage; i++){
		newFileContents[j] = ogFileContents[i];
		j++;
	}
	
	printf("\n\nNew Contents: %s", newFileContents);
	fputs(newFileContents, nfp); //Bazei mono to alhthino periexomeno se ena neo arxeio wste na ginei to Decryption
	
	fclose(nfp);
}
	
	//caesars cypher decrypt
void caesarsCypherDecr(char io[], int num){ //io -> input / output
	char hexChars[] = {"0123456789ABCDEF"};
	
	int i, j;
    for (i = 0; i < strlen(io); i++){
        for (j = 0; j < strlen(io);){  //Psaxnei ton characthra sto hexChars
            while (io[i] != hexChars[j]){
                j++;
    		}
            break;
        }
        
        if(j < num){  //Gia otan einai sthn arxh tou string, na phgainei sto telos
            j += strlen(hexChars);
            io[i] = hexChars[j - num];
        }
        else{
            io[i] = hexChars[j - num];
            j = 0;
        }
    }
}
	
	//Hex decrypt
void hexToString(char string[], char hex[]){
	int len = strlen(hex);
  	
  	int i=0, j=0;
	for (j = 0; j < len; j += 2) {
    	int val[1];
    	sscanf(hex + j, "%2X", val);
    	string[i] = val[0];
    	string[i + 1] = '\0';
    	++i;
  	}
}
	
	//Giants function decrypt


//Verify
bool stringsSame(char str1[], char str2[]){
	if(strcmp(str1, str2) == 0)
		return true;
	else
		return false;
}

void verify(char hash1[], char hash2[]){
	if(stringsSame(hash1, hash2)){
		printf("Decryption completed properly\n");
	}
	else
		printf("Decryption was not completed properly\n");
}

void writefile(char array[], char filename[]){
		FILE *fp;
		fp = fopen(filename, "w+");
		fputs(array, fp);
		fclose(fp);
	}


void encryption(char file[]){
	int counter = fcounter(file) + 8;
	char contents[counter];
	printf("0\n");
	getWholeFile(file, contents);
	printf("Contents: %s\n", contents);
	printf("1\n");
	
	char Hash[16];
	char temp[counter];
	strcpy(temp, contents);
	//hash(temp, MAX, Hash);
	printf("\nHash: %s\n", Hash);
	//printf("%s", find_first_number(Hash));
	
	printf("\n==========================================================\n");
	
	printf("Contents before swap: %s\n", contents);
	swap(contents, 2, 26); //Dokimh
	printf("Contents after swap: %s", contents);
	
	printf("\n==========================================================\n");
	
	char hex[100];
	stringToHex(contents, hex);
	printf("Contents after hex: %s", hex);
	
	printf("\n==========================================================\n");
	
	caesarsCypherEncr(hex, 2); //Dokimh
	printf("Contents after caesars: %s", hex);
	printf("\n==========================================================\n");
	
	char garbage[10], finalForm[200];
	randomGarbage(garbage);
	allinone(finalForm, Hash, hex, garbage);
	printf("Final form: %s", finalForm);
	printf("\n==========================================================\n");
	
	writefile(finalForm, "ogencryptedfile.txt");
}

//Menu
void mainMenu(){
	printf("\n-Main Menu-\n");
	printf("1. Encrypt\n");
	printf("2. Decrypt\n");
	printf("3. Exit\n");
	
	
	int choice;
	do{
		printf("> ");
		scanf("%d", choice);
	}
	while(choice < 1 || choice > 3);
	
	switch(choice){
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			printf("\n\nBye!\n\n");
			system("pause");
			exit(0);
			break;
	}
}


//Programm

int main(){
	/*
	-Encryption-
	file -> Onoma arxeiou gia encryption
	counter -> Arithmos xarakthrwn sto parapanw arxeio
	Hash -> Hash pou dhmiourgeitai sto encryption
	garbage ->Skoupidia sto telos tou arxeiou
	
	-Decryption-
	encrContents -> Arxika periexomena tou encrypted arxeiou me hash kai skoupidia
	realHash -> Hash pou pairnoume apo to encrypted arxeio prin arxisei h diadikasia tou decryption
	stringToFinalDecr -> String gia thn telikh decryption sunarthsh
	hashToComp -> H hash pou dhmioyrgeitai meta to decryption wste na ginei to verify
	finalcontents -> Decrypred array
	decryptedFile -> Decrypred file
	*/
	
	
	srand(time(NULL));
	char file[30];
	
	//printf("Give the name of the file: ");
	//scanf("%s", file);
	encryption("file.txt");
	
	printf("\n==========================================================\n");
	//Decryption
	/*char encrContents[counter+26];
	char realHash;
	
	getHashFromFile("ogencryptedfile.txt", realHash, 16);
	printf("Hash: %s", realHash);
	
	getWholeFile("ogencryptedfile.txt", encrContents);
	printf("\n\nContents: %s", encrContents);
	
	createRealFile("encryptedFile.txt", encrContents, 16, 10, fileSize(encrContents), realFileSize(encrContents, 16, 10));
	
	//Caesars cypher Decrypt
	caesarsCypherDecr(encrContents, find_first_number(realHash));
	
	//Hex Decrypt
	hexToString(stringToFinalDecr, encrContents);
	
	//Giants Decrypt
	
	
	//Generate Hash
	char hashToComp[];
	hash(finalcontents, MAX, hashToComp);
	
	//Verify
	verify(realHash, hashToComp);
	
	//Create decrypted file
	writefile(finalcontents, decryptedFile);*/
	
	system("pause");
	return 0;
}
