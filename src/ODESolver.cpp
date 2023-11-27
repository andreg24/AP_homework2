#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
#include "./eigen/Eigen/Dense"

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

   vector<VectorXd> RK4(unsigned int n) {
       double h = (t_end - t_start)/n; 
       double t=t_start;    
       std::vector<VectorXd> Y;   
       //double t_n = t_start;
       VectorXd y = y0;
       Y.push_back(y0);
       for (unsigned int j=0; j<n; j++) {

           VectorXd k1 = fun(t, y);
/*
           VectorXd k2 = fun(t[j]+h/2, Y[j]+0.5*k1*h);
           VectorXd k3 = fun(t[j]+h/2, Y[j]+0.5*k2*h);
           VectorXd k4 = fun(t[j]+h, Y[j]+k3*h);
*/
           VectorXd k2 = fun(t+h/2.0, y+0.5*k1*h);
           VectorXd k3 = fun(t+h/2.0, y+0.5*k2*h);
           VectorXd k4 = fun(t+h, y+k3*h);
           t+=h;

           y+=+h/6.0*(k1+2*k2+2*k3+k4);
           Y.push_back(y);
           std::cout<<"ciao"<<y<<endl;

       }
     //  pair<VectorXd, vector<VectorXd>> res(t,Y);
       return Y; 
   }
};

VectorXd fun(double t, VectorXd y) {
   double a=2.0/3.0;
   double b=4.0/3.0;
   double c=1.0;
   double d=1.0;
   VectorXd dy(y.size());
   dy(0)=a*y(0)-b*y(0)*y(1);
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
   std::vector<VectorXd> solution=solver.RK4(n);
   for (unsigned int j=0; j<5; j++){
    std::cout<<solution[j]<<endl;
       //std::cout << solution.second[j].transpose() << std::endl;
   }

   return 0;
}
