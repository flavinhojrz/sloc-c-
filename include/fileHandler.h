#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "./file.h"

namespace fs = std::filesystem;

/**
 * @class fileHandler
 * @brief Class for handling file operations, including validation and processing.
 *
 * The fileHandler class provides functionalities to check file paths,
 * process files, and retrieve files from directories.
 */
class fileHandler {
private:
  std::string path; /**< Path to the input directory or file */

public:
  /**
   * @brief Constructor for the fileHandler class.
   *
   * @param inputPath Path to the directory or file to be processed.
   */
  fileHandler(const std::string& inputPath);

  /**
   * @brief Checks if the path is valid.
   *
   * @return True if the path is valid, otherwise false.
   */
  bool isValidPath() const;

  /**
   * @brief Checks if the path is a directory.
   *
   * @return True if the path is a directory, otherwise false.
   */
  bool isDirectory() const;

  /**
   * @brief Processes a document from the specified path.
   *
   * @param filePath The path to the file to be processed.
   * @return A File object containing information about the processed file.
   */
  File processFile(const std::string& filePath) const;

  /**
   * @brief Searches for files in the specified directory recursively.
   *
   * @return A vector of strings representing the paths of found files.
   */
  std::vector<std::string> getFilesInDirectoryRecursive() const;

  /**
   * @brief Searches for files only in the specified directory.
   *
   * @return A vector of strings representing the paths of found files.
   */
  std::vector<std::string> getFilesInDirectory() const;

  /**
   * @brief Main workflow to set files in the database.
   *
   * @param Db Reference to a vector of File objects where the processed files will be stored.
   * @param isRecursive Boolean flag to indicate if the search should be recursive.
   */
  void setFilesInDatabase(std::vector<File>& Db, bool isRecursive) const;

  /**
   * @brief Verifies if the file has a valid extension.
   *
   * @param filePath The path to the file to be checked.
   * @return True if the file extension is valid, otherwise false.
   */
  bool isValidExtension(const std::string& filePath) const;
};
