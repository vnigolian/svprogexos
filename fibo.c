#include <stdio.h>
 
int demander_nombre(int min, int max);
int Fibonacci(int n);
int FibonacciIteratif(int n);
 
// ----------------------------------------------------------------------
int main()
{
  char rep;
 
  do {
    int n=demander_nombre(0, 40);
    printf("Méthode itérative :");
    printf("    F(%i) = %i\n",n,FibonacciIteratif(n));
    printf("Méthode récursive :");
    printf("    F(%i) = %i\n",n,Fibonacci(n));
 
    do {
		printf("Voulez-vous recommencer [o/n] ? ");
		scanf("%c",&rep);
    }while ((rep != 'o') && (rep != 'n'));
  }while (rep == 'o');
 
  return 0;
}
 
/* ----------------------------------------------------------------------
 * Calcule de façon itérative le n-ieme nombre de Fibonacci.
 * Entrée : le nombre n 
 * Sortie : F(n)
 * ---------------------------------------------------------------------- */
int FibonacciIteratif(int n)
{
  int Fn=0;    // stocke F(i)  , initialisé par F(0)
  int Fn_1=Fn; // stocke F(i-1), initialisé par F(0)
  int Fn_2=1;  // stocke F(i-2), initialisé par F(-1)
 
  for (int i=1; i <= n; ++i) {
    Fn   = Fn_1 + Fn_2;    // pour n>=1 on calcule F(n)=F(n-1)+F(n-2)
    Fn_2 = Fn_1;           // et on decale...
    Fn_1 = Fn;
  }
  return Fn;
}
 
/* ----------------------------------------------------------------------
 * Calcule de façon récursive le n-ieme nombre de Fibonacci.
 * Entrée : le nombre n 
 * Sortie : F(n)
 * ---------------------------------------------------------------------- */
int Fibonacci(int n)
{
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return Fibonacci(n-1) + Fibonacci(n-2);
}
 
/* --------------------------------------------------------------
 * fonction demandant à l'utilisateur un nombre compris
 * dans un intervalle [a, b], ou supérieur ou égal à a
 * si b < a.
 * Entrée : les deux nombres a et b définissant l'intervalle
 * Sortie : le nombre saisi par l'utilisateur
 * -------------------------------------------------------------- */
int demander_nombre(int a, int b)
{
    int res;
 
    do{
		printf("Entrez un nombre int ");
		if (a >= b){
			printf("supérieur ou égal à %i\n",a);
		}else{
				printf("compris entre %i et %i",a,b);
				printf("\n%i\n",scanf("%i",&res));
			
		}
    } while ((res < a) || ((a < b) && (res > b)));
 
   return res;
}

