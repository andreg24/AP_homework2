#include <iostream>
#include <functional>
#include "./eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

class ODESolver {
private:
    function<VectorXd(double, const VectorXd&)> fun; //lambda function
    double t_start;
    double t_end;
    const VectorXd y0;
    unsigned int n;

public:
    //Constructor
    ODESolver(function<VectorXd(double, const VectorXd&)> fun, double t_start, double t_end, const VectorXd y0) : fun(fun), t_start(t_start), t_end(t_end), y0(y0) {};

    //RK4
    pair<VectorXd, vector<VectorXd> > RK4(unsigned int n) {
        double h = (t_end - t_start)/n; 
        pair<VectorXd, vector<VectorXd>> res;
        vector<VectorXd> y(y0.size());
        VectorXd t(n);
        y.push_back(y0);
        double t_n = t_start;
        VectorXd y_n = y0;
        for (unsigned int j=0; j<n; j++) {
            VectorXd k1 = fun(t_n, y_n);
            VectorXd k2 = fun(t_n+h/2, y_n+0.5*k1*h);
            VectorXd k3 = fun(t_n+h/2, y_n+0.5*k2*h);
            VectorXd k4 = fun(t_n+h, y_n+k3*h);
            res.first[j] = t_n;
            res.second[j] = y_n;
            t_n+= h;
            y_n+= h/6*(k1+2*k2+2*k3+k4);
        }
        return res; 
    }
};

