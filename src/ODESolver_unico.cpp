#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
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
       VectorXd t(n);
       t[0] = t_start;    
       std::vector<VectorXd> Y;   
       VectorXd y = y0;
       Y.push_back(y0);
       for (unsigned int j=0; j<n; j++) {

           VectorXd k1 = fun(t[j], y);
/*
           VectorXd k2 = fun(t[j]+h/2, Y[j]+0.5*k1*h);
           VectorXd k3 = fun(t[j]+h/2, Y[j]+0.5*k2*h);
           VectorXd k4 = fun(t[j]+h, Y[j]+k3*h);
*/
           VectorXd k2 = fun(t[j]+h/2.0, y+0.5*k1*h);
           VectorXd k3 = fun(t[j]+h/2.0, y+0.5*k2*h);
           VectorXd k4 = fun(t[j]+h, y+k3*h);
           if (j!= n-1) {
           t[j+1]=t[j]+h;
           }

           y+=+h/6.0*(k1+2*k2+2*k3+k4);
           Y.push_back(y);
           //std::cout<<"ciao"<<y<<endl;

       }
       return Y; 
   }

   void RK4_csv(unsigned int n) {
       double h = (t_end - t_start)/n; 
       double t = t_start;       
       VectorXd y = y0;
       std::ofstream myfile;
    myfile.open("resultsRK4.csv");
    if (myfile.is_open()) {
      myfile << "t" <<" , ";
      for (unsigned int i=0; i<y.size()-1; i++) {
         myfile<< "y" << i<< " , ";
      };
      myfile << "y"<< y.size()-1<< "\n";
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
           myfile << t << ",";
           for (unsigned int i=0; i<y.size()-1; i++) {
            myfile << y(i) << ",";
           }
           myfile << y(y.size()-1);
           myfile << "\n";
           //std::cout<<"ciao"<<y<<endl;

       }

        myfile.close();
        std::cout << "I risultati sono stati salvati in resultsRK4.csv" << std::endl;
    } else {
        std::cout << "Impossibile aprire il file resultsRK4.csv" << std::endl;
    }
   }

   vector<VectorXd> midpoint(unsigned int n) {
    double h = (t_end - t_start) / n;
    VectorXd t(n);
    t[0] = t_start;
    vector<VectorXd> Y;
    VectorXd y = y0;
    Y.push_back(y0);

    for (unsigned int j = 0; j < n; j++) {
      VectorXd k1 = fun(t[j], y);
      VectorXd k2 = fun(t[j] + h / 2.0, y + 0.5 * h * k1);
      if (j!= n-1) {
           t[j+1]=t[j]+h;
      }
      y += h * k2;
      Y.push_back(y);
    }
    return Y;
   }

   void midpoint_csv(unsigned int n) {
    double h = (t_end - t_start) / n;
    double t = t_start;
    VectorXd y = y0;

    std::ofstream myfile;
    myfile.open("results_midpoint.csv");
    if (myfile.is_open()) {
      myfile << "t" <<" , ";
      for (unsigned int i=0; i<y.size()-1; i++) {
         myfile<< "y" << i<< " , ";
      };
      myfile << "y"<< y.size()-1<< "\n";

    for (unsigned int j = 0; j < n; j++) {
      VectorXd k1 = fun(t, y);
      VectorXd k2 = fun(t + h / 2.0, y + 0.5 * h * k1);
      t+=h;

      y += h * k2;
      myfile << t << ",";
           for (unsigned int i=0; i<y.size()-1; i++) {
            myfile << y(i) << ",";
           }
           myfile << y(y.size()-1);
           myfile << "\n";
           //std::cout<<"ciao"<<y<<endl;
    }

   myfile.close();
        std::cout << "I risultati sono stati salvati in results_midpoint.csv" << std::endl;
    } else {
        std::cout << "Impossibile aprire il file results_midpoint.csv" << std::endl;
    }

}

vector<VectorXd> euler(unsigned int n) {
    double h = (t_end - t_start) / n;
    VectorXd t(n);
    t[0] = t_start;
    vector<VectorXd> Y;
    VectorXd y = y0;
    Y.push_back(y0);

    for (unsigned int j = 0; j < n; j++) {
      VectorXd k1 = fun(t[j], y);
      if (j!= n-1) {
      t[j + 1] = t[j] + h;
      }

      y += h * k1;
      Y.push_back(y);
    }

    return Y;
  }

  void euler_csv(unsigned int n) {
    double h = (t_end - t_start) / n;
    double t = t_start;
    VectorXd y = y0;

    std::ofstream myfile;
    myfile.open("results_euler.csv");
    if (myfile.is_open()) {
      myfile << "t" << " , ";
      for (unsigned int i = 0; i < y.size() - 1; i++) {
        myfile << "y" << i << " , ";
      };
      myfile << "y" << y.size() - 1 << "\n";

      for (unsigned int j = 0; j < n; j++) {
        VectorXd k1 = fun(t, y);
        t += h;
        y += h * k1;
        myfile << t << ",";
        for (unsigned int i = 0; i < y.size() - 1; i++) {
          myfile << y(i) << ",";
        }
        myfile << y(y.size() - 1);
        myfile << "\n";
      }

      myfile.close();
      std::cout << "I risultati sono stati salvati in results_euler.csv" << std::endl;
    } else {
      std::cout << "Impossibile aprire il file results_euler.csv" << std::endl;
    }
  }
};


/*VectorXd fun(double t, VectorXd y) {
   double a=2.0/3.0;
   double b=4.0/3.0;
   double c=1.0;
   double d=1.0;
   VectorXd dy(y.size());
   dy(0)=a*y(0)-b*y(0)*y(1);
   dy(1)=c*y(1)*y(0)-d*y(1);
   return dy;
}*/

VectorXd fun(double t, VectorXd y) {
   double a=10;
   VectorXd dy(y.size());
   dy(0)=-a*y(0);
   return dy;
}

int main(){
   double t_start=0;
   double t_end=10;
   VectorXd y0(1);
   y0<<1;
   unsigned int n=5000;
   ODESolver solver= ODESolver( fun, t_start,t_end,y0);
   //std::vector<VectorXd> solution1=solver.RK4(n);
   //solver.RK4_csv(n);
   //std::vector<VectorXd> solution2=solver.midpoint(n);
   /*for (unsigned int j=4990; j<5000; j++){
    std::cout<<solution1[j]<<endl;
       //std::cout << solution.second[j].transpose() << std::endl;
   }*/
   /*for (unsigned int j=4990; j<5000; j++){
    std::cout<<solution2[j]<<endl;
       //std::cout << solution.second[j].transpose() << std::endl;
   }*/
   //solver.midpoint_csv(n);
   std::vector<VectorXd> solution3=solver.euler(70);
   for (unsigned int j=0; j<70; j++){
    std::cout<<solution3[j]<<endl;
       //std::cout << solution.second[j].transpose() << std::endl;
   }
   solver.euler_csv(70);

   return 0;
}
