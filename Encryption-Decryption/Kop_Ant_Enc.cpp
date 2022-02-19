#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define nmax 10

//void Kop_Ant_Enc (char Hash[], int hashN, )

void swapP(char P[][nmax], int n1, int n2)
{
	int i = 0;
	int k = n2 - 1;
	char temp;
	int m = n2 / 2;
	
	do
	{
	    temp = P[n1][k];
	    P[n1][k] = P[n1][i];
	    P[n1][i] = temp;
	    k--;
	    i++;
	}
	while (i != m);
}

void swapSeira (char P[][nmax], int i, int k)
{
	char temp[nmax];
	strcpy(temp, P[k]);
	strcpy(P[k], P[i]);
	strcpy(P[i], temp);	
}

main()//Sinartisi kyria
{
	char Minima[150] = {"123456789101112131415161718192"}; //
	int minimaL = strlen(Minima);
	printf("%d \n", minimaL); // 
	printf("%s", Minima);//
	
	int hashN = 5; //
	
	if (minimaL % hashN == 0) //An den yparxoyn kena
	{
		int n1 = minimaL / hashN; //Dimiourgia Pinaka-Egrastirio
		printf("%d", n1);//
		int n2 = hashN;
		printf("%d", n2);//
		char P[n1][nmax];
		
		int i, k, z = 0; //Gemisma P me Minima
		for (i = 0; i <= n1-1; i++)
        {
        	for (k = 0; k <= n2 - 1; k++)
        	{
        	P[i][k] = Minima[z];
        	z++;
            }
		}
		 printf("\n");//
	    for (i = 0; i <= n1-1; i++)//
	    {
		printf("%s\n", P[i]);//
	    }
		
		int l;
		for (i = 0; i <= n1-1; i++)
	    {
		l = strlen(P[i]);
		swapP (P, i, l);
	    }
	    
	    printf("\n");//
	    for (i = 0; i <= n1-1; i++)//
	    {
		printf("%s\n", P[i]);//
	    }
		
		if (n1 > 2)
		{
			i = 0;
			k = 2;
		    l = n1 / 2;
		    int counter = 0;
		    do
		    {
			swapSeira(P, i, k);
			i++;
			k++;
			counter++;
		    }
		    while (counter != l);
	    }
	    
	    else
	    {
	    	i = 0;
	    	k = 1;
	    	swapSeira(P, i, k);
		}
		
		printf("\n");//
	    for (i = 0; i <= n1-1; i++)//
	    {
		printf("%s\n", P[i]);//
	    }
	}
	
system("Pause");
}
