# GROUP MEMBERS
Sara Carpenè – saracarpene01@gmail.com
Davide De Dominicis – dedominicis2001@gmail.com
Andrea Gottardi – andreagottardi24@gmail.com 

# CODE ORGANIZATION
We choose to implement these two modules: statistical module and ODE module.

# STRUCTURE
- folder csv_examples contains some csv files to use in testing csvparser
- folder src contains the csvparser and odesolver code
- folder apps contains the main files that showcase the functioning of the two modules’ libraries.

# STATISTICAL MODULE
This module takes as command line argument a csv file.
We decided to implement the CSVParser as a class. We store as private members the dataset, the header (that contains the name of the columns) and the size of the dataset (that corresponds to the numbers of columns).
We decided to use the Boost library to perform the statistical operations.
The main creates a member of the class CSVParser, and, when called the function read() , the data in the csv file are stored in “dataset”.
Dataset is a private member of the “CSVParser”, it is a two dimensional vector that store information in columns. Every column is homogeneous and can be composed of double or string. It can handle missing values by the use of std:: optional.
For the columns these operations can be performed:

	-Double columns: mean, variance, median, standard deviation, covariance between two double columns, correlation analysis between two columns, frequency 	count.
 
	-String columns: frequency count.
 
There are two more methods:

	-Summary: for all the columns it computes all possible operations (according to column type), and saves the results in the specified file.
 
	-Classification: allows to find the rows where a wanted word appears and save the results in a specified txt file. You need to indicate the index of the 	column in which you want to search for the wanted word.
 
Moreover, we implemented the Iterator class that allows to smoothly iterate through the columns of the dataset (built on top of the std vector iterator).

# ODE MODULE
The ODEsolver class in the module represents a Cauchy problem. Its creation requires specifying the differential equation to be solved, the initial point, and the interval in which the solution has to be calculated.
We used the third part library Eigen to perform operations with vectors.

The methods implemented to solve the Cauchy problem are: Runge Kutta 4, Euler's method, and the midpoint method. Each of these methods is implemented into two functions, the first one with the name of the method and the second one with csv. The first returns an object in which the different t_n and y1, y2, y3, ... are stored, for later use in any other computation. The second function prints the results in a .csv file.
The other functions allow testing the goodness of fit of numerical methods

	-Accuracy: This function compares the solution found by the numerical method and the analytical solution by taking the infinite norm of the difference 		between the two values
 
	-Efficiency: This function tests the speed of execution of the method (to obtain more accurate estimate of the computation time we decided to execute the 	method five times and return the mean of the results).
 
	-Stability: This function returns by how much the solution is perturbed if the initial value of the Cauchy problem is perturbed.
 
	-Convergence: This function compares numerical solutions obtained by different steps, returning the mean of the differences between the solutions and the 	exact solution. We used the following formula in order to approximate the order of convergency:
	\frac{\log{||e_n-e_{n-1}||}}{\log{||e_{n-1}-e_{n-2}||}}

# INSTALL AND TEST
To create the shared libraries (csvparser.so and odesolver.so), compile maincsv and mainode and link them with the libraries, execute the command *./projbuild.sh /path/to/boost path/to/eigen3*
The result will be saved in a build directory inside the main project directory.

To test the executables on a predetermined example execute *./testbuild.sh*. In order to change the dataset on which maincsv is executed is necessary to modify the given dataset in the testbuild.sh file or execute the command *./maincsv datasetname.csv outputfile_name.


# INDIVIDUAL CONTRIBUTIONS
- Statistical module: all the members of the group contributed equally to the design and implementation of the module
- ODE module: design and implementation realized equally by Carpenè and De Dominicis
- Project management: libraries management, cmake files and bash scripts done by Gottardi
