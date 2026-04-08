#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>
#include <string_view>
enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    SYMBOL
};

struct Token {
    TokenType type;
    std::string_view value; // string_views to reduce allocations sizes
};

struct Tokens : std::vector<Token> {
    explicit Tokens(std::string_view input); // technically not noexcept, but should only throw if emplace_back throws
};

#endif