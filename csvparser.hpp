#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <optional>
#include <vector>

using namespace std;
 
class CSVParser {
public:
	// Constructor
	CSVParser(const string& input_file);

	vector<variant<vector<string>, vector<optional<double>>>> getDataset() { return dataset; }

	// parser function
	void read();

	variant<string, optional<double>> operator()(const int row, const int col) const;

	// prints the dataset by columns
	//void print();

private:
	string input_file;
	vector<variant<vector<string>, vector<optional<double>>>> dataset;
	vector<string> header;
};
