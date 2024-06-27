#include <iostream>
#include <fstream>
#include <pbnjson.hpp>

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

    const pbnjson::JValue& root = parser.getDom();

    // Function to recursively print keys and values
    std::function<void(const pbnjson::JValue&, const std::string&)> printKeysValues =
        [&](const pbnjson::JValue& value, const std::string& prefix) {
            if (value.isObject()) {
                for (const auto& key : value.children()) {
                    printKeysValues(key.second, prefix + key.first.asString() + ".");
                }
            } else if (value.isArray()) {
                int index = 0;
                for (const auto& element : value.items()) {
                    printKeysValues(element, prefix + std::to_string(index++) + ".");
                }
            } else {
                std::cout << prefix << ": " << value.stringify() << std::endl;
            }
        };

    // Start parsing from the root
    printKeysValues(root, "");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file>" << std::endl;
        return 1;
    }

    const std::string json_file = argv[1];
    parseJson(json_file);

    return 0;
}
