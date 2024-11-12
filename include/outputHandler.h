#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "./file.h"

/**
 * @class outputHandler
 * @brief Class for handling the output formatting and error messages.
 *
 * The outputHandler class provides methods for displaying formatted output,
 * error messages, and help information.
 */
class outputHandler {
public:
  /**
   * @brief Outputs formatted information about the processed files.
   *
   * @param db Reference to a vector of File objects containing the processed files.
   * @param filesProcessed The number of files that have been processed.
   * @param options A pair of strings representing sorting options.
   */
  void outputFormatted(std::vector<File>& db,
                       int filesProcessed,
                       std::pair<std::string, std::string> options);

  /**
   * @brief Prints the header for the output table.
   *
   * @param filesProcessed The number of files processed.
   * @param fileNameWidth The width for formatting file names in the output.
   */
  void printHeader(int filesProcessed, int fileNameWidth);

  /**
   * @brief Gets the width of the largest file name for formatting purposes.
   *
   * @param db Reference to a vector of File objects.
   * @return The width of the largest file name.
   */
  int getLargestFileNameWidth(const std::vector<File>& db);

  /**
   * @brief Prints the help message from the specified file.
   *
   * @param filePath The path to the help file.
   */
  static void printHelpMessage(const std::string& filePath);

  /**
   * @brief Prints an error message and exits the program.
   *
   * @param message The error message to be printed.
   */
  void printErrorAndExit(const std::string message);
};
