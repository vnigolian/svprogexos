/* ======================================================================
 *
 * Discreate moving average (of an array of values).
 *
 * Version: 1.0 (170901)
 * Author: J.-C. Chappelier (EPFL, 2017)
 *
 * ======================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm> // for min()
using namespace std;

constexpr size_t default_width(3); // some default width for the moving average

/* ======================================================================
 * Compute the moving average of X with a window size T_c, even if the
 * size of X is less than T_c. It simply make a copy in the later
 * case.
 */
vector<double> moving_average(vector<double> X, // input signal
                              size_t T_c = default_width)
{
  vector<double> X_hat(X); /* copy of X to simply handle both the case where X is too short
                            * and the undefined initial values of the moving average, here
                            * by convention taken to be the initial values of X.
                            */

  // Computation takes place only if there is enough signal, i.e.  X.size() >= T_c
  if (X.size() >= T_c) {
    // Initial computation (when n = T_c - 1)
    double  somme(0.0);
    for (size_t m(0); m < T_c; ++m) { // sum iteration
      somme += X[m];
    }
    X_hat[T_c - 1] = somme / T_c;

    // General computation
    for (size_t n(T_c); n < X.size(); ++n) { // for all timestep
      somme += X[n] - X[n - T_c];
      X_hat[n] = somme / T_c;
    }
  }
  
  return X_hat;
}

/* ======================================================================
 * Tool function: sync display of two arrays.
 */
void sync_display(vector<double> const& v,
                  vector<double> const& w)
{
  cout << "# signal\tmoving average" << endl;
  for (size_t i(0); i < v.size(); ++i) {
    cout << v[i] << '\t'
         << (i < w.size() ? w[i] : '-')
         << endl;
  }
}

// ======================================================================
int main()
{
  vector<double> temperatures( { 15.1, 14.8, 13.7, 12.6, 13.8, 14.1,
                                 14.5, 14.8, 15.0, 15.1, 15.5         } );

  sync_display(temperatures, moving_average(temperatures) );

  return 0;
}
