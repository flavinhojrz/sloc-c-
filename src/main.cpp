#include <iostream>
#include "../include/fileHandler.h"
#include "../include/outputHandler.h"

const std::string HELP_FILE_PATH = "./help.txt";

void processHelpOption(const outputHandler& output, const std::string& arg) {
    if (arg == "-h" || arg == "--help") {
        output.printHelpMessage(HELP_FILE_PATH);
        std::exit(0);
    }
}

void validateOptions(int argc, char* argv[], bool& hasValidOption, bool& invalidOptionDetected, bool& attemptedSortWithoutFlag) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help" || arg == "-r" || arg == "-s" || arg == "-S") {
            hasValidOption = true;
            return;
        }
        if (arg.find_first_not_of("ftcbsa") == std::string::npos) {
            attemptedSortWithoutFlag = true;
        }
        if (arg[0] == '-' && arg != "-h" && arg != "--help" && arg != "-r" && arg != "-s" && arg != "-S") {
            invalidOptionDetected = true;
        }
    }
}

std::pair<std::string, std::string> processSortOption(int argc, char* argv[], int& i) {
    std::pair<std::string, std::string> sortOption;
    if (argv[i] == std::string("-s") || argv[i] == std::string("-S")) {
        if (i + 1 >= argc) {
            std::cerr << "Argument expected after sort option! (f | t | c | b | s | a)\n";
            std::exit(1);
        }
        sortOption = { argv[i], argv[++i] };
        if (sortOption.second.find_first_not_of("ftcbsa") != std::string::npos) {
            std::cerr << "Invalid option! (f | t | c | b | s | a)\n";
            std::exit(1);
        }
    }
    return sortOption;
}

void processFiles(int argc, char* argv[], std::vector<File>& Db, bool isRecursive) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') continue;
        fileHandler handler(arg);
        handler.setFilesInDatabase(Db, isRecursive);
    }
    if (Db.empty()) {
        std::cerr << "No valid files found!\n";
        std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    outputHandler output;
    bool hasValidOption = false, attemptedSortWithoutFlag = false, invalidOptionDetected = false;

    validateOptions(argc, argv, hasValidOption, invalidOptionDetected, attemptedSortWithoutFlag);

    if (invalidOptionDetected || (!hasValidOption && argc > 1)) {
        std::cerr << "Error: Use -h for help on options\n";
        return 1;
    }

    if (argc < 2 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        output.printHelpMessage(HELP_FILE_PATH);
        return 0;
    }

    std::vector<File> Db;
    std::pair<std::string, std::string> sortOption;
    bool isRecursive = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        processHelpOption(output, arg);

        if (arg == "-r") isRecursive = true;

        auto tempSortOption = processSortOption(argc, argv, i);
        if (!tempSortOption.first.empty() && sortOption.first.empty()) {
            sortOption = tempSortOption;
        }
    }

    processFiles(argc, argv, Db, isRecursive);
    output.outputFormatted(Db, Db.size(), sortOption);

    return 0;
}
