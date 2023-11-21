#include "csvparser.hpp"

int main() {
//	CSVParser A("csv_examples/top_english_movies.csv");

	CSVParser A("csv_examples/prove.csv");
	A.read();
	vector<variant<vector<optional<string>>, vector<optional<double>>>> x = A.getDataset();
	/*
	cout << x.size() << endl;;
	vector<optional<double>> y = get<vector<optional<double>>>(x[1]);
	cout << y[4].value() << endl;
	cout << "-----" << endl;
	variant<optional<string>, optional<double>> a = A(4,1);
  optional<double> b = get<optional<double>>(a);
	cout << b.value() << endl;
	*/
}
