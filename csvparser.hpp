#include <fstream>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <string>
#include <variant>
#include <optional>
#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/median.hpp>


using namespace std;
using namespace boost::accumulators;

class CSVParser {
public:
	// Constructor
	CSVParser(const string& input_file);

	vector<variant<vector<optional <string>>, vector<optional<double>>>> getDataset() { return dataset; }

	// parser function
	void read();

	variant<optional <string>, optional<double>> operator()(const int row, const int col);


	double mean_col(size_t col_idx);
	
	double var_col(size_t col_idx);
	double median_col(size_t col_idx);
	double dev_std(size_t col_idx) ;
	// prints the dataset by columns
	//void print();

private:
	string input_file;
	vector<variant<vector<optional<string>>, vector<optional<double>>>> dataset;
	vector<string> header;
};
