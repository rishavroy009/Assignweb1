#include "json_reader.h"
#include <iostream>
#include <fstream>

void parseJsonValue(const pbnjson::JValue& value, std::ostream& output) {
    if (value.isObject()) {
        for (const auto& key : value.children()) {
            parseJsonValue(key.second, output); // Recursively parse nested objects or arrays
        }
    } else if (value.isArray()) {
        for (const auto& element : value.items()) {
            parseJsonValue(element, output); // Recursively parse array elements
        }
    } else {
        output << value.stringify() << " "; // Print the value and add space separator
    }
}

void parseJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    pbnjson::JDomParser parser;
    if (!parser.parseFile(filename.c_str(), pbnjson::JSchema::AllSchema())) {
        std::cerr << "Failed to parse JSON file: " << filename << std::endl;
        return;
    }

    pbnjson::JValue root = parser.getDom();
    parseJsonValue(root, std::cout); // Print parsed values to standard output
    std::cout << std::endl; // Add newline at the end
}
