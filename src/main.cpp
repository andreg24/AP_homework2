#include "ODESolver.hpp"

// Function to check RK4 and midpoint
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

// Function to check euler
VectorXd fun(double t, VectorXd y) {
   double a=10;
   VectorXd dy(y.size());
   dy(0)=-a*y(0);
   return dy;
}

VectorXd analitic(double t) {
   double a = 10;
   VectorXd y(1);
   y(0) = exp(-a*t);
   return y;
}


int main(){
   double t_start=0;
   double t_end=10;
   VectorXd y0(1);
   y0<<1;
   unsigned int n=5000;
   ODESolver solver= ODESolver( fun, t_start,t_end,y0);

   // Testing RK4
   /*std::vector<VectorXd> solution1=solver.RK4(n);
   for (unsigned int j=0; j<5000; j++){
    std::cout<<solution1[j]<<endl;
       //std::cout << solution.second[j].transpose() << std::endl;
   }
   solver.RK4_csv(n);*/

   // Testing midpoint
   //std::vector<VectorXd> solution2=solver.midpoint(n);
   /*for (unsigned int j=4990; j<5000; j++){
    std::cout<<solution2[j]<<endl;
       //std::cout << solution.second[j].transpose() << std::endl;
   }*/
   //solver.midpoint_csv(n);

   // Testing Euler
   pair<VectorXd, vector<VectorXd>> solution3=solver.euler(70);
   /*for (unsigned int j=0; j<70; j++){
    std::cout<<solution3[j]<<endl;
       //std::cout << solution.second[j].transpose() << std::endl;
   }*/
   solver.euler_csv(70.0);

   //double ghj = solver.accuracy(solution3, analitic);
   //std::cout << ghj<<endl;

   //solver.testEfficiency("cazzo", 70); 
   //solver.testStability("euler", solution3);


   solver.convergence2(solution3, analitic);
   std::cout << "The minimal error is: "<< solver.convergence2(solution3, analitic).first<< "The average convergence error is: "<<solver.convergence2(solution3, analitic).second << endl;


   


   return 0;
}
