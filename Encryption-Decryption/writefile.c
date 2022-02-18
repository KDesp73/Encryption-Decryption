
//Encryption - Decryption Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

void writefile(char array[], char filename[]){
	FILE *fp;
	fp = fopen(filename, "w+");
	fputs(array, fp);
	fclose(fp);
}

int main(){
	system("pause");
}
