#include <stdio.h>
#include <math.h> 
#include <ctype.h>
#include <string.h>
 
 
#define CHAR_NUMBER 27

// ======================================================================
void calcule_probas(const char* s, int compter_espace, double distribution[CHAR_NUMBER])
{
  double frequences[CHAR_NUMBER];
  for(int i=0;i<CHAR_NUMBER;i++) frequences[i]=0;
  double somme=0.0;
  
  for(int i=0;i<strlen(s);i++){
	  if(isalpha(s[i])){
		  ++frequences[toupper(s[i])-'A'];
		  ++somme;
	  }else if ((s[i]==' ') && compter_espace!=0){
		  ++frequences[CHAR_NUMBER];
		  ++somme;
	  }
  }
  
  for(int i=0;i<CHAR_NUMBER;i++){
	  if(frequences[i]>0){
		  distribution[i]=frequences[i]/somme;
	  }else{
		  distribution[i]=0.0;
	  }
  }
}
 
// ======================================================================
double log2(double x)
{
  if (x == 0.0) return 0.0; // pour Ã©viter le NaN
  return log(x) / log(2.0);
}
 
// ======================================================================
double entropieFromDistribution(double distribution[CHAR_NUMBER])
{
  double entropy=0.0;
  
  for(int i=0;i<CHAR_NUMBER;i++){
	  entropy -= distribution[i]*log2(distribution[i]);
  }
  return entropy;
}
 
// ======================================================================
double entropie(const char* s)
{
	double distribution[CHAR_NUMBER];
	calcule_probas(s,0,distribution);
	return entropieFromDistribution(distribution);
}
 
// --------------------------------------------------
void test(const char* s) {
  printf("chaîne : %s\n",s);
  printf("H = %lf\n",entropie(s));
  
}
 
// ======================================================================
int main()
{
 
  test("IL FAIT BEAU A IBIZA");
  test("AAAAA");
  test("A");
  test("abcdefghij");
  test("ABCDEFGHIJ");
  test("JIHGFEDCBA");
  test("AABBCC");
  test("BBCCZZ");
  test("AB");
  test("ZSSZZSSZZS");
  test("ABCD");
 
  return 0;
}

