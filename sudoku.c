#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>

int icur=0, jcur=0;

void affichage (int grille[9][9])
{
    int i,j;
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
		{
		  printf(i==icur && j==jcur?"<%d>":" %d ",grille[i][j]);
		  if(j%3==2) printf("|");
    	}
        putchar('\n');
        if (!((i+1)%3)) puts("------------------------------");
    }
    puts("\n\n");
}


int ligne (int k, int grille[9][9], int i,int j)
{
    for (j=0;j<9;j++)
        if (grille[i][j] == k)
            return 0;
    return 1;
}


int colonne (int k, int grille[9][9],int i, int j)
{
    for (i=0;i<9;i++)
        if (grille[i][j] == k)
            return 0;
    return 1;
}


int bloc (int k, int grille[9][9], int i, int j)
{
    int x, y;
    x=3*(i/3), y=3*(j/3);
    for (i=x;i<x+3; i++)
        for (j=y;j<y+3;j++)
            if (grille[i][j] == k)
                return 0;
    return 1;
}

int remplir(int grille[9][9], int pos)
{
    int i,j,k;
    if (pos == 9*9)
        return 1;
    i = pos/9 , j = pos%9;
    if (grille[i][j]!= 0)
        return remplir(grille, pos+1);
    for (k=1;k<=9;k++)
    {
        if (ligne(k,grille,i,j)==1 && colonne(k,grille,i,j)==1 && bloc(k,grille,i,j)==1)
        {
            grille[i][j] = k;
            if (remplir(grille, pos+1))
                return 1;
        }
    }
    grille[i][j] = 0;
    return 0;
}

void copie(int grille[9][9], int grillee[9][9])
{
    int i,j;
   	for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            {
                grille[i][j] = grillee[i][j];
            }
}


int main()
{
    int i,j,k;
	int resolver[9][9];

    int grille[9][9] =
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };

    printf("\n\n Jouer \n\n");
    do
    {
       affichage(grille);
    	char c = getchar();
    	switch(c)
    	{ case '1'...'9': grille[icur][jcur]=c-'0'; break;
            
            case 'y': case'Y': if(icur>0) icur--; break;
            case 'g': case'G': if(jcur>0) jcur--; break;
            case 'h': case'H': if(jcur<8) jcur++; break;
            case 'b': case'B': if(icur<8) icur++; break;

       }
       if(c=='m')
	   {
               copie(resolver,grille);
	   }
       if(c=='r')
       {
       copie(resolver,grille);
       if(remplir(grille,0)==1){
            printf("Il y a une solution\n");
       }
       }
    }
while(1);
    system("PAUSE");
    return 0;
}

