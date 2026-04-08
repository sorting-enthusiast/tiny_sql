#include <print>
#include <iostream>
#include <string>
#include "table.h"
#include "tokenizer.h"
#include <algorithm>
namespace rngs = std::ranges;

int main() {
    std::vector v = {1,2,3,4,};
    std::println("{}", v);
    std::print("Welcome to the tiny_sql REPL!\nEnter .quit to quit\n>> ");
    std::string input;
    for (;;) if (std::getline(std::cin, input)) {
        auto tokens = Tokens(input);
        for (auto const& t: tokens) std::println("{}, {}",(int)t.type, t.value);
        if (rngs::any_of(tokens, [](auto&& t) { return t.value == ".quit"; })) break;
        std::print(">> ");
    }
    return 0;
}