#pragma once

#include <format>
#include <memory>
#include <stdexcept>

namespace Utilits
{
    template <typename T>
    inline auto GetSharedPtr(std::weak_ptr<T> weakPtr)
    {
        auto sharedPtr = weakPtr.lock();
        if (sharedPtr == nullptr)
            throw std::runtime_error(std::format("Weak pointer has been empty. The type of this weak pointer: {}", typeid(typename decltype(weakPtr)::element_type).name()));
        
            return sharedPtr;
    }

    inline void DrawEmptyLine(std::size_t length)
    {
        for (std::size_t i = 0; i < length; ++i)
            std::wcout << L' ';
    }
}