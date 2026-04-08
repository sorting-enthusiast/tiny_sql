#include "tokenizer.h"
#include <cassert>
#include <charconv>
#include <string_view>
#include <unordered_set>
using std::operator""sv;
static const std::unordered_set<std::string_view> keywords{"CREATE"sv, "TABLE"sv, "INSERT"sv, "INTO"sv, "VALUES"sv, "INTEGER"sv, "TEXT"sv, "SELECT"sv, "FROM"sv, "WHERE"sv, "DELETE"sv, "DROP"sv, ".quit", ".tables"};

// does not currently deal with multi-word string literals, and defaults to identifier
Tokens::Tokens(std::string_view input) {
    auto process_token = [this](auto&& token) {
        int r;
        if (keywords.contains(token)) emplace_back(TokenType::KEYWORD, token);
        else if (token == "="sv) emplace_back(TokenType::SYMBOL, token);
        else if (token.starts_with("'") && token.ends_with("'") && token.length() > 1) {
            token.remove_prefix(1);
            token.remove_suffix(1);
            emplace_back(TokenType::LITERAL, token);
        }
        else if (auto[ptr, ec] = std::from_chars(token.data(), token.data() + token.length(), r); ec == std::errc{} && ptr == token.data() + token.length()) emplace_back(TokenType::LITERAL, token);
        else emplace_back(TokenType::IDENTIFIER, token);
    };
    const auto delims = " \t(){},"sv;
    while (!input.empty()) {
        if (auto i = input.find_first_of(delims); i != std::string_view::npos) {
            auto token = input.substr(0, i);
            input.remove_prefix(i + 1);
            if (token.empty()) continue;
            process_token(token);
        } else {
            process_token(input);
            break;
        }
    }
}