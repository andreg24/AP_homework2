#ifndef ODESOLVER_HPP_
#define ODESOLVER_HPP

#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include <vector>
//#include "../../eigen/Eigen/Dense"
#include "Eigen/Dense"
#include <chrono>

using namespace Eigen;
using namespace std;

class ODESolver {
private:
  const function<VectorXd(double,VectorXd)> fun; //Function to implement outside the class
  const double t_start; //Initial value of the interval of the domain of the function
  const double t_end; //Last value of the interval of the domain of the function
  const VectorXd y0; //Initial value of the Cauchy problem

public:
    //Constructor
    ODESolver(function<VectorXd(double, VectorXd)> fun, double t_start, double t_end, VectorXd y0);

    //Runge Kutta 4 method for solving ODEs
    pair<VectorXd, vector<VectorXd>> RK4(const unsigned int n);

    //Variation of RK4 that saves the results into a csv
    void RK4_csv(const unsigned int n, const string filename);

    //Midpoint method for solving ODEs
    pair<VectorXd, vector<VectorXd>> midpoint(const unsigned int n);

    //Variation of midpoint method that saves the results into a csv
    void midpoint_csv(const unsigned int n, const string filename);

    // Forward Euler methord for solving ODEs
    pair<VectorXd, vector<VectorXd>> euler(const unsigned int n);

    // Variation of euler method that saves the results into a csv
    void euler_csv(const unsigned int n,const string filename);

    // Accuracy
    double accuracy(pair<VectorXd, vector<VectorXd>>& res,const function<VectorXd(double)> analitic);

    //Efficiency
    double efficiency(const string method, const unsigned int n);

    //Stability
    pair<double, double> stability(const string method, pair<VectorXd, vector<VectorXd>>& res, const double p);

    //Convergence
    double convergence(pair<VectorXd, vector<VectorXd>>& res,const function<VectorXd(double)> analytic_solution);
 
};


#endif
