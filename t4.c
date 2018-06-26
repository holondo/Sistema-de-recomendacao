#include <stdio.h>
#include <stdlib.h>

typedef struct _numeros
{
    int numerador, denominador;
}NUMEROS;

void swap(NUMEROS** coef, int neq, int ncoef, int lin, int col)
{
    NUMEROS coefaux[ncoef];
    int tester = lin;
    
	if(coef[lin][col].numerador == 0)
	{
		for(int i = 0; i < ncoef; i++)
		{
			coefaux[i].numerador = coef[lin][i].numerador;
			coefaux[i].denominador = coef[lin][i].denominador;
		}
		
		while(coef[tester][col].numerador == 0 && tester < neq-1 )
		{
			tester = tester+1;
		}

		for(int i = 0; i < ncoef; i++)
		{
			coef[lin][i].numerador = coef[tester][i].numerador;
			coef[lin][i].denominador = coef[tester][i].denominador;
			
			coef[tester][i].numerador = coefaux[i].numerador;
			coef[tester][i].denominador = coefaux[i].denominador;
		}
	}
    return;
}

int func_mmc(NUMEROS** coef, NUMEROS * aux, int na, int nb, int j)
{
   long int mmc;
   if(coef[na][j].denominador >= aux[j].denominador)
   { 
       mmc = coef[na][j].denominador;
   }
   if( coef[na][j].denominador < aux[j].denominador )
   {
       mmc = aux[j].denominador;
   }
   while( (mmc%coef[na][j].denominador) != 0 || (mmc%aux[j].denominador) != 0)
   {
       mmc++;
   }
   
   return mmc;
}



int main()
{
    int neq, ncoef;
    scanf("%d %d", &neq, &ncoef);
    char tipo1;
    scanf(" %c", &tipo1);
    //tipo1 = getchar();
    
    NUMEROS** coef = malloc(neq*sizeof(NUMEROS));
    NUMEROS** coefaux = malloc(neq*sizeof(NUMEROS));
    
    for(int i = 0; i < neq; i++)
    {
        coef[i] = malloc(ncoef*sizeof(NUMEROS));
        coefaux[i] = malloc(ncoef*sizeof(NUMEROS));
    }
    
    if(tipo1 == 'p')
    {
        for(int i = 0; i < ncoef; i++)
        {
            scanf("%d %d", &coef[0][i].numerador, &coef[0][i].denominador);
        }
        
        char tipo2;
        scanf(" %c", &tipo2);
        
        if(tipo2 == 'p')
        {
            for(int i = 0; i < ncoef; i++)
            {
                scanf("%d %d", &coef[1][i].numerador, &coef[1][i].denominador);
            }
        }
        
        if(tipo2 == 'r')
        {
            for(int i = 1; i < 2; i++)
            {
                for(int j = 0; j < ncoef; j++)
                {
                    scanf("%d %d", &coef[i][j].numerador, &coef[i][j].denominador);
                }
            }
        }
    }
    
    if(tipo1 == 'r')
    {
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < ncoef; j++)
            {
                scanf("%d %d", &coef[i][j].numerador, &coef[i][j].denominador);
            }
        }
        
        char tipo2;
        scanf(" %c", &tipo2);
        
        if(tipo2 == 'p')
        {
            for(int i = 0; i < ncoef; i++)
            {
                scanf("%d %d", &coef[2][i].numerador, &coef[2][i].denominador);
            }
        }
        
        if(tipo2 == 'r')
        {
            for(int i = 2; i < 3; i++)
            {
                for(int j = 0; j < ncoef; j++)
                {
                    scanf("%d %d", &coef[i][j].numerador, &coef[i][j].denominador);
                }
            }
        }
    }
//printf("%d %d %d %d ",coef[0][0].numerador, coef[0][1].numerador, coef[0][2].numerador, coef[0][3].numerador);
// swap
		
		//aqui vai um for pra fazer swap, mmc, subtraC'C#orecursiva
        for(int i = 0; i < neq-1; i++)
        {
            int tester = i+1;
            long int mmc = 0;
            swap(coef, neq, ncoef, i, i);
            
            while(coef[tester][i].numerador == 0 && tester < neq)
    		{
    			tester = tester+1;
    		}
    		
    		NUMEROS aux[ncoef], fator;
    		fator.numerador = coef[tester][i].numerador * coef[i][i].denominador;
    		fator.denominador = coef[tester][i].denominador * coef[i][i].numerador;
    		
    		for(int j = 0; j < ncoef; j++)
    		{
    		    aux[j].numerador = coef[i][j].numerador * fator.numerador;
    		    aux[j].denominador = coef[i][j].denominador * fator.denominador;
    		    printf("%d/%d", aux[j].numerador, aux[j].denominador);
    		}
    		printf("\n");
    		for(int j = 0; j < ncoef; j++)
    		{
                mmc = func_mmc(coef, aux, i, tester, j);
                coef[tester][j].denominador = (mmc);
                printf("mmc:%ld", mmc);
                coef[tester][j].numerador = ((coef[tester][j].denominador/mmc) * coef[tester][j].numerador);
                coef[tester][j].numerador -= ((coef[i][j].denominador/mmc) * coef[i][j].numerador);
    		}
        }
        
        
        for (int i = 0; i < neq; i++)
        {
    		if(coef[i][0].numerador == 0 && coef[i][1].numerador == 0 && coef[i][2].numerador == 0 && coef[i][3].numerador != 0)
    		{
    		    printf("nao\n");
    		    break;
    		}
    		else if(i == neq-1)
    		    {
    		        printf("sim\n");
    		    }
        }
        
        for (int i = 0; i < neq; i++)
        {
            for(int j = 0; j < ncoef; j++)
            {
                if(coef[i][j].numerador%coef[i][j].denominador == 0)
                {
                    coef[i][j].numerador /=coef[i][j].denominador;
                    coef[i][j].denominador/= coef[i][j].denominador;
                }
                if(coef[i][j].denominador == 1 && j == ncoef-1)
                {
                    printf("%d",coef[i][j].numerador);
                }
                if(coef[i][j].denominador == 1 && j < ncoef-1)
                {
                    printf("%d\t",coef[i][j].numerador);
                }
                
                if(coef[i][j].denominador != 1 && j == ncoef-1)
                {
                    printf("%d/%d", coef[i][j].numerador, coef[i][j].denominador);
                }
                if(coef[i][j].denominador != 1 && j < ncoef-1)
                {
                    printf("%d/%d\t", coef[i][j].numerador, coef[i][j].denominador);
                }
            }
            printf("\n");
        }
    return 0;
}
//dar fri
