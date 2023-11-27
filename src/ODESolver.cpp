#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
#include "../../eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

class ODESolver {
private:
  function<VectorXd(double,VectorXd)> fun; // Change here
  double t_start;
  double t_end;
  VectorXd y0;

public:
  ODESolver(function<VectorXd(double, VectorXd)> fun, double t_start, double t_end, VectorXd y0) : fun(fun), t_start(t_start), t_end(t_end), y0(y0) {};

   pair<VectorXd, vector<VectorXd> > RK4(unsigned int n) {
       double h = (t_end - t_start)/n; 
       vector<VectorXd> Y;
       VectorXd t(n);
       Y.push_back(y0);
       t[0]=t_start;
       
       
       //double t_n = t_start;
       VectorXd y = y0;
       for (unsigned int j=0; j<n; j++) {
           VectorXd tempY1=y;
           VectorXd k1 = fun(t[j], y);
/*
           VectorXd k2 = fun(t[j]+h/2, Y[j]+0.5*k1*h);
           VectorXd k3 = fun(t[j]+h/2, Y[j]+0.5*k2*h);
           VectorXd k4 = fun(t[j]+h, Y[j]+k3*h);
*/
           VectorXd tempY2=y+0.5*k1*h;
           VectorXd k2 = fun(t[j]+h/2, tempY2);
           VectorXd tempY3=y+0.5*k2*h;
           VectorXd k3 = fun(t[j]+h/2, tempY3);
           VectorXd tempY4=y+k3*h;
           VectorXd k4 = fun(t[j]+h, tempY4);
           t[j+1]=t[j]+h;

           y+=+h/6*(k1+2*k2+2*k3+k4);
           Y.push_back(y);
       }
       pair<VectorXd, vector<VectorXd>> res(t,Y);
       return res; 
   }
};

VectorXd fun(double t, VectorXd y) {
   double a=2/3;
   double b=4/3;
   double c=1;
   double d=1;
   VectorXd dy(y.size());
   dy(0)=a*y(0)-b*y(0)*y(1)*t/t;
   dy(1)=c*y(1)*y(0)-d*y(1);
   return dy;
}

int main(){
   double t_start=0;
   double t_end=50;
   VectorXd y0(2);
   y0<<4, 2;
   unsigned int n=5000;
   ODESolver solver= ODESolver( fun, t_start,t_end,y0);
   pair<VectorXd, vector<VectorXd> > solution=solver.RK4(n);
   for (unsigned int j=0; j<1; j++){
       std::cout << solution.second[j].transpose() << std::endl;
   }

   return 0;
}
