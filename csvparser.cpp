#include "csvparser.hpp"

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

CSVParser::CSVParser(const string& input_file) : input_file(input_file)  { read(); }


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
				++line_counter;
				//--- should we raise an error if a column name is missing??? ---
			}
		// second line -> detect type and allocate columns
		} else if (line_counter == 1) {
			while (getline(lineStream, cell, ',')) {
				// detect type
				if ( check_conversion(cell) ) { 
					optional<double> converted_value = stod(cell);
					vector<optional<double>> temp;
					temp.push_back(converted_value);
					dataset.push_back(temp); 
				}
				else {
					vector<string> temp;
					temp.push_back(cell);
					dataset.push_back(temp);
				}
				++line_counter;
			}
		} else {
			int counter = 0; // col index counter
			while (getline(lineStream, cell, ',')) {
				// is a string column
				if (holds_alternative<vector<string>>(dataset[counter])) {
					get<vector<string>>(dataset[counter]).push_back(cell);
				}
				// is a double column
				else {
					// check if convertible
					if (check_conversion(cell)) {
						optional<double> converted = stod(cell);
						get<vector<optional<double>>>(dataset[counter]).push_back(converted);
					} 
					else {
						// ---raise error because colum contains more than one type ---
					}
				}
			}
		}
	}
}
/*

   	if (!columns_allocated) {
    	while (getline(lineStream, cell, ',')) {
				// fill header
				header.push_back(cell);

				//detect type
      	try {
        	double value = stod(cell); // try to convert to double
          dataset.push_back(vector<double>{value});
        } catch (invalid_argument&) {
        	dataset.push_back(vector<string>{cell}); // if conversion fails, it's a string
        }
      }
      columns_allocated = true;
    }


     int counter = 0; // col index counter
     while (getline(lineStream, cell, ',')) {
       if (holds_alternative<vector<string>>(dataset[counter])) {
         get<vector<string>>(dataset[counter]).push_back(cell);
       } else if (std::holds_alternative<std::vector<double>>(dataset[counter])) {
         double value = std::stod(cell);
         std::get<std::vector<double>>(dataset[counter]).push_back(value);
       }
       ++counter;
		 
   }

 }

 

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
     std::cout << "\n";
   }
 }
}/
*/
