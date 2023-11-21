#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <optional>
#include <vector>
#include <stdexcept>

using namespace std;
 
class CSVParser {
public:
	// Constructor
	CSVParser(const string& input_file);

	vector<variant<vector<optional<string>>, vector<optional<double>>>> getDataset() { return dataset; }

	// parser function
	void read();

	variant<optional<string>, optional<double>> operator()(const int row, const int col);

	// prints the dataset by columns
	//void print();

private:
	string input_file;
	vector<variant<vector<optional<string>>, vector<optional<double>>>> dataset;
	vector<string> header;
};
