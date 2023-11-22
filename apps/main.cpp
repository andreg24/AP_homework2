#include "csvparser.hpp"

int main() {


	CSVParser A("top_english_movies2.csv");
	A.read();
	
	std::cout<< "La media è: "<<A.mean_col(0)<< ". La varianza è: "<< A.var_col(0)<< ". La mediana è: "<< A.median_col(0)<< ". La deviazione standard è: "<< A.dev_std(0)<< ". La correlazione è: "<< A.correlation_analysis(0,2)<<std::endl;
	
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

  map<string, int> freq = A.countFrequency(2);
  for (const auto& pair : freq ) {
    cout<< "Elemento: " << pair.first << " Frequenza: " << pair.second<< std::endl;
  }

  std::string filename = "output.txt";
  A.summary(filename);
	
}
