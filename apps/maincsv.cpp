#include "csvparser.hpp"

int main(int argc, char* argv[]) {
   // Check if the correct number of arguments is provided
   if (argc != 3) {
       std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
       return 1;
   }

   // Parse input and output filenames from command line arguments
   std::string input_file = argv[1];
   std::string output_file = argv[2];

   // Create an instance of CSVParser
   CSVParser parser(input_file);

   // Perform operations
   parser.read();
   parser.summary(output_file);
   string classificationfile="classificationresults.csv";
   parser.classification("Iris-setosa", 5, classificationfile);
   return 0;
}
