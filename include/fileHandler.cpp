#include "./fileHandler.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "./file.h"

// Allowed types
const std::vector<std::string> ALLOWED_EXTENSIONS = { "c", "cpp", "h", "hpp", "py" };

fileHandler::fileHandler(const std::string& inputPath) : path(inputPath) {}

bool fileHandler::isValidPath() const { return fs::exists(path); }

bool fileHandler::isDirectory() const { return fs::is_directory(path); }

bool fileHandler::isValidExtension(const std::string& filePath) const {
  size_t dotPos = filePath.rfind('.');
  if (dotPos == std::string::npos)
    return false;

  std::string extension = filePath.substr(dotPos + 1);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

  // Check if the extension is allowed.
  return std::find(ALLOWED_EXTENSIONS.begin(), ALLOWED_EXTENSIONS.end(), extension)
         != ALLOWED_EXTENSIONS.end();
}

// Processes a file to count the number of lines, blank lines, comment lines, and code lines
File fileHandler::processFile(const std::string& filePath) const {
  std::fstream cfile(filePath);
  using count_t = unsigned long;
  bool inBlockComment = false;  // Bool to indicate if we're inside a block comment
  bool inString = false;        // Bool to indicate if we're inside a string
  count_t lineCount{};
  count_t blankLines{};
  count_t commentLines{};
  count_t codeLines{};
  std::string line{};

  // Determine the file type based on the extension
  size_t dotPos = filePath.rfind('.');
  std::string fileType = "UNDEF";

  if (dotPos != std::string::npos) {
    std::string extension = filePath.substr(dotPos + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension == "c")
      fileType = "C";
    else if (extension == "py")
      fileType = "PYTHON";
    else if (extension == "cpp")
      fileType = "CPP";
    else if (extension == "h")
      fileType = "H";
    else if (extension == "hpp")
      fileType = "HPP";
  }

  // If the file is open, start processing each line
  if (cfile.is_open()) {
    while (std::getline(cfile, line)) {
      lineCount++;  // Increment the total line count

      // Check if the line is blank (completely empty or just whitespace)
      if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
        if (inBlockComment) {
          // If we're in a block comment, count it as a comment line but do not increment blankLines
          commentLines++;
        } else {
          blankLines++;  // Only count as a blank line if not in a block comment
        }
        continue;
      }

      bool hasCode = false;
      bool hasComment = false;
      size_t i = 0;

      // Parse each character in the line to identify code, comments, or strings
      while (i < line.size()) {
        if (line[i] == '"') {
          inString = !inString;  // Toggle the string state
        }

        if (!inString) {
          // Detect line comments (//) and block comments (/* ... */)
          if (!inBlockComment && line[i] == '/' && i + 1 < line.size()) {
            if (line[i + 1] == '/') {  // Single-line comment
              hasComment = true;
              break;                          // The rest of the line is a comment
            } else if (line[i + 1] == '*') {  // Start of a block comment
              inBlockComment = true;
              hasComment = true;
              i += 2;  // Move past the beginning of the block comment
              continue;
            }
          }

          // If in a block comment, check if it ends in the current line
          if (inBlockComment) {
            size_t endBlockPos = line.find("*/", i);
            if (endBlockPos != std::string::npos) {
              inBlockComment = false;
              hasComment = true;    // Block comment ended
              i = endBlockPos + 2;  // Move past the end of the block comment
              continue;
            } else {
              hasComment = true;  // The entire line is a block comment
              break;
            }
          }

          if (!isspace(line[i])) {
            hasCode = true;  // Found code
          }
        }

        i++;
      }

      // Final count: a line with both code and comment is counted for both
      if (hasCode) {
        codeLines++;
      }
      if (hasComment) {
        commentLines++;
      }
    }

    // If the file ends while still in a block comment, increment comment lines
    if (inBlockComment) {
      commentLines++;
    }
  } else {
    std::cerr << ">>>> Error opening file!\n";
  }

  return File(filePath, fileType, blankLines, commentLines, codeLines, lineCount);
}
std::vector<std::string> fileHandler::getFilesInDirectoryRecursive() const {
  std::vector<std::string> files;
  for (const auto& entry : fs::recursive_directory_iterator(path)) {
    if (fs::is_regular_file(entry.path())) {
      files.push_back(entry.path().string());
    }
  }
  return files;
}

std::vector<std::string> fileHandler::getFilesInDirectory() const {
  std::vector<std::string> files;
  for (const auto& entry : fs::directory_iterator(path)) {
    if (fs::is_regular_file(entry.path())) {
      files.push_back(entry.path().string());
    }
  }
  return files;
}

void fileHandler::setFilesInDatabase(std::vector<File>& Db, bool isRecursive) const {
  if (!isValidPath()) {
    return;
  }
  std::vector<std::string> paths;
  // Check if it is a directory and set the mode
  if (isDirectory()) {
    paths = isRecursive ? getFilesInDirectoryRecursive() : getFilesInDirectory();
  }
  // Check if it is a file with a valid extension
  else if (isValidExtension(path)) {
    paths.push_back(path);
  }
  // If it is neither a valid directory nor a valid file, display an error.
  else {
    std::cout << ">>>> Error: File with invalid extension: " << path << "\n";
    return;
  }
  // Process each found file
  for (const auto& filePath : paths) {
    if (isValidExtension(filePath)) {
      Db.push_back(processFile(filePath));
    }
  }
}
