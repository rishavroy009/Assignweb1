#ifndef JSON_READER_H
#define JSON_READER_H

#include <pbnjson.hpp>
#include <vector>
#include <string>

void collectJsonData(const pbnjson::JValue &value, std::vector<std::string> &keys, std::vector<std::string> &values);

#endif // JSON_READER_H
