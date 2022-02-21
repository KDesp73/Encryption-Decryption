#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Pithana mellontika bugs:
//messageLength < 2
// hashNum < 2 || hashNum > 9
// hashNum > messageLength

void swapKout (char P[], int n1, int n2, int hashN)
{
    char temp;
    while (n1 < n2)
	{
	    temp = P[n2]; 
	    P[n2] = P[n1];
	    P[n1] = temp;
	    n2--;
	    n1++;
    }
}

void swap (char P[], int hashN)
{
	int messageL = strlen(P);
	int repeats = messageL / hashN;	
	
	if (messageL % hashN == 0 || messageL % hashN == 1)
	{
		int n1 = 0;
	    int n2 = hashN - 1;
	    int counter = 0;
	do
	{
		swapKout(P, n1, n2, hashN);
		n1 = n1 + hashN;
		n2 = n2 + hashN;
		counter++;
	}
	while (counter < repeats);
    }
	
	else
	{
		int n1 = 0;
	    int n2 = hashN - 1;
	    int counter = 0;
	do
	{
		swapKout(P, n1, n2, hashN);
		n1 = n1 + hashN;
		n2 = n2 + hashN;
		counter++;
	}
	while (counter < repeats);
	n2 = messageL - 1;
	swapKout (P, n1, n2, messageL % hashN);
	}
}

main()//
{
	char P[50] = {"012345678abcdefghijk"};
	
	printf("Array before swap: %s\n", P);
	
	int hashN = 9;
	
	swap(P, hashN);
	
	printf("Array after swap: %s\n", P);
	
system("Pause");
}
