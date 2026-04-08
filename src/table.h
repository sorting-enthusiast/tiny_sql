#ifndef TABLE_H
#define TABLE_H
#include <unordered_map>
#include <string>
#include <vector>
#include <iterator>
#include <variant>
#include <expected>
using Value = std::variant<int, std::string>;

struct Column {
    std::string name;
    enum Type { INTEGER, TEXT } type;
};

struct Table {
    std::vector<Column> columns;
    std::vector<std::vector<Value>> rows;
};
using Database = std::unordered_map<std::string, Table>;
#endif