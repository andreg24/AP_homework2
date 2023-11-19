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

	void print_columns();

private:
	string input_file;
	vector<variant<vector<string>, vector<double>>> dataset;
}
