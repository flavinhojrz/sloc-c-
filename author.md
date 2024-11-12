# Introduction
The Source Lines of Code (SLOC) project aims to provide developers and project managers with a clear understanding of their codebase by accurately counting and categorizing lines of code, comments, and blank lines across multiple programming files. In today's fast-paced software development environment, measuring code quality and maintainability is crucial for effective project management and team productivity.

This project includes a C++ implementation that processes source files written in languages, currently supporting C, C++. The program is designed to analyze both individual files and entire directories, allowing for recursive file searching. It counts total lines, blank lines, comment lines, and lines of code, presenting the results in a well-formatted output table.

- Remember, every part of code was formatted with Clang.

# Author(s)

Kauã do Vale Ferreira <- kkvale27@gmail.com

Flavio Oliveira da Silva Junior <-flavinhoj78@gmail.com

# Problems found or limitations

One significant challenge encountered was ensuring accurate line counting. Despite reviewing the project specifications, we continually discovered new edge cases that could lead to errors in our calculations.

Additionally, we cannot be 100% certain about how the program will handle very large files—whether it will crash or if it can accurately count the lines. This uncertainty necessitated considerable effort during development.

Ultimately, we were unable to implement support for additional languages, particularly Python, as we had originally intended, which would include support for comments using # and '''.
# Grading

| Item                                                | Valor máximo | Valor esperado |
| --------------------------------------------------- | :----------: | :------------: |
| Read a single source file                           |      10      |       10       |
| Read a list of files from a directory               |      15      |       15       |
| Show help as requested `-h`                         |      4       |       4        |
| Treat error situations                              |      8       |       8        |
| Show correct number of blank lines                  |      5       |       5        |
| Show correct number of comment lines                |      10      |       8       |
| Show correct number of code lines                   |      10      |       8        |
| Show correct number of total lines                  |      5       |       5        |
| Show the type of source file                        |      5       |       5        |
| Show percentages as requested                       |      10      |       8        |
| Show consolidation at the bottom of a table         |      5       |       5        |
| Table is formatted as requested                     |      8       |       8        |
| The project contains at least one struct or classes |      5       |       5        |

# Compiling and Runnig

Step 1 : g++ -std=c++17 -o slockf src/main.cpp include/fileHandler.cpp include/outputHandler.cpp (On main directory)

Step 2 : ./slockf src -arg 