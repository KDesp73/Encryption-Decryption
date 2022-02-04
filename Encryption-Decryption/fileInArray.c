#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fileInArray(char c, char array[][50])
{
int i=0, j=0;
FILE *fp;
fp=fopen("test.txt","r");
c=fgetc(fp);

//Emfanish periexomenou arxeiou
while(c!=EOF)
     {
     printf("%c", c);
     c=fgetc(fp);
     }
     
//Apo8hkeush periexomenou arxeiou se array kai emfanish ayths
while(fgets(array[i],50,fp))
     {
     array[i][strlen(array[i])]='\0';
     i++;
     }
j=i;
for(i=0; i<j; i++)
     printf("%s ", array[i]);
fclose(fp);
printf("\n");
}

int main()
{
char c, array[50][50];
fileInArray(c, array);
system("Pause");
return 0;	
}
