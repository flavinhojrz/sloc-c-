#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using count_t = unsigned long;

/**
 * @class File
 * @brief Class representing a file with information about its content.
 *
 * The File class stores information about a file, including its name,
 * type, and counts of blank lines, comments, and code.
 */
class File {
private:
  std::string fileName; /**< File name */
  std::string fileType; /**< File type (extension) */
  count_t nBlank;       /**< Number of blank lines */
  count_t nComments;    /**< Number of comment lines */
  count_t nCode;        /**< Number of code lines */
  count_t nLines;       /**< Total number of lines */

public:
  /**
   * @brief Constructor for the File class.
   *
   * @param name File name.
   * @param type File type (extension).
   * @param blankLines Number of blank lines.
   * @param comments Number of comment lines.
   * @param loc Number of code lines.
   * @param lines Total number of lines.
   */
  File(const std::string& name,
       std::string type,
       count_t blankLines,
       count_t comments,
       count_t loc,
       count_t lines)
      : fileName(name), fileType(type), nBlank(blankLines), nComments(comments), nCode(loc),
        nLines(lines) {}

  /**
   * @brief Gets the file name.
   *
   * @return File name.
   */
  std::string getFileName() const { return fileName; }

  /**
   * @brief Gets the file type.
   *
   * @return File type.
   */
  std::string getFileType() const { return fileType; }

  /**
   * @brief Gets the number of blank lines.
   *
   * @return Number of blank lines.
   */
  count_t getBlankLines() const { return nBlank; }

  /**
   * @brief Gets the number of comment lines.
   *
   * @return Number of comment lines.
   */
  count_t getComments() const { return nComments; }

  /**
   * @brief Gets the number of code lines.
   *
   * @return Number of code lines.
   */
  count_t getnCodes() const { return nCode; }

  /**
   * @brief Gets the total number of lines.
   *
   * @return Total number of lines.
   */
  count_t getLines() const { return nLines; }

  /**
   * @brief Gets the percentage of blank lines relative to total lines.
   *
   * @return Formatted string with the percentage of blank lines.
   */
  std::string getPercentageBlank() const {
    if (nLines == 0)
      return "(0%)";
    return formatPercentage((nBlank * 100.0) / nLines);
  }

  /**
   * @brief Gets the percentage of comment lines relative to total lines.
   *
   * @return Formatted string with the percentage of comment lines.
   */
  std::string getPercentageComments() const {
    if (nLines == 0)
      return "(0%)";
    return formatPercentage((nComments * 100.0) / nLines);
  }

  /**
   * @brief Gets the percentage of code lines relative to total lines.
   *
   * @return Formatted string with the percentage of code lines.
   */
  std::string getPercentageCode() const {
    if (nLines == 0)
      return "(0%)";
    return formatPercentage((nCode * 100.0) / nLines);
  }

private:
  /**
   * @brief Formats a value as a percentage.
   *
   * @param value Value to be formatted.
   * @return Formatted string with the percentage value.
   */
  std::string formatPercentage(double value) const {
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << value;
    return "(" + out.str() + "%)";
  }
};
