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


	//iterator class
	class ColIterator{
	private:
	const CSVParser& csvparser;
	size_t col;

	public:
		ColIterator(const CSVParser& csvp, size_t size ) : csvparser(csvp), col(size){};

		ColIterator& operator++(){
			++col;
			return *this;
		}

		bool operator!= ( const ColIterator& other) const{
			return col != other.col;
		}

		const variant<vector<optional<string>>, vector<optional<double>>>& operator*() const{
			return csvparser.dataset[col];
		}
	};

	ColIterator begin() const{
		return ColIterator(*this, 0);
	}

	ColIterator end() const{
		return ColIterator(*this, dataset.size());
	}


private:
	string input_file;
	vector<variant<vector<optional<string>>, vector<optional<double>>>> dataset;
	vector<string> header;
	int size;
};
