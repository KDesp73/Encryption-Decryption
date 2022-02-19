#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void revString(char string[], char revstr[]){
    for(int i = 0; i < strlen(string); i++){
        revstr[i] = string[strlen(string) - i - 1];
    }
    printf("\n");
}

void swap(char io[], int num, int size){
	while(size % num != 0){
		strcat(io, " ");
		size++;
	}
	
	int i,j;
	char temp;
	for(i=0; i<size/num; i+=num){
		for(j=0; j<num; j++){
			temp = io[j+i];
			io[i+j] = io[size - num + j - i]; 
			io[size - num + j - i] = temp;	
		}
	}

}

void swapInHalf(char string[]){
	char firstHalf[strlen(string)/2];
	char secondHalf[strlen(string)/2];
	
	int i;
	for(i=0;i<strlen(string)/2;i++){
		firstHalf[i] = string[i];
		secondHalf[i] = string[(strlen(string)/2)+i]; 
	}

	strcpy(string, strcat(secondHalf, firstHalf));
}

int main(){
	char revstr[20];
	char string[] = "abcdefghijklmnopqrstuvwxyz";
	printf("String: %s\n", string);
	swap(string, 2, 26);
	printf("Swapped string: %s\n", string);
	
	printf("Done\n");
	system("pause");
	return 0;
}
