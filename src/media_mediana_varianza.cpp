#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>
#include <numeric>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/median.hpp>


using namespace boost::accumulators;

class CSVParser {
public:
  // Constructor
  CSVParser(const std::string input_file) : input_file(input_file) {}


  // Parser function

  void read() {
    std::ifstream file(input_file);
    std::string line;
    bool columns_allocated = false;

    //header

    std::getline(file, line);
    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, ',')) {
      header.push_back(cell);
    }

    while (std::getline(file, line)) {
      std::stringstream lineStream(line);
      //std::string cell;
      if (!columns_allocated) {
        while (std::getline(lineStream, cell, ',')) {
          try {
            double value = std::stod(cell); // try to convert to double
            dataset.push_back(std::vector<double>{value});
            } 
          catch (std::invalid_argument&) {
            dataset.push_back(std::vector<std::string>{cell}); // if conversion fails, it's a string
            }
        }
        columns_allocated = true;
      }

      int counter = 0; // col index counter
      while (std::getline(lineStream, cell, ',')) {
        if (std::holds_alternative<std::vector<std::string>>(dataset[counter])) {
          std::get<std::vector<std::string>>(dataset[counter]).push_back(cell);
        } 
        else if (std::holds_alternative<std::vector<double>>(dataset[counter])) {
          double value = std::stod(cell);
          std::get<std::vector<double>>(dataset[counter]).push_back(value);
          }
        ++counter;
      }
    }
  }

  // Print function

  void print() {
    std::cout<<"printing the header"<<std::endl;
    for (unsigned int n=0; n<header.size();n++){
      std::cout<<header[n]<<" ";
      }
    std::cout<<std::endl;
    std::cout<<"col"<<dataset.size();
    std::cout<< "row"<< std::get<std::vector<double>>(dataset[0]).size()<<"\n";
    for (const auto& column : dataset) {
      if (std::holds_alternative<std::vector<std::string>>(column)) {
        const auto& string_column = std::get<std::vector<std::string>>(column);
        for (const auto& cell : string_column) {
          std::cout << cell << " ";
        }
        std::cout << "\n";
      }
      else if (std::holds_alternative<std::vector<double>>(column)) {
        const auto& double_column = std::get<std::vector<double>>(column);
        for (const auto& cell : double_column) {
          std::cout << cell << " ";
        }
        std::cout << "\n";
      }
    }
  }

  /*double mean(size_t col_idx) {
    if (col_idx >= dataset.size() || col_idx < 0) {
            std::cerr << "Column index out of range." << std::endl;
            return 0.0;
        }

    if (std::holds_alternative<std::vector<double>>(dataset[col_idx])) {
      const auto& double_column = std::get<std::vector<double>>(dataset[col_idx]);
      if (double_column.empty()) {
        std::cerr << "Column is empty." << std::endl;
        return 0.0;
      }
      
      double sum = std::accumulate(double_column.begin(), double_column.end(), 0.0);
      return sum / double_column.size();
    }
    else {
      std::cerr << "Column is not numeric." << std::endl;
      return 0.0;
    }
  }*/

  double mean_col(size_t col_idx) {
        if (col_idx >= dataset.size() || col_idx < 0) {
            std::cerr << "Column index out of range." << std::endl;
            return 0.0;
        }

        if (std::holds_alternative<std::vector<double>>(dataset[col_idx])) {
            const auto& double_column = std::get<std::vector<double>>(dataset[col_idx]);
            if (double_column.empty()) {
                std::cerr << "Column is empty." << std::endl;
                return 0.0;
            }

            boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
            for (const auto& val : double_column) {
                acc(val);
            }

            return boost::accumulators::mean(acc);
        } else {
            std::cerr << "Column is not numeric." << std::endl;
            return 0.0;
        }
  }

  double var_col(size_t col_idx) {
        if (col_idx >= dataset.size() || col_idx < 0) {
            std::cerr << "Column index out of range." << std::endl;
            return 0.0;
        }

        if (std::holds_alternative<std::vector<double>>(dataset[col_idx])) {
            const auto& double_column = std::get<std::vector<double>>(dataset[col_idx]);
            if (double_column.empty()) {
                std::cerr << "Column is empty." << std::endl;
                return 0.0;
            }

            boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc;
            for (const auto& val : double_column) {
                acc(val);
            }

            return boost::accumulators::variance(acc);
        } else {
            std::cerr << "Column is not numeric." << std::endl;
            return 0.0;
        }
  }

  double median_col(size_t col_idx) {
        if (col_idx >= dataset.size() || col_idx < 0) {
            std::cerr << "Column index out of range." << std::endl;
            return 0.0;
        }

        if (std::holds_alternative<std::vector<double>>(dataset[col_idx])) {
            const auto& double_column = std::get<std::vector<double>>(dataset[col_idx]);
            if (double_column.empty()) {
                std::cerr << "Column is empty." << std::endl;
                return 0.0;
            }

            accumulator_set<double, stats<tag::median(with_p_square_quantile)>> acc;
            for (const auto& val : double_column) {
                acc(val);
            }

            return median(acc);
        } else {
            std::cerr << "Column is not numeric." << std::endl;
            return 0.0;
        }
  }

  double dev_std(size_t col_idx) {
    return std::sqrt(var_col(col_idx));
  }

private:
  std::string input_file;
  std::vector<std::variant<std::vector<std::string>, std::vector<double>>> dataset;
  std::vector<std::string> header;
  
};

 




int main() {
  CSVParser A = CSVParser("top_english_movies2.csv");
  
  A.read();
  //A.print();
  std::cout<< "La media è: "<<A.mean_col(0)<< ". La varianza è: "<< A.var_col(0)<< ". La mediana è: "<< A.median_col(0)<< ". La deviazione standard è: "<< A.dev_std(0)<<std::endl;
  
  return 0;
}
