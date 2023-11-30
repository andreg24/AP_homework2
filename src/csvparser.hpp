#include <fstream>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <string>
#include <variant>
#include <optional>
#include <map>
#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/covariance.hpp>


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
	void summary(const string& filename);
	void classification(string wanted, int col_idx);

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

    map<string, int> countFrequency(size_t col_idx);

    double covar(size_t col_idx1, size_t col_idx2);

    double correlation_analysis(size_t col_idx1, size_t col_idx2) {
		if (col_idx1 >= size || col_idx1 < 0 || col_idx2 >= size || col_idx2 < 0) {
            cerr << "Column index out of range." << endl;
            return 0.0;
        }
		optional<double> result;
		if (dev_std(col_idx1)==0 || dev_std(col_idx2)==0){
			throw runtime_error("Standard deviation is zero. You can't divide by zero!");			return result.value();
		}

        result=covar(col_idx1, col_idx2)/(dev_std(col_idx1)*dev_std(col_idx2));
		return result.value();
    }

	

private:
	string input_file;
	vector<variant<vector<optional<string>>, vector<optional<double>>>> dataset;
	vector<string> header;
	int size;
};
