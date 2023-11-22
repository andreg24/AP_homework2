#include "csvparser.hpp"

/*
	useful functions
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



CSVParser::CSVParser(const string& input_file) : input_file(input_file)  {}

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
					optional<string> value = cell;
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
				cout << cell.c_str() << endl;
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
							throw invalid_argument("Brutto coglione hai messo delle stringhe nella colonna dei double");
						}
					}
				}
				++ counter;
			}
		}
	}
}


variant<optional<string>, optional<double>> CSVParser::operator()(const int row, const int col) {
	variant<vector<optional<string>>, vector<optional<double>>> column = dataset[col];
	variant<optional<string>, optional<double>> result;
	try {
		result = get<vector<optional<string>>>(column)[row];
	} catch (bad_variant_access& e) {
		cout << "gotcha" << endl;
		result = get<vector<optional<double>>>(column)[row];
	}
	return result;
}


double CSVParser::mean_col(size_t col_idx){
		if (col_idx >= dataset.size() || col_idx < 0) {
            cerr << "Column index out of range." << endl;
            return 0.0;}

        if (holds_alternative<std::vector<optional<double>>>(dataset[col_idx])) {
            const auto& double_column = get<vector<optional<double>>>(dataset[col_idx]);
            if (double_column.empty()) {
                cerr << "Column is empty." << std::endl;
                return 0.0;
            }

            boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
            for (const auto& val : double_column) {
                acc(val.value());
            }
			return boost::accumulators::mean(acc);
       		} else {
            cerr << "Column is not numeric." << std::endl;
            return 0.0;
        }

        }


  double CSVParser::var_col(size_t col_idx) {
        if (col_idx >= dataset.size() || col_idx < 0) {
            cerr << "Column index out of range." << endl;
            return 0.0;
        }

        if (holds_alternative<std::vector<optional<double>>>(dataset[col_idx])) {
            const auto& double_column = std::get<std::vector<optional<double>>>(dataset[col_idx]);
            if (double_column.empty()) {
                cerr << "Column is empty." << endl;
                return 0.0;
            }

            boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc;
            for (const auto& val : double_column) {
                acc(val.value());
            }

            return boost::accumulators::variance(acc);
        } else {
            cerr << "Column is not numeric." << endl;
            return 0.0;
        }
  }

double CSVParser::median_col(size_t col_idx) {
        if (col_idx >= dataset.size() || col_idx < 0) {
            std::cerr << "Column index out of range." << std::endl;
            return 0.0;
        }

        if (std::holds_alternative<std::vector<optional<double>>>(dataset[col_idx])) {
            const auto& double_column = std::get<std::vector<optional<double>>>(dataset[col_idx]);
            if (double_column.empty()) {
                std::cerr << "Column is empty." << std::endl;
                return 0.0;
            }

            accumulator_set<double, stats<tag::median(with_p_square_quantile)>> acc;
            for (const auto& val : double_column) {
                acc(val.value());
            }

            return median(acc);
        } else {
            std::cerr << "Column is not numeric." << std::endl;
            return 0.0;
        }
  }


double CSVParser::dev_std(size_t col_idx) {
    return std::sqrt(var_col(col_idx));
  }

map<string, int> CSVParser::countFrequency(size_t col_idx) {
    map<string, int> stringFrequencyMap;

        if (col_idx >= dataset.size() || col_idx < 0) {
            cerr << "Column index out of range." << endl;
            return stringFrequencyMap;
        }

        if (holds_alternative<vector<optional<string>>>(dataset[col_idx])) {
            const auto& string_column = get<vector<optional<string>>>(dataset[col_idx]);

            for (const auto& cell : string_column) {
                if (cell.has_value()) {
                    string value = cell.value();
                    stringFrequencyMap[value]++;
                }
            }

            return stringFrequencyMap;
        } else {
            const auto& numeric_column = get<vector<optional<double>>>(dataset[col_idx]);

            for (const auto& cell : numeric_column) {
                if (cell.has_value()) {
                    double value = cell.value();
                    stringFrequencyMap[to_string(cell.value())]++;
                }
            }

            return stringFrequencyMap;
        }
}

double CSVParser::covar(size_t col_idx1, size_t col_idx2) {
        if (col_idx1 >= size || col_idx1 < 0 || col_idx2 >= size || col_idx2 < 0) {
            cerr << "Column index out of range." << endl;
            return 0.0;
        }

        if (holds_alternative<std::vector<optional<double>>>(dataset[col_idx1]) && holds_alternative<std::vector<optional<double>>>(dataset[col_idx2])) {
            const auto& double_column1 = std::get<std::vector<optional<double>>>(dataset[col_idx1]);
            const auto& double_column2 = std::get<std::vector<optional<double>>>(dataset[col_idx2]);
            if (double_column1.empty() || double_column2.empty()) {
                cerr << "One of the columns is empty." << endl;
                return 0.0;
            }

            boost::accumulators::accumulator_set<double, stats<tag::covariance<double, tag::covariate1> > > acc;
            for (size_t i = 0; i < double_column1.size(); ++i) {
                acc(double_column1[i].value(), covariate1 = double_column2[i].value());
            }

            

            return covariance(acc);
        } else {
            cerr << "One of the columns is not numeric." << endl;
            return 0.0;
        }
    }



/*  DA AGGIORNARE
void CSVParser::print() {

    std::cout<<"col"<<dataset.size();

    std::cout<< "row"<< std::get<std::vector<double>>(dataset[0]).size();

   // std::get<std::vector<std::string>>;

 for (const auto& column : dataset) {
   if (std::holds_alternative<std::vector<std::string>>(column)) {
     const auto& string_column = std::get<std::vector<std::string>>(column);
     for (const auto& cell : string_column) {
       std::cout << cell << " ";
     }
     std::cout << "\n";
   } else if (std::holds_alternative<std::vector<double>>(column)) {
     const auto& double_column = std::get<std::vector<double>>(column);
     for (const auto& cell : double_column) {
       std::cout << cell << " ";
     }

 }
}/
*/
