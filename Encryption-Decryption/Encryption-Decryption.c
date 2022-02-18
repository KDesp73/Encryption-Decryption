
//Encryption - Decryption Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_array 50
#include <stdbool.h>
#include <float.h>

//Programm
int fcounter(char filename[50])
{
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

void fileinarray(char array[], char filename[50]){
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
	    array[counter] = c;
	    counter++;
	}
	
	fclose(fp);
}

//Menu

//Verify

//create key through hash

//create hash
int find_first_number(char string[]){
	int n = 16;//sizeof(string);
	printf("Size of string: %d\n",n);
	char numbers[] = "23456789";

	//int finall_num = 3;
	
	for (int i=0;i<n;i++){
		for (int j=0;j<=7;j++){
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
	
	for(int i=0;i<=100;i++){
		intlist[i] = 0;
	}

	int j;
	bool flag;
	
	for(int i=0;i<=counter;i++){
		j=0;
		flag = false;
		while(flag == false && j<=lcounter){
			
			if(array[i] == list[j]){
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
	
	for(int i=0;i<=lcounter;i++){
		printf("%c : %d\n",list[i],intlist[i]); // emfanizei poses fores emafanistike o kathe xaraktiras
		lsum += intlist[i];
	}
	
	double hash=0;
	double x;

	x = (double)lsum/(lsum-lcounter);
	if(counter<=2) x = 1.0000000000000000001;
	
	hash += x/(1+x);
	printf("\n\nBefore loop\nx = %lf\nHash = %lf\n",x,hash);	
	
	for(int i=0;i<=lcounter;i++){
		//hash += x/(1+exp(x*-1));
		hash += x/(1+x);
	}
	
	hash = fabs(hash);
	hash = hash*pow(10, 16);
	
	
	printf("\n\nx = %lf\nHash = %lf\n",x,hash);
    printf("\n\nFinal Hash = %.0lf\n\n",hash);

	snprintf(chash, 30, "%f", hash);
	chash[strcspn(chash, ".")] = 0;
	
	
	int pos1[] = {1,3,4,6,8,0};
	int pos2[] = {6,8,1,3,4,9};
	char swap;
	for(int i=0;i<7;i++){
		swap = chash[pos1[i]];
		chash[pos1[i]] = chash[pos2[i]];
		chash[pos2[i]] = swap;
	}
	printf("\n\nPreFinal Hash = %s\n\n",chash);
	
}

//Decryption

//Encryption
void program(char filename[]){
	int counter;
	//char filename[50];
	//strcpy(filename,"test.txt");
	 
	counter = fcounter(filename);
	char array[counter];
	fileinarray(array,filename);
	
	char Hash[30];
	
	//strcpy(Hash,hash(array, counter));
	hash(array, counter, Hash);
	printf("\nMain Final Hash = %s\n\n",Hash);
	printf("First Number in Hash: %d\n\n", find_first_number(Hash));
}

int main(){
	char filename[50];
	
	strcpy(filename,"test.txt");
	program(filename);
	
	/*printf("\n==========================================================\n");
	
	strcpy(filename,"test2.txt");
	program(filename);
	
	printf("\n==========================================================\n");
	
	strcpy(filename,"test3.txt");
	program(filename);*/
		
	system("pause");
}
