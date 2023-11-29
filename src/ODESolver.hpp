#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include <vector>
#include "./eigen/Eigen/Dense"
#include <chrono>

using namespace Eigen;
using namespace std;

class ODESolver {
private:
  function<VectorXd(double,VectorXd)> fun; //Function to implement outside the class
  double t_start; //Initial value of the interval of the domain of the function
  double t_end; //Last value of the interval of the domain of the function
  VectorXd y0; //Initial value of the Cauchy problem

public:
    //Constructor
    ODESolver(function<VectorXd(double, VectorXd)> fun, double t_start, double t_end, VectorXd y0);

    //Runge Kutta 4 method for solving ODEs
    vector<VectorXd> RK4(unsigned int n);

    //Variation of RK4 that saves the results into a csv
    void RK4_csv(unsigned int n);

    //Midpoint method for solving ODEs
    vector<VectorXd> midpoint(unsigned int n);

    //Variation of midpoint method that saves the results into a csv
    void midpoint_csv(unsigned int n);

    // Forward Euler methord for solving ODEs
    vector<VectorXd> euler(unsigned int n);

    // Variation of euler method that saves the results into a csv
    void euler_csv(unsigned int n);

    // Accuracy
    double accuracy(vector<VectorXd> Y, function<VectorXd(double)> analitic) {
      double max_error = 0.0;
      VectorXd diff(Y.size()-1); 
      cout<<Y[0].size()<<endl;
      cout<<Y.size()<<endl;
        for (unsigned int i=0; i < Y[0].size(); i++) //ciclo sulle righe 
        {
          for (unsigned int j=1; j<Y.size(); j++) // ciclo sulle colonne a partire dalla seconda 
          {
              diff[j-1] = Y[j][i] - analitic(Y[0][i])[j];
              cout << diff[j-1]<<endl;
          }
          max_error = max(diff.norm(), max_error);
          
        }
        return max_error;
    }

    // Convergence order


};
