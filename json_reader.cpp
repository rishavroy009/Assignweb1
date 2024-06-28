#include <iostream>
#include <fstream>
#include <string>
#include <pbnjson.hpp>

using namespace pbnjson;
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <json_file>" << endl;
        return 1;
    }

    const char* json_filename = argv[1];

    // Read JSON file into a string
    ifstream file(json_filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << json_filename << endl;
        return 1;
    }

    string json_str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Parse JSON
    JDomParser parser;
    JValue parsed;

    if (!parser.parse(json_str, parsed)) {
        cerr << "Failed to parse JSON: " << parser.errorString() << endl;
        return 1;
    }

    // Access JSON data
    if (parsed.isObject()) {
        JValue::Object jsonObj = parsed.asObject();
        for (const auto& pair : jsonObj) {
            cout << "Key: " << pair.first << ", Value: " << pair.second.asString() << endl;
        }
    } else {
        cerr << "JSON root is not an object" << endl;
        return 1;
    }

    return 0;
}
