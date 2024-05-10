#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "readfile.hpp"


std::string parseFile(const std::string &filePath)
{
    std::ifstream file(filePath); // Open the file for reading
    std::string contents;         // This will store the file contents

    if (file.is_open()) {
        // Read each line of the file and append it to contents
        std::string line;
        while (std::getline(file, line)) {
            contents += line;
            contents += '\n';
        }
        contents += '\0';

        file.close(); // Close the file
    } else {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
    }

    return contents;
}
