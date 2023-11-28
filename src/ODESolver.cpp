#include "ODESolver.hpp"

ODESolver::ODESolver(function<VectorXd(double, VectorXd)> fun, double t_start, double t_end, VectorXd y0) : fun(fun), t_start(t_start), t_end(t_end), y0(y0) {};

  vector<VectorXd> ODESolver::RK4(unsigned int n) {
      double h = (t_end - t_start)/n; //step height. It is fixed
      VectorXd t(n); //vector containing t values each step
      t[0] = t_start; 
      std::vector<VectorXd> Y; //vector containing the values of the solution in t[i] each step.
      VectorXd y = y0; 
      Y.push_back(y0);

      for (unsigned int j=0; j<n; j++) {
        //Runge Kutta increments 
        VectorXd k1 = fun(t[j], y); 
        VectorXd k2 = fun(t[j]+h/2.0, y+0.5*k1*h);
        VectorXd k3 = fun(t[j]+h/2.0, y+0.5*k2*h);
        VectorXd k4 = fun(t[j]+h, y+k3*h);
        // t update
        if (j!= n-1) {
          t[j+1]=t[j]+h;
        }
        // y update using RK4 method 
        y+=+h/6.0*(k1+2*k2+2*k3+k4);
        Y.push_back(y);
        }
      return Y; 
  }

  void ODESolver::RK4_csv(unsigned int n) {
       double h = (t_end - t_start)/n; //fixed step height
       double t = t_start;       
       VectorXd y = y0;
       std::ofstream myfile;
      myfile.open("resultsRK4.csv"); //Opening the file in which we are going to write the results
      if (myfile.is_open()) {

        //header of the csv
        myfile << "t" <<" , ";
        for (unsigned int i=0; i<y.size()-1; i++) {
          myfile<< "y" << i<< " , ";
        };
        myfile << "y"<< y.size()-1<< "\n";
        for (unsigned int j=0; j<n; j++) {
           VectorXd k1 = fun(t, y);
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

        }

        myfile.close(); //Closing the file
        std::cout << "Results are now written in resultsRK4.csv" << std::endl;
      } 
      else {
      std::cout << "Unable to open the file 'resultsRK4.csv'" << std::endl;
      }
  }

  vector<VectorXd> ODESolver::midpoint(unsigned int n) {
    double h = (t_end - t_start) / n; //fixed step height
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

  void ODESolver::midpoint_csv(unsigned int n) {
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
        std::cout << "Results are now written in results_midpoint.csv" << std::endl;
    } 
    else {
      std::cout << "Unable to open the file 'results_midpoint.csv'" << std::endl;
    }

}

  vector<VectorXd> ODESolver::euler(unsigned int n) {
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

  void ODESolver::euler_csv(unsigned int n) {
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
      std::cout << "Results are now written in 'results_euler.csv'" << std::endl;
    } 
    else {
      std::cout << "Unable to open the file 'results_euler.csv'" << std::endl;
    }
  }



