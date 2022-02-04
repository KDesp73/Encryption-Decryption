#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fileInArray(char c, char line[][50])
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
while(fgets(line[i],50,fp))
     {
     line[i][strlen(line[i])]='\0';
     i++;
	 }
j=i;
for(i=0; i<j; i++)
     printf("%s ", line[i]);
fclose(fp);
printf("\n");
}

int main()
{
char c, line[50][50];
fileInArray(c, line);
system("Pause");
return 0;	
}
