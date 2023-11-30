#include "ODESolver.hpp"

ODESolver::ODESolver(function<VectorXd(double, VectorXd)> fun, double t_start, double t_end, VectorXd y0) : fun(fun), t_start(t_start), t_end(t_end), y0(y0) {};

  pair<VectorXd, vector<VectorXd>> ODESolver::RK4(unsigned int n) {
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
      pair<VectorXd, vector<VectorXd>> res;
    res.first = t;
    res.second =Y;
    return res; 
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
        myfile << t_start << " , "<< y0 << "\n";

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

  pair<VectorXd, vector<VectorXd>> ODESolver::midpoint(unsigned int n) {
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
    pair<VectorXd, vector<VectorXd>> res;
    res.first = t;
    res.second =Y;
    return res;
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
    myfile << t_start << " , "<< y0 << "\n";

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

  pair<VectorXd, vector<VectorXd>> ODESolver::euler(unsigned int n) {
    
    double h = (t_end - t_start) / n;
    VectorXd t(n+1);
    t[0] = t_start;
    vector<VectorXd> Y;
    VectorXd y = y0;
    Y.push_back(y0);

    for (unsigned int j = 0; j < n; j++) {
      VectorXd k1 = fun(t[j], y);
        t[j + 1] = t[j] + h;
      
      //cout << y<<endl;
      y += h * k1;
      
      Y.push_back(y);
    }

    pair<VectorXd, vector<VectorXd>> res;
    res.first = t;
    res.second =Y;
    return res;
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
      myfile << t_start << " , "<< y0 << "\n";


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

  double ODESolver::accuracy(pair<VectorXd, vector<VectorXd>>& res, function<VectorXd(double)> analitic) {
        double max_error = 0.0;
        vector<VectorXd>& Y = res.second;
        VectorXd& t = res.first;
        //cout << Y.size()<<endl;
        //cout << t.size()<<endl;
        //cout<< t[0] << endl;
        //cout << t[t.size()-1] << endl;
        for (unsigned int i = 0; i < t.size(); ++i) {
            VectorXd y_analitic = analitic(t[i]); // Calcolo della soluzione analitica in t

            VectorXd diff = Y[i] - y_analitic; // Differenza tra soluzione numerica e analitica

            double error = diff.norm(); // Calcolo della norma dell'errore

            max_error = std::max(max_error, error); // Aggiornamento dell'errore massimo
        }

        return max_error;
    }

    unsigned int ODESolver::convergence(pair<VectorXd, vector<VectorXd>>& res, function<VectorXd(double)> analitic) {
        double h = (t_end - t_start)/res.second.size();
        double accuracy = this->accuracy(res, analitic);
        unsigned int C = 10;
        double k = h;
        unsigned int p = 0;
        while (accuracy<C*k) {
          k = k*k;
          p+= 1;
        }
        return p;
    };

    void ODESolver::testEfficiency(string x, unsigned int n) {
      if (x == "RK4") {
      std::chrono::duration<double> sum;
      for (unsigned int i=0; i<5; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        RK4(n); // O qualsiasi metodo che si desidera testare
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = end - start;
        sum+= time;
      }
      chrono::duration<double> a = sum/5;
      std::cout << "Elapsed time: " << a.count() << "s\n";
      }
      else if (x == "midpoint") {
      std::chrono::duration<double> sum;
      for (unsigned int i=0; i<5; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        midpoint(n); // O qualsiasi metodo che si desidera testare
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = end - start;
        sum+= time;
      }
      chrono::duration<double> a = sum/5;
      std::cout << "Elapsed time: " << a.count() << "s\n";
      }
      else if (x == "euler") {
      std::chrono::duration<double> sum;
      for (unsigned int i=0; i<5; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        euler(n); // O qualsiasi metodo che si desidera testare
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = end - start;
        sum+= time;
      }
      chrono::duration<double> a = sum/5;
      std::cout << "Elapsed time: " << a.count() << "s\n";
      }
      else {
          throw invalid_argument("Invalid input for testEfficency. You have to choose between RK4, midpoint or euler!");
      }
    };

  void ODESolver::testStability(string x, pair<VectorXd, vector<VectorXd>>& res){
    VectorXd pert = VectorXd::Constant(res.second[0].size(), 0.01);
    VectorXd y0_pert=res.second[0]+pert;

    unsigned int n=res.second.size();
    ODESolver perturbed(fun,t_start,t_end,y0_pert);
    // Calcola la soluzione con il metodo scelto
    pair<VectorXd, vector<VectorXd>> res_pert;

      if (x == "RK4") {
          res_pert = perturbed.RK4(n);
      } else if (x == "midpoint") {
          res_pert = perturbed.midpoint(n);
      } else if (x == "euler") {
          res_pert = perturbed.euler(n);
      } else {
          // Gestione dell'errore nel caso x non sia nessuno dei valori previsti
      }

    double max_error = 0.0;
    vector<VectorXd>& Y = res.second;
    vector<VectorXd>& Y_pert=res_pert.second;
        for (unsigned int i = 0; i < n; ++i) {

            VectorXd diff = Y[i] - Y_pert[i]; // Differenza tra soluzione numerica e analitica

            double error = diff.norm(); // Calcolo della norma dell'errore

            max_error = std::max(max_error, error); // Aggiornamento dell'errore massimo
        }

    cout<<"with a perturbation of the initial value of " << 0.01 << " the solution has a perturbation of " << max_error<<endl;

    };
    
