#include "odesolver.hpp"

//----------------------------------------------------------
// Function to check euler
VectorXd fun(double t, VectorXd y) {
   double a=2;
   VectorXd dy(y.size());
   dy(0)=-a*y(0)*t;
   return dy;
}

// Analitic solution
VectorXd analitic(double t) {
   VectorXd y(1);
   y(0) = exp(-t*t);
   return y;
}
//---------------------------------------------------------------
Eigen::VectorXd func(double t,Eigen::VectorXd y) {
 Eigen::VectorXd result(2);
 int a=4; int b=3; int c=0; int d=2; int e=3;
 result[0]=-a*y[0]-b*y[1]+c*t;
 result[1]=d*y[0]+e*y[1];
 return result;
}

Eigen::VectorXd analitic2(double t){ 
   Eigen::VectorXd y(2);
   y[0]=-(exp(-3*t)*(exp(5*t)-6))/5;
   y[1]=2*(exp(-3*t)*(exp(5*t)-1))/5;
   return y;
}
//--------------------------------------------------------


int main(){


// Function 1D:
   // interval
   double t_start=0; 
   double t_end=10;
   // initial value
   VectorXd y0(1);
   y0<<1;
   // number of subintervals
   unsigned int n=70;
   ODESolver solver= ODESolver( fun, t_start,t_end,y0);

   // RUNGE KUTTA 4
   pair<VectorXd, vector<VectorXd>> sol_rk=solver.RK4(n);
   
   // Printing RK4 in a csv
   solver.RK4_csv(n,"RK4results.csv");

   // RK4's accuracy
   double acc_rk = solver.accuracy(sol_rk, analitic);
   std::cout << "The global error of RK4's method for your differential equation is: "<< acc_rk<<endl;

   // RK4's efficiency
   double eff_rk = solver.efficiency("RK4", n); 
   std::cout << "Elapsed time for RK4's computation: " << eff_rk << "s\n";

   // RK4's stability
   pair <double, double> stab_rk = solver.stability("RK4", sol_rk, 0.01);
   std::cout<<"with a perturbation on the initial value of " << stab_rk.first << " the solution has a perturbation of " << stab_rk.second<<endl;

   // RK4's convergence order
   solver.convergence(sol_rk, analitic);
   std::cout << "The convergence order is: "<<solver.convergence(sol_rk, analitic)<<"\n"<< endl;


   // MIDPOINT
   pair<VectorXd, vector<VectorXd>> sol_mp=solver.midpoint(n);
   
   // Printing Midpoint in a csv
   solver.midpoint_csv(n,"midpointResults.csv");

   // Midpoint's accuracy
   double acc_mp = solver.accuracy(sol_mp, analitic);
   std::cout << "The global error of midpoint's method for your differential equation is: "<< acc_mp<<endl;

   // Midpoint's efficiency
   double eff_mp= solver.efficiency("midpoint", n); 
   std::cout << "Elapsed time for midpoint's computation: " << eff_mp << "s\n";

   // Midpoint's stability
   pair <double, double> stab_mp = solver.stability("midpoint", sol_mp, 0.01);
   cout<<"with a perturbation on the initial value of " << stab_mp.first << " the solution has a perturbation of " << stab_mp.second<<endl;

   // Midpoint's convergence order
   solver.convergence(sol_mp, analitic);
   std::cout << "The convergence order is: "<<solver.convergence(sol_mp, analitic)<<"\n"<< endl;


   // EULER
   pair<VectorXd, vector<VectorXd>> sol_eu=solver.euler(n);
   
   // Printing Euler in a csv
   solver.euler_csv(n,"eulerResults.csv");

   // Euler's accuracy
   double acc_eu = solver.accuracy(sol_eu, analitic);
   std::cout << "The global error of Euler's method for your differential equation is: "<< acc_eu<<endl;

   // Euler's efficiency
   double eff_eu = solver.efficiency("euler", n); 
   std::cout << "Elapsed time for euler's computation: " << eff_eu << "s\n";

   // Euler's stability
   pair <double, double> stab_eu = solver.stability("euler", sol_eu, 0.01);
   std::cout<<"with a perturbation on the initial value of " << stab_eu.first << " the solution has a perturbation of " << stab_eu.second<<endl;

   // Euler's convergence order
   solver.convergence(sol_eu, analitic);
   std::cout << "The convergence order is: "<<solver.convergence(sol_eu, analitic)<< "\n"<< endl;
   std::cout << "\n";


cout<<"------------------------------------------------------------------"<<"\n"<<endl;
// Function 2D:
   // interval
   double t_start2=0; 
   double t_end2=50;
   // initial value
   VectorXd y0_2(2);
   y0_2<<1, 0;
   // number of subintervals
   unsigned int n2=100;
   ODESolver solver2= ODESolver( func, t_start2,t_end2,y0_2);

   // RUNGE KUTTA 4
   pair<VectorXd, vector<VectorXd>> sol_rk2=solver2.RK4(n2);
   
   // Printing RK4 in a csv
   solver2.RK4_csv(n2,"RK4Results.csv");

   // RK4's accuracy
   double acc_rk2 = solver2.accuracy(sol_rk2, analitic2);
   std::cout << "The global error of RK4's method for your differential equation is: "<< acc_rk2<<endl;

   // RK4's efficiency
   double eff_rk2 = solver2.efficiency("RK4", n2); 
   std::cout << "Elapsed time for RK4's computation: " << eff_rk2 << "s\n";

   // RK4's stability
   pair <double, double> stab_rk2 = solver2.stability("RK4", sol_rk2, 0.01);
   std::cout<<"with a perturbation on the initial value of " << stab_rk2.first << " the solution has a perturbation of " << stab_rk2.second<<endl;

   // RK4's convergence order
   solver2.convergence(sol_rk2, analitic2);
   std::cout << "The convergence order is: "<<solver2.convergence(sol_rk2, analitic2)<<"\n"<< endl;


   // MIDPOINT
   pair<VectorXd, vector<VectorXd>> sol_mp2=solver2.midpoint(n2);
   
   // Printing Midpoint in a csv
   solver2.midpoint_csv(n2,"midpointResults2.csv");

   // Midpoint's accuracy
   double acc_mp2 = solver2.accuracy(sol_mp2, analitic2);
   std::cout << "The global error of midpoint's method for your differential equation is: "<< acc_mp2<<endl;

   // Midpoint's efficiency
   double eff_mp2= solver2.efficiency("midpoint", n2); 
   std::cout << "Elapsed time for midpoint's computation: " << eff_mp2 << "s\n";

   // Midpoint's stability
   pair <double, double> stab_mp2 = solver2.stability("midpoint", sol_mp2, 0.01);
   cout<<"with a perturbation on the initial value of " << stab_mp2.first << " the solution has a perturbation of " << stab_mp2.second<<endl;

   // Midpoint's convergence order
   solver2.convergence(sol_mp2, analitic2);
   std::cout << "The convergence order is: "<<solver2.convergence(sol_mp2, analitic2)<<"\n"<< endl;


   // EULER
   pair<VectorXd, vector<VectorXd>> sol_eu2=solver2.euler(n2);
   
   // Printing Euler in a csv
   solver2.euler_csv(n2,"eulerResults2.csv");

   // Euler's accuracy
   double acc_eu2 = solver2.accuracy(sol_eu2, analitic2);
   std::cout << "The global error of Euler's method for your differential equation is: "<< acc_eu2<<endl;

   // Euler's efficiency
   double eff_eu2 = solver2.efficiency("euler", n2); 
   std::cout << "Elapsed time for euler's computation: " << eff_eu2 << "s\n";

   // Euler's stability
   pair <double, double> stab_eu2 = solver2.stability("euler", sol_eu2, 0.01);
   std::cout<<"With a perturbation on the initial value of " << stab_eu2.first << " the solution has a perturbation of " << stab_eu2.second<<endl;

   // Euler's convergence order
   solver2.convergence(sol_eu2, analitic2);
   std::cout << "The convergence order is: "<<solver2.convergence(sol_eu2, analitic2)<< endl;


   return 0;
}
