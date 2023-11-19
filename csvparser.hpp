#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace std;
 
class CSVParser {
public:
	// Constructor
	CSVParser(const string& input_file);

	// parser function
	void read();

	// prints the dataset by columns
	void print();

private:
	string input_file;
	usigned int cols_num;
	vector<variant<vector<string>, vector<double>>> dataset;
	vector<string> header;
};
