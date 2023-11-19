// CSVParser class

CSVParser::CSVParser(string& input_file) : input_file(input_file)  { read(); }


void CSVParser::read() {
	/* 
		Reads the CSV file and stores the result in dataset
	*/

   ifstream file(input_file);
	 string line; //???
	 bool columns_allocated = false; // checks if columns vector have been allocated in dataset

   while (getline(file, line)) {
		 stringstream lineStream(line);
     string cell;

     if (!columns_allocated) {
       while (getline(lineStream, cell, ',')) {
         try {
           double value = stod(cell); // try to convert to double
           dataset.push_back(svector<double>{value});
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
}
