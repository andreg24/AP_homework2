#ifndef ODESOLVER_HPP_
#define ODESOLVER_HPP

#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include <vector>
#include "Eigen/Dense"
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
    void RK4_csv(unsigned int n);

    //Midpoint method for solving ODEs
    pair<VectorXd, vector<VectorXd>> midpoint(unsigned int n);

    //Variation of midpoint method that saves the results into a csv
    void midpoint_csv(unsigned int n);

    // Forward Euler methord for solving ODEs
    pair<VectorXd, vector<VectorXd>> euler(unsigned int n);

    // Variation of euler method that saves the results into a csv
    void euler_csv(unsigned int n);

    // Accuracy
    double accuracy(pair<VectorXd, vector<VectorXd>>& res, function<VectorXd(double)> analitic);

    //Convergence
    unsigned int convergence(pair<VectorXd, vector<VectorXd>>& res, function<VectorXd(double)> analitic);

    //Efficiency
    void testEfficiency(string x, unsigned int n);

    //Stability
    void testStability(string x, pair<VectorXd, vector<VectorXd>>& res);


    pair<double, double> convergence2(pair<VectorXd, vector<VectorXd>>& res, function<VectorXd(double)> analytic_solution) {
        unsigned int n = res.first.size();
        double h = (t_end - t_start)/n;
        VectorXd h_values(4); // Valori di h per la discretizzazione
        h_values << h, h/2, h/4, h/8;

        VectorXd errors(4); // Contiene gli errori massimi per ogni h
        for (int i = 0; i < h_values.size(); ++i) {
            auto numerical_solution = euler((t_end - t_start) / h_values(i));

            double max_error = accuracy(numerical_solution, analytic_solution); // Calcola l'errore massimo
            errors(i) = max_error;
        }

        // Calcola l'ordine di convergenza
        VectorXd convergence_order(3);
        for (int i = 1; i < errors.size(); ++i) {
            double order = log(errors(i - 1) / errors(i)) / log(2.0); // Formula per l'ordine di convergenza
            convergence_order(i - 1) = order;

        }
        /*for (auto elem : convergence_order) {
          cout<<" ciao "<< elem << " ciao "<<endl;
        }*/
 
        // Calcola l'ordine di convergenza medio
        double avg_order = convergence_order.mean();

        // Restituisce l'errore più piccolo e l'ordine di convergenza medio
        return make_pair(errors.maxCoeff(), avg_order);
    }

    
};


#endif
