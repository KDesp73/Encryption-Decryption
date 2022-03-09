#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Encryption
/*
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
}*/

int f(int x, int y){
	return x*y+x+y;
}

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

int main(){
	char string[10];
	int num;
	
	
	
	printf("Give num: ");
	scanf("%d", &num);
	
	printf("\n-Encryption-\n");
	printf("Give string: ");
	scanf("%s", string);
	caesarsCypherEncr(string, num);
	printf("%s", string);
	printf("\n\n");
	
	
	
	printf("\n-Decryption-\n");
	printf("Give string: ");
	scanf("%s", string);
	caesarsCypherDecr(string, num);
	printf("%s", string);
	printf("\n\n");
	
	
	system("pause");
	return 0;
}
