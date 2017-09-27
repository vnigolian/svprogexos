#include <iostream>
#include <limits>
#include <string>
using namespace std;
 
int demander_nombre(int min, int max);
int Fibonacci(int n);
int FibonacciIteratif(int n);
 
// ----------------------------------------------------------------------
int main()
{
  char rep;
 
  do {
    int n(demander_nombre(0, 40));
    cout << "Méthode itérative :" << endl;
    cout << "    F(" << n << ") = " << FibonacciIteratif(n)
         << endl;
    cout << "Méthode récursive :" << endl;
    cout << "    F(" << n << ") = " << Fibonacci(n) << endl;
 
    do {
      cout << "Voulez-vous recommencer [o/n] ? ";
      cin >> rep;
    } while ((rep != 'o') and (rep != 'n'));
  } while (rep == 'o');
 
  return 0;
}
 
/* ----------------------------------------------------------------------
 * Calcule de façon itérative le n-ieme nombre de Fibonacci.
 * Entrée : le nombre n 
 * Sortie : F(n)
 * ---------------------------------------------------------------------- */
int FibonacciIteratif(int n)
{
  int Fn(0);    // stocke F(i)  , initialisé par F(0)
  int Fn_1(Fn); // stocke F(i-1), initialisé par F(0)
  int Fn_2(1);  // stocke F(i-2), initialisé par F(-1)
 
  for (int i(1); i <= n; ++i) {
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
 
    do {
      cout << "Entrez un nombre int ";
      if (a >= b)
	cout << "supérieur ou égal à " << a;
      else
	cout << "compris entre " << a << " et " << b;
      cout << " : ";
      cin >> res;
      if (cin.fail()) { 
	cout << "Je vous ai demandé d'entrer un nombre, "
	     << "pas du charabia !" << endl;
        // remet cin dans un état lisible
        cin.clear();
	// "jette" toute la ligne
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	res = a-1;
      }
    } while ((res < a) or ((a < b) and (res > b)));
 
   return res;
}
