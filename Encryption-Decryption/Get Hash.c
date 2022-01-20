#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//WORKS
void getHashFromFile(char file[], char hash[], int sizeofHash){
	FILE *fp;
	fp = fopen(file, "r");
	
	if (fp == NULL) {
        printf("File can't be opened\n");
    }
	
	fgets(hash, sizeofHash+1, fp); //Pairnei tous 1ous 64 xarakthres
   
   fclose(fp);
}

//WORKS
void getWholeFile(char file[], char buffer[], int maxSize){
	FILE *fp;
    fp = fopen(file, "rb");
	
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

//WORKS
int wholeFileSize(char contents[]){
	return strlen(contents);
}

//WORKS
int realFileSize(char contents[], int sizeofHash, int sizeofGarbage){
	return wholeFileSize(contents) - sizeofHash - sizeofGarbage;
}

//WORKS
void createRealFile(char newFileName[], char ogFileContents[], int sizeofHash, int sizeofGarbage, int sizeofFile, int sizeofRealFile){
	FILE *nfp = fopen(newFileName, "w+");
	
	char newFileContents[200];
	
	int i,j=0;
	for(i = sizeofHash; i < sizeofFile - sizeofGarbage; i++){
		newFileContents[j] = ogFileContents[i];
		j++;
	}
	
	fputs(newFileContents, nfp); //Bazei mono to alhthino periexomeno se ena neo arxeio wste na ginei to Decryption
	
	fclose(nfp);
}

int main(){
	char hash[64];
	char contents[200];
	
	getHashFromFile("file.txt", hash, 64);
	printf("Hash: %s", hash);
	
	getWholeFile("file.txt", contents, 200);
	printf("\n\nContents: %s", contents);
	
	createRealFile("newFile.txt", contents, 64, 10, wholeFileSize(contents), realFileSize(contents, 64, 10));
	
		
	printf("\n\n");
	system("pause");
	return 0;
}
