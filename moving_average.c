/* ======================================================================
 *
 * Discrete moving average (of an array of values).
 *
 * Version: 1.0 
 * Author: VZ Nigolian(EPFL, 2017)
 * Translated from a C++ exercise written by J.-C. Chappelier
 * ======================================================================
 */
#include <stdio.h>

/* ======================================================================
 * Compute the moving average of X with a window size T_c, even if the
 * size of X is less than T_c. It simply make a copy in the later
 * case.
 */
void moving_average(int size, double X[size], int T_c, double X_hat[size]);

/* ======================================================================
 * Tool function: sync display of two arrays.
 */
void sync_display(int size, double v[size], double w[size]);

// ======================================================================
int main()
{
	int size = 11;
  double temperatures[]= { 15.1, 14.8, 13.7, 12.6, 13.8, 14.1,
                                 14.5, 14.8, 15.0, 15.1, 15.5};

  double temp_hat[size];
  moving_average(size,temperatures,3,temp_hat);
  sync_display(size,temperatures, temp_hat );

  return 0;
}


/* ======================================================================
 * Compute the moving average of X with a window size T_c, even if the
 * size of X is less than T_c. It simply make a copy in the later
 * case.
 */
void moving_average(int size, double X[size], int T_c, double X_hat[size])
{


  // Computation takes place only if there is enough signal, i.e.  X.size() >= T_c
  if (size >= T_c) {
    // Initial computation (when n = T_c - 1)
    double  somme=0.0;
    for (int m=0; m < T_c; ++m) { // sum iteration
      somme += X[m];
      X_hat[m]=X[m];
    }
    X_hat[T_c - 1] = somme / T_c;

    // General computation
    for (int n=T_c; n < size; ++n) { // for all timestep
      somme += X[n] - X[n - T_c];
      X_hat[n] = somme / T_c;
    }
  }
}

void sync_display(int size, double v[size], double w[size])
{
  printf("# signal\tmoving average\n");
  for (int i=0; i < size; ++i) {
    printf("%lf\t%lf\n",v[i],w[i]);
  }
}
