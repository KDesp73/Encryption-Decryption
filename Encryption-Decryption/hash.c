#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void getWholeFile(char file[], char buffer[]){
	memset(buffer, 0, strlen(buffer));
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



void hash(char array[], char chash[]){
	int max_now = 0;
	int now = 0;
	char strings[10][MAX/10];
	int hs[MAX/10];
	char string[10];
	int i ;
	int x = MAX/16;
	char iot[20];
	char temp_string[MAX] = "";
	char hs2[MAX/10];
	
	for(i=0;i<=MAX;i+=10){
		int h = array[i]+array[i+1]+array[i+2]+array[i+3]+array[i+4]+array[i+5]+array[i+6]+array[i+7]+array[i+8]+array[i+9];
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
	
	int k=0;
	char strr[20];
	for (i=strlen(temp_string);i>=strlen(temp_string)-8;i--){
		chash[k++]=temp_string[i];
	}
	//printf("\n\n%s\n\n",chash);
	
}

void main(int argc, char *argv[]){

		char filename[] = "h.txt";
		char HASH[300];
		char file[MAX];
			
		getWholeFile(argv[i],file);
		hash(file, HASH);
		printf("\n\nHASH : %s\n\nHash Len: %d\n\n",HASH,strlen(HASH));

	system("pause");
}
