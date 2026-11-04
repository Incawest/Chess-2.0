#pragma once
#include <stdexcept>
#include <string>

class ChessRuleException : public std::runtime_error
{
public:
    explicit ChessRuleException(const std::string& message) : std::runtime_error(message) {}
};
