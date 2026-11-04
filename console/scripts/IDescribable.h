#pragma once
#include <string>

class IDescribable
{
public:
    virtual ~IDescribable() noexcept = default;
    virtual std::string Describe() const = 0;
};
