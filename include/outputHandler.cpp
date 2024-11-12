#include "./outputHandler.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "./file.h"

// Function to print help message from a specified help file
void outputHandler::printHelpMessage(const std::string& HELP_FILE_PATH) {
  std::ifstream helpFile(HELP_FILE_PATH);
  if (!helpFile) {
    std::cerr << "Help file not specified at this path: " << HELP_FILE_PATH << "\n";
    return;
  }

  std::string line;
  // Read each line from the help file and print it to the console
  while (std::getline(helpFile, line)) {
    std::cout << line << "\n";
  }

  helpFile.close();
  std::exit(0);  // Exit the program after printing help
}

// Function to print an error message and exit the program
void outputHandler::printErrorAndExit(const std::string message) {
  std::cout << ">>>> Error: " << message << "\n";
  std::exit(-1);  // Exit with an error status
}

// Function to print the header of the output table
void outputHandler::printHeader(int filesProcessed, int fileNameWidth) {
  std::cout << "Files processed: " << filesProcessed << "\n";
  std::cout << "-----------------------------------------------------------------------------------"
               "--------------------------------------------------------\n";
  // Print column headers with specified widths
  std::cout << std::left << std::setw(fileNameWidth) << "Filename";
  std::cout << std::left << std::setw(20) << "Language";
  std::cout << std::left << std::setw(15) << "Comments";
  std::cout << std::left << std::setw(15) << "Blank";
  std::cout << std::left << std::setw(15) << "Code";
  std::cout << std::left << std::setw(15) << "All"
            << "\n";
  std::cout << "-----------------------------------------------------------------------------------"
               "--------------------------------------------------------\n";
}

// Function to determine the maximum width of file names for table formatting
int outputHandler::getLargestFileNameWidth(const std::vector<File>& files) {
  int maxWidth = 8;  // Minimum width for "Filename"
  for (const auto& file : files) {
    int length = file.getFileName().length();
    if (length > maxWidth) {
      maxWidth = length;  // Update maxWidth if a longer filename is found
    }
  }
  return maxWidth + 2;  // Add some padding
}

// Function to output formatted data about processed files
void outputHandler::outputFormatted(std::vector<File>& Db,
                                    int filesProcessed,
                                    std::pair<std::string, std::string> options) {
  int largestFileNameWidth = getLargestFileNameWidth(Db);
  printHeader(filesProcessed, largestFileNameWidth);
  // Check the sorting option
  bool reverseOrder = (options.first == "-S");  // `-S` indicates reverse sorting
  char sortOption
    = options.second[0];  // The first character of the second option defines the sort field

  // Comparison lambda function for sorting files based on the selected criteria
  auto compare = [sortOption](const File& a, const File& b) {
    switch (sortOption) {
    case 'f':
      return a.getFileName() < b.getFileName();
    case 't':
      return a.getFileType() < b.getFileType();
    case 'c':
      return a.getComments() < b.getComments();
    case 'b':
      return a.getBlankLines() < b.getBlankLines();
    case 's':
      return a.getnCodes() < b.getnCodes();
    case 'a':
      return a.getLines() < b.getLines();
    default:
      return false;  // Safety case for unexpected sort option
    }
  };

  // Sort the Db vector according to the selected option
  if (reverseOrder) {
    std::sort(Db.begin(), Db.end(), [compare](const File& a, const File& b) {
      return !compare(a, b);  // Invert the comparison for reverse order
    });
  } else {
    std::sort(Db.begin(), Db.end(), compare);  // Normal sorting
  }

  // Output the formatted data for each file
  for (size_t i = 0; i < Db.size(); i++) {
    std::cout << std::left << std::setw(largestFileNameWidth) << Db[i].getFileName();
    std::cout << std::left << std::setw(20) << Db[i].getFileType();
    std::cout << std::left << std::setw(15)
              << std::to_string(Db[i].getComments()) + " " + Db[i].getPercentageComments();
    std::cout << std::left << std::setw(15)
              << std::to_string(Db[i].getBlankLines()) + " " + Db[i].getPercentageBlank();
    std::cout << std::left << std::setw(15)
              << std::to_string(Db[i].getnCodes()) + " " + Db[i].getPercentageCode();
    std::cout << std::left << std::setw(15) << Db[i].getLines() << "\n";
  }

  std::cout << "-----------------------------------------------------------------------------------"
               "--------------------------------------------------------\n";
}
