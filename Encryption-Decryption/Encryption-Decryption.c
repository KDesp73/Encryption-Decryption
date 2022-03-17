//Encryption - Decryption Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX 500

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
	//int maxSize = 200;//fcounter(file);
	
	size_t i;

	for (i = 0; i < MAX; ++i){
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

void hash(char array[], int counter, char HASH[]){
	char chash[20];
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
	int w,m;
	char t;
    for (int o = 0; o < 6; o++) {
    	
        w = pos2[o];
        m = pos1[o];
        
        t = chash[w];
        chash[w] = chash[m];
        chash[m] = t;
        
    }
	
	int mo;
	for(mo = 0; mo < 16; mo++){
		HASH[mo] = chash[mo];
	}
	
	printf("\n\nPreFinal Hash = %s\n\n",HASH);
	
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

void randomGarbage(char garbage[]){
	char randomBullshit[] = "0123456789ABCDEF";
	char num[] = "0123456789";

	int i;
	for(i=0; i < 10; ){
		garbage[i] = randomBullshit[rand()%strlen(randomBullshit)];
		if(checkLetter(garbage[i])){
			garbage[i+1] = num[rand()%strlen(num)];
			i++;
		}
		i++;
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
void stringToHex(char string[], char hex[]){
  	int len = strlen(string);

  	int i, j = 0;
	for (i = 0; i < len; ++i){
		sprintf(hex + j, "%02X", string[i] & 0xff);
		j += 2;
	}
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

void removeGarbage(char arr[], int sizeOfGar, int sizeOfHash){
	char arr1[MAX];
	int i, j = 0;
	for(i = sizeOfHash; i < strlen(arr) - sizeOfGar - 1; i++){
		arr1[j] = arr[i];
		j++;
	}
	strcpy(arr, arr1);
}
	
int fileSize(char contents[]){
	return strlen(contents);
}

int realFileSize(char contents[], int sizeofHash, int sizeofGarbage){
	return fileSize(contents) - sizeofHash - sizeofGarbage;
}
	
	//caesars cypher decrypt
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
	
	//char Hash[16];
	char Hash[] = "3333242532058932";
	//char Hash[] = "0123456789ABCDEF";
	char temp[counter];
	strcpy(temp, contents);
	//hash(temp, counter, Hash);
	printf("\nHash: %s\n", Hash);
	
	
	
	printf("\n==========================================================\n");
	printf("First Hash Num: %d\n", find_first_number(Hash));
	printf("Contents before swap: %s\n", contents);
	swap(contents, find_first_number(Hash)); //Dokimh
	printf("Contents after swap: %s", contents);
	
	printf("\n==========================================================\n");
	
	char hex[MAX];
	stringToHex(contents, hex);
	printf("Contents after hex: %s", hex);
	
	printf("\n==========================================================\n");
	
	caesarsCypherEncr(hex, find_first_number(Hash)); //Dokimh
	printf("Contents after caesars: %s", hex);
	printf("\n==========================================================\n");
	
	char garbage[10], finalForm[MAX];
	randomGarbage(garbage);
	allinone(finalForm, Hash, hex, garbage);
	printf("Final form: %s", finalForm);
	printf("\n==========================================================\n");
	
	
	writefile(finalForm, "ogencryptedfile.txt");
	
}

void decryption(char file[]){	
	char temp[MAX];
	getWholeFile(file, temp);
	int size = strlen(temp);
	char encrCont[size];
	strcpy(encrCont, temp);
	
	char Hash[16];
	getHashFromFile(file, Hash, 16);
	printf("Hash: %s\n", Hash);
	
	//char e1[size-26];
	removeGarbage(encrCont, 10, 16);
	printf("Contents after removal: %s", encrCont);
	
	printf("\n\nFind num: %d\n\n", find_first_number(Hash));
	caesarsCypherDecr(encrCont, find_first_number(Hash));
	printf("\n\nContents after caesars: %s", encrCont);
	
	hexToString(encrCont);
	//stringToHex(encrCont, encrCont);
	printf("\n\nContents after hex: %s", encrCont);
	
	swap(encrCont, find_first_number(Hash));
	printf("\n\nContents after swap: %s", encrCont);
	
	/*char filename[50];
	printf("Give the name of the file: ");
	scanf("%s", filename);*/
	writefile(encrCont, "newFile.txt");
	
}

//Menu
void mainMenu(){
	char file[30];
	askFile(file);
	
	//printf("\n-Main Menu-\n");
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
			encryption(file);
			break;
		case 2:
			decryption("ogencryptedfile.txt");
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
	
	
	
	//mainMenu();
	char file[30];
	askFile(file);
	encryption(file);
	decryption("ogencryptedfile.txt");
	printf("\n\n\n");
	


	
	system("pause");
	return 0;
}
