#include "csvparser.hpp"

int main() {


	CSVParser A("top_english_movies.csv");
	A.read();
	
	std::cout<< "La media è: "<<A.mean_col(0)<< ". La varianza è: "<< A.var_col(0)<< ". La mediana è: "<< A.median_col(0)<< ". La deviazione standard è: "<< A.dev_std(0)<<std::endl;
	
	  for (const auto& col: A){
		std::cout<<"cambio colonna"<<std::endl;
		if (holds_alternative<vector<optional<string>>>(col)) {
           const auto& str_vec = get<vector<optional<string>>>(col);
           if (!str_vec.empty()) {
               cout << *str_vec[0] << endl;
           }
       } else if (holds_alternative<vector<optional<double>>>(col)) {
           const auto& double_vec = get<vector<optional<double>>>(col);
           if (!double_vec.empty()) {
               cout << *double_vec[0] << endl;
           }
  }}
	
}
