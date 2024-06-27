#include "json_reader.h"
#include <iostream>
#include <vector>

void collectJsonData(const pbnjson::JValue &value, std::vector<std::string> &keys, std::vector<std::string> &values) {
    if (value.isObject()) {
        for (const auto &key : value.children()) {
            keys.push_back(key.first.asString());
            collectJsonData(key.second, keys, values);
        }
    } else if (value.isArray()) {
        for (const auto &element : value.items()) {
            collectJsonData(element, keys, values);
        }
    } else {
        values.push_back(value.stringify());
    }
}