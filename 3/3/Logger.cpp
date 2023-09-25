#include "Logger.h"
#include <fstream>
#include <iostream>

void ConsoleLogger::print(const std::string& message) {
    std::cout << message << "\n";
};

void FileLogger::print(const std::string& message) {
    std::ofstream file(path_, std::ios::app);
    file << message << "\n";
};