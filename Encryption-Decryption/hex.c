#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Convert text to hex
void stringToHex(char string[], char hex[]){
  	int len = strlen(string);

  	int i, j = 0;
	for (i = 0; i < len; ++i){
		sprintf(hex + j, "%02x", string[i] & 0xff);
		j += 2;
	}
}

//Convert hex to text
void hexToString(char string[], char hex[]){
	int len = strlen(hex);
  	
  	int i=0, j=0;
	for (j = 0; j < len; j += 2) {
    	int val[1];
    	sscanf(hex + j, "%2x", val);
    	string[i] = val[0];
    	string[i + 1] = '\0';
    	++i;
  	}
}

int main(){
	char hex[20], string[20];
	
	printf("Give string: ");
	scanf("%s", string);
	stringToHex(string, hex);
	printf("'%s' in hex is %s\n", string, hex);
	
	printf("Give hex: ");
	scanf("%s", hex);
	hexToString(string, hex);
	printf("%s as a string is '%s'\n", hex, string);
	system("pause");
	return 0;
}
