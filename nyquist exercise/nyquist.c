#include <stdio.h>
#include <math.h>
 
#define M_PI 3.14159265358979323846
 
//notes : the C++ version used vectors inside the struct but since
//it's impossible to use variable-sized array in structs in C then
//the array must be considered separately when calling the functions. 

// --------------------------------------------------
struct Sinusoide {
  double amplitude;
  double frequence;
  double dephasage;
};


// --------------------------------------------------
struct Echantillonage {
  double fe;       // fréquence d'échantillonnage
  double t0;       // temps initial
};
 
// ======================================================================
// fonction outil : composante sinusoidale pure
 
double sin_pure(double x, struct Sinusoide s)
{
  return s.amplitude * sin(2 * M_PI * s.frequence * x + s.dephasage);
}
 
// ======================================================================
// fonction outil : signal = somme de sinus
 
double signal(double x, int taille, struct Sinusoide signal[taille])
{
  double val=0.0;
  for (int i=0;i<taille;i++) {
    val += sin_pure(x, signal[i]);
  }
  return val;
}
 
// ======================================================================
// échantillonnage d'un signal
 
void echantillonne(int taille, struct Sinusoide s[taille], double freq,
                            double t_min, double t_max, struct Echantillonage* echant,
                            int nb_echant, double echantillons[nb_echant])
{
  echant->fe = freq;
  echant->t0 = t_min;
   
  for (int i=0; i < nb_echant; i++) {
    echantillons[i] = signal(t_min + i / freq, taille, s);
  }
}
 
// ======================================================================
// fonction outil : sinus cardinal
 
double sinc(double x)
{
    
  return (fabs(x) < 1e-8 ? 1.0 : sin(M_PI * x)/(M_PI * x));
}
 
// ======================================================================
// formule de reconstruction
 
double reconstruction(double x, struct Echantillonage echant,
                            int nb_echant, double echantillons[nb_echant])
{
  double valeur=0.0;
  for (int i=0; i < nb_echant; ++i) {
    valeur += echantillons[i] * sinc(echant.fe * (x - echant.t0) - i);
  }
  return valeur;
}
 
// ======================================================================
int main()
{

  struct Sinusoide s[4] ={
    { 1.0 , 2.0, 0.0 }, // première composante
    { 0.5 , 4.0, 0.1 }, // ...
    { 0.33, 6.0, 0.2 }, // ...
    { 0.25, 8.0, 0.3 } // ...
   };
 
  double t_min=0.0;
  double t_max=2.0;
  
  struct Echantillonage ech1;
  double freq1 = 20.0;
  int nb_echant1 = 1+(int)(freq1 * (t_max - t_min));
  double echantillons1[nb_echant1];
  echantillonne(4,s,freq1,t_min,t_max, &ech1, nb_echant1, echantillons1);
  
  struct Echantillonage ech2;
  double freq2 = 11.0;
  int nb_echant2 = 1+(int)(freq2 * (t_max - t_min));
  double echantillons2[nb_echant2];
  echantillonne(4,s,freq2,t_min,t_max, &ech2, nb_echant2, echantillons2);
  
  int nb_points=30;
  double dt=(t_max-t_min)/nb_points;
  
  for(double t=t_min;t<=t_max;t+=dt){
      printf("%lf8 %lf8 %lf8 %lf8\n",t,
                                 signal(t,4,s),
                                 reconstruction(t,ech1,nb_echant1,echantillons1),
                                 reconstruction(t,ech2,nb_echant2,echantillons2));
  }
 
  return 0;
}
