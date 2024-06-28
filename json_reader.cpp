#include <iostream>
#include <fstream>
#include <pbnjson.hpp>

using namespace pbnjson;
using namespace std;

int main() {
    JDomParser parser;
    JValue parsed;

    ifstream file("path/to/your/json/file.json");
    string json_str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    if (!parser.parse(json_str, parsed)) {
        cerr << "Failed to parse JSON: " << parser.errorString() << endl;
        return 1;
    }

    // Process the parsed JSON data

    return 0;
}
