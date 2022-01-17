
//Encryption - Decryption Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Programm

//Menu

//Verify

//create key through hash

//create hash


//Decryption

//Encryption

int main(){
	int ac_d = 30;
	char afilename[50] = "h.txt";

	printf("file: %s\n", afilename);
	
	char c;
	int counter = 0;
	FILE *fptr;
	fptr = fopen(afilename, "rb");

	// Open file
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
	printf("1\n");
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
    	counter += 1;
    	
        //printf ("|%d",(int) c);
        //char str[strlen(c);]
        c = fgetc(fptr);
    }
    
    printf("%d", counter);
    int str[counter];
    //int loi[counter];
    printf("2\n");
    int c2=0;
    
    
    for (int i=0;i<=counter;i++){
    	str[i] = 0;
	}
    
    printf("3\n");
    fclose(fptr);
    fptr = fopen("pass.py", "rb");
    
    c = fgetc(fptr);
    while (c != EOF)
    {
    	str[c2] = (int) c;
        //printf ("|%d",str[c2]);
        //char str[strlen(c);]
        c = fgetc(fptr);
        c2 += 1;
    }
    fclose(fptr);
    
    int c_d = ac_d;
    
    int fvl = counter/c_d;
    int fv[fvl], fvc=0;
	//printf("%d\n",fvl);
    
    
    for (int i=0;i<=(fvl)-1;i+=1){
    	
    	fv[i] = 0;
    	if (i==0){
		
    		for (int k=0;k<=c_d;k++){
    			fv[i] += str[i+k];
			}
		}else{
			fv[i] += fv[i-1];
			for (int k=0;k<=c_d;k++){
    			fv[i] += str[i+k];
			}
		}
		//printf("%d\n",fv[i]);

	}
	printf("4\n");
	
	//fv -> fvl
	int ti=0;
	for (int i=0;i<=fvl-1;i++){
		printf("-----------");
		printf("5%d\n",i);
		while (fv[i] > 250){
			ti = fv[i]%10;
			if(ti==0){
				fv[i] = (fv[i]/10)-1;
			}else{
			
				fv[i] = (fv[i]/10)+ti;
			}
			//printf("%d\n",fv[i]);
		}
	}
	
	for (int i=0;i<=fvl-1;i++){
		printf("%c",(char)fv[i]);
	}
	printf("\n");
    
  
    fclose(fptr);
	
	system("pause");
	return 0;
}
