#include <iostream>
#include <fstream>
#include <pbnjson.hpp> // Include the pbnjson header

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <json_file>" << endl;
        return 1;
    }

    const char* json_file = argv[1];

    // Initialize the JSON parser
    pbnjson::JDomParser parser;
    std::string error;

    // Read the JSON file
    ifstream file(json_file);
    if (!file.is_open()) {
        cerr << "Failed to open JSON file: " << json_file << endl;
        return 1;
    }

    // Parse the JSON content
    if (!parser.parse(file, pbnjson::JSchemaFragment("{}"), &error)) {
        cerr << "Failed to parse JSON: " << error << endl;
        return 1;
    }

    // Get the root of the parsed JSON
    pbnjson::JValue root = parser.getDom();

    // Iterate over the JSON object to print keys and values
    if (root.isObject()) {
        for (auto& key : root.children()) {
            cout << "Key: " << key.first.asString() << ", Value: " << key.second.asString() << endl;
        }
    } else {
        cerr << "Root element is not an object!" << endl;
        return 1;
    }

    return 0;
}
