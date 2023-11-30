#include "csvparser.hpp"
/*
-------------------------------------------------
    USEFUL FUNCTIONS
-------------------------------------------------
*/

bool check_conversion(const string& cell) {
	/*
		Returns true if a full string is convertible to double
	*/
	size_t n;
	try {	stod(cell, &n); }
	catch (invalid_argument& e) { return false; }
	// check if all string is converted
	if ( n == cell.size() ) { return true; }
	else { return false; }
}

void print_vector(const vector<string>& vect) {
	for (unsigned int i=0; i<vect.size(); ++i) {
		cout << vect[i] << ", ";
	}
	cout << endl;
}

//------------------------------------------------------------

//CONSTRUCTOR
CSVParser::CSVParser(const string& input_file) : input_file(input_file)  {}


//PARSER
void CSVParser::read() {
	/* 
		Reads the CSV file and stores the result in dataset
	*/

	ifstream file(input_file);
	string line;
	bool columns_allocated = false; // checks if columns vector have been allocated in dataset
	unsigned int line_counter = 0; // number of row

  while (getline(file, line)) {
		stringstream lineStream(line);
    string cell;

		// first line -> fill header
		if (line_counter == 0) {
    	while (getline(lineStream, cell, ',')) {
				header.push_back(cell);
				//--- should we raise an error if a column name is missing??? ---
			}
            size=header.size();
			++line_counter;
		} 
		// second line -> detect type and allocate columns
		else if (line_counter == 1) {
			while (getline(lineStream, cell, ',')) {
				// detect type
				if (check_conversion(cell)) { 
					optional<double> value = stod(cell);
					vector<optional<double>> temp;
					temp.push_back(value);
					dataset.push_back(temp); 
				}
				else {
					optional<string> value;
					if (cell.size() > 0) { value = cell; }
					vector<optional<string>> temp;
					temp.push_back(value);
					dataset.push_back(temp);
				}
			}
			++line_counter;
		} 
		// all other lines
		else {
			int counter = 0; // columns index counter
			while (getline(lineStream, cell, ',')) {
				//cout << cell.c_str() << endl;
				// is a string column
				if (holds_alternative<vector<optional<string>>>(dataset[counter])) {
					optional<string> value;
					if (cell.size() > 0) { value = cell; }
					get<vector<optional<string>>>(dataset[counter]).push_back(value);
				}
				// is a double column
				else {
					// checks if convertible
					optional<double> value;
					if (check_conversion(cell)) {
						value = stod(cell);
						get<vector<optional<double>>>(dataset[counter]).push_back(value);
					} else {
						if (cell.size() == 0) {	// is a missing value
							get<vector<optional<double>>>(dataset[counter]).push_back(value);
						} else {
							throw invalid_argument("You can't put string in a column of double");
						}
					}
				}
				++ counter;
			}
		}
	}
}

//OPERATOR ()
variant<optional<string>, optional<double>> CSVParser::operator()(const int row, const int col) {
	variant<vector<optional<string>>, vector<optional<double>>> column = dataset[col];
	variant<optional<string>, optional<double>> result;
	try {
		result = get<vector<optional<string>>>(column)[row];
	} catch (bad_variant_access& e) {
		//cout << "gotcha" << endl;<<<<<<<<<<<<<<<--------------------------
        //<<<<<<<<<<<<<<<<<<<<<<<<<------------------------
		result = get<vector<optional<double>>>(column)[row];
	}
	return result;
}

//MEAN
double CSVParser::mean_col(size_t col_idx){

        //checks on column index
		if (col_idx >= dataset.size() || col_idx < 0) {
        throw out_of_range("Column index out of range.");
            return 0.0;}

        //if dataset[col_idx] is a column of double
        if (holds_alternative<std::vector<optional<double>>>(dataset[col_idx])) {
            const auto& double_column = get<vector<optional<double>>>(dataset[col_idx]);
            
            //checks if the column is empty
            if (double_column.empty()) {
                throw runtime_error("Column is empty.");
                return 0.0;
            }

            //creates the boost accumulator
            boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
            for (const auto& val : double_column) {
                acc(val.value());
            }

			return boost::accumulators::mean(acc);
       		} 

            else {
            //if the column is not of double
            throw invalid_argument("Column is not numeric.");
            return 0.0;
        }

        }

//VARIANCE
double CSVParser::var_col(size_t col_idx) {

        //checks on column index
        if (col_idx >= dataset.size() || col_idx < 0) {
            throw out_of_range("Column index out of range.");
            return 0.0;
        }

        //if dataset[col_idx] is a column of double
        if (holds_alternative<std::vector<optional<double>>>(dataset[col_idx])) {
            const auto& double_column = std::get<std::vector<optional<double>>>(dataset[col_idx]);
            
            //checks if the column is empty
            if (double_column.empty()) {
                throw runtime_error("Column is empty.");
                return 0.0;
            }

            //creates the boost accumulator
            boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc;
            for (const auto& val : double_column) {
                acc(val.value());
            }

            return boost::accumulators::variance(acc);
        } 
        else {
            //if the column is not of double
            throw invalid_argument( "Column is not numeric." );
            return 0.0;
        }
  }

//MEDIAN
double CSVParser::median_col(size_t col_idx) {
        
        //checks on column index
        if (col_idx >= dataset.size() || col_idx < 0) {
            throw out_of_range("Column index out of range.");
            return 0.0;
        }

        //if dataset[col_idx] is a column of double
        if (std::holds_alternative<std::vector<optional<double>>>(dataset[col_idx])) {
            const auto& double_column = std::get<std::vector<optional<double>>>(dataset[col_idx]);
            
            //checks if the column is empty
            if (double_column.empty()) {
                throw runtime_error("Column is empty.");
                return 0.0;
            }
            
            //creates the boost accumulator
            accumulator_set<double, stats<tag::median(with_p_square_quantile)>> acc;
            for (const auto& val : double_column) {
                acc(val.value());
            }

            return median(acc);
        } 
        else {
            //if the column is not of double
            throw invalid_argument("Column is not numeric.");
            return 0.0;
        }
  }

//STANDARD DEVIATION
double CSVParser::std_dev(size_t col_idx) {
    return std::sqrt(var_col(col_idx));
  }

//COVARIANCE 
double CSVParser::covar(size_t col_idx1, size_t col_idx2) {

        //checks on column indexes
        if (col_idx1 >= size || col_idx1 < 0 || col_idx2 >= size || col_idx2 < 0) {
            throw out_of_range( "Column index out of range.");
            return 0.0;
        }

        //if dataset[col_idx1] and dataset[col_idx2] are columns of double
        if (holds_alternative<std::vector<optional<double>>>(dataset[col_idx1]) && holds_alternative<std::vector<optional<double>>>(dataset[col_idx2])) {
            const auto& double_column1 = std::get<std::vector<optional<double>>>(dataset[col_idx1]);
            const auto& double_column2 = std::get<std::vector<optional<double>>>(dataset[col_idx2]);
            
            //checks if the columns are empty
            if (double_column1.empty() || double_column2.empty()) {
                throw runtime_error("One of the columns is empty.");
                return 0.0;
            }

            //creates the boost accumulators
            boost::accumulators::accumulator_set<double, stats<tag::covariance<double, tag::covariate1> > > acc;
            for (size_t i = 0; i < double_column1.size(); ++i) {
                acc(double_column1[i].value(), covariate1 = double_column2[i].value());
            }

            return covariance(acc);
        } 
        else {
            //if the column is not of double
            throw invalid_argument("One of the columns is not numeric.");
            return 0.0;
        }
    }

//CORRELATION ANALYSIS
double CSVParser::correlation_analysis(size_t col_idx1, size_t col_idx2) {

        //checks on columns indexes
		if (col_idx1 >= size || col_idx1 < 0 || col_idx2 >= size || col_idx2 < 0) {
            cerr << "Column index out of range." << endl;
            return 0.0;
        }

		optional<double> result;

        //cecks if the standard deviation of the column is zero
		if (std_dev(col_idx1)==0 || std_dev(col_idx2)==0){
			throw runtime_error("Standard deviation is zero. You can't divide by zero!");			
			return result.value();
		}

        result=covar(col_idx1, col_idx2)/(std_dev(col_idx1)*std_dev(col_idx2));
		return result.value();
    }

//FREQUENCY COUNT
map<string, int> CSVParser::countFrequency(size_t col_idx) {
    map<string, int> stringFrequencyMap;

        //checks on column index
        if (col_idx >= dataset.size() || col_idx < 0) {
            throw out_of_range("Column index out of range.");
            return stringFrequencyMap;
        }

        //if dataset[col_idx] is a column of double
        if (holds_alternative<vector<optional<string>>>(dataset[col_idx])) {
            const auto& string_column = get<vector<optional<string>>>(dataset[col_idx]);
            
            //checks if the column is empty
            if (string_column.empty()) {
            throw runtime_error("Column is empty.");
            return stringFrequencyMap;
            }

            //fill the frequency map
            for (const auto& cell : string_column) {
                if (cell.has_value()) {
                    string value = cell.value();
                    stringFrequencyMap[value]++;
                }
            }

            return stringFrequencyMap;
        } 

        //if dataset[col_idx] is a column of double
        else {
            const auto& numeric_column = get<vector<optional<double>>>(dataset[col_idx]);
            
            //checks if the column is empty
            if (numeric_column.empty()) {
            throw runtime_error("Column is empty.");
            return stringFrequencyMap;
        }
            //fill the frequency map
            for (const auto& cell : numeric_column) {
                if (cell.has_value()) {
                    double value = cell.value();
                    stringFrequencyMap[to_string(cell.value())]++;
                }
            }

            return stringFrequencyMap;
        }
}

//SUMMARY
void CSVParser::summary(const string& filename){
    //open the desired file
    ofstream outFile(filename);
    if(outFile.is_open()){

        for (unsigned int i = 0; i < size; i++){

            //if dataset[col_idx] is a column of double
            if (holds_alternative<std::vector<optional<double>>>(dataset[i])){
               const auto& double_column = get<vector<optional<double>>>(dataset[i]);

               //compute statistical operations
               outFile << "Column " << header[i] << ": Mean = " << mean_col(i) 
                      << ", Median = " << median_col(i) 
                      << ", Std Dev = " << std_dev(i) 
                      << ", Variance = " << var_col(i) << "\n";
                map<string, int> freq = countFrequency(i);
                for (const auto& pair : freq) {
                    outFile << " Element:  " << pair.first << " Frequency: " << pair.second << endl;
                }
                outFile << "Correlation with other numeric columns:" << endl;
                for (size_t j = 0; j < dataset.size(); ++j) {
                    if (j != i &&
                        holds_alternative<vector<optional<double>>>(dataset[j])) {
                        try {
                        double correlation = correlation_analysis(i, j);
                        outFile << "  With column '" << header[j] << "': " << correlation << endl;
                        }
                        catch (const exception& e) {
                        outFile <<" For the column "<<header[j]<<" "<< e.what()<< endl;
           }
                    }
                }
           }
           else {
            //if dataset[col_idx] is a column of string
                outFile << "Column " << header[i] << ": non numeric column"<<"\n";
                //compute frequency count
                map<string, int> freq = countFrequency(i);
                for (const auto& pair : freq) {
                    outFile << " Element:  " << pair.first << " Frequency: " << pair.second<<endl;
                }
            }
            outFile<< "--------------------------------------------------------"<< endl;

       }
       outFile.close();
        }
   
   else{
       throw runtime_error("unable to open the file");
   }
    };

//CLASSIFICATION
void CSVParser::classification(string wanted, int col_idx,const string& filename){
        
        //checks on column index        
        if (col_idx >= dataset.size() || col_idx < 0) {
            throw out_of_range("Column index out of range.");
        }

        //boolean to check if the wanted element has been found or not
        bool found=false;

        //open the file
        ofstream outFile(filename);
        if(outFile.is_open()){
            outFile << "CLASSIFICATION OF: "<<wanted<<"\n";

        //if dataset[col_idx] is a column of double
        if (holds_alternative<vector<optional<string>>>(dataset[col_idx])) {
            const auto& string_column = get<vector<optional<string>>>(dataset[col_idx]);
            
            //checks if the column is empty
            if (string_column.empty()) {
            throw runtime_error("Column is empty.");
            }

            for (unsigned int row_idx=0; row_idx<string_column.size();row_idx++){
                //find the row indexes in which there is the wanted element
                if(string_column[row_idx].value()==wanted){
                    found=true;
                    outFile<< "Row "<<row_idx<<": "<<"\n";

                    //print the corresponding row
                    for(unsigned int c=0;c<size;c++){
                        if (holds_alternative<vector<optional<string>>>(dataset[c])) {
                            const auto& tmp = get<vector<optional<string>>>(dataset[c]);
                            outFile<<" "<< tmp[row_idx].value()<<" ";
                        }
                        else {
                            const auto& tmp = get<vector<optional<double>>>(dataset[c]);
                            outFile<<" "<< tmp[row_idx].value()<<" ";
                        }
                    }
                    outFile<<"\n";
            }
            }
        }
        else{
            //if dataset[col_idx] is a column of string
            const auto& double_column = get<vector<optional<double>>>(dataset[col_idx]);
            
            //checks if the column is empty
            if (double_column.empty()) {
            throw runtime_error("Column is empty.");
            }

            for (unsigned int row_idx=0; row_idx<double_column.size();row_idx++){
                //find the row indexes in which there is the wanted element
                if(double_column[row_idx].value()==stod(wanted)){
                    found=true;
                    outFile<< "Row "<<row_idx<<": "<<"\n";
                    for(unsigned int c=0;c<size;c++){
                        //print the corresponding row
                        if (holds_alternative<vector<optional<string>>>(dataset[c])) {
                            const auto& tmp = get<vector<optional<string>>>(dataset[c]);
                            outFile<<" "<< tmp[row_idx].value()<<" ";
                        }
                        else {
                            const auto& tmp = get<vector<optional<double>>>(dataset[c]);
                            outFile<<" "<< tmp[row_idx].value()<<" ";
                        }
                    }
                    outFile<<"\n";
            }
            }
        }

        //if the wanted element is not in the column
        if (found==false){
            outFile<<"There is no "<<wanted<< " in column "<<col_idx;
        }
               outFile.close();
        }
   
   else{
       throw runtime_error("unable to open the file");
   }
    };
      
        
