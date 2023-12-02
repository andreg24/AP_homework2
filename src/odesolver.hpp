#ifndef ODESOLVER_HPP_
#define ODESOLVER_HPP

#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include <vector>
#include "../../eigen/Eigen/Dense"
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
    pair<VectorXd, vector<VectorXd>> RK4(unsigned int n);

    //Variation of RK4 that saves the results into a csv
    void RK4_csv(unsigned int n, string filename);

    //Midpoint method for solving ODEs
    pair<VectorXd, vector<VectorXd>> midpoint(unsigned int n);

    //Variation of midpoint method that saves the results into a csv
    void midpoint_csv(unsigned int n, string filename);

    // Forward Euler methord for solving ODEs
    pair<VectorXd, vector<VectorXd>> euler(unsigned int n);

    // Variation of euler method that saves the results into a csv
    void euler_csv(unsigned int n,string filename);

    // Accuracy
    double accuracy(pair<VectorXd, vector<VectorXd>>& res, function<VectorXd(double)> analitic);

    //Efficiency
    double efficiency(string x, unsigned int n);

    //Stability
    pair<double, double> stability(string x, pair<VectorXd, vector<VectorXd>>& res, double p);

    //Convergence
    double convergence(pair<VectorXd, vector<VectorXd>>& res, function<VectorXd(double)> analytic_solution);
 
};


#endif
