#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void randomGarbage(char garbage[]){
	char randomBullshit[] = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
	
	int i;
	for(i=0; i < 10; i++){
		garbage[i] = randomBullshit[rand()%strlen(randomBullshit)];
	}
}

int main(){
	char garbage[10];
	srand(time(NULL));
	randomGarbage(garbage);
	printf("%s\n", garbage);
	
	system("pause");
	return 0;
}
