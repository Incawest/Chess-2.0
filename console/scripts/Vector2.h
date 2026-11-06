#pragma once

#include <math.h>

class Vector2
{
public:
    int row = 0;
    int col = 0;
public:
    Vector2() noexcept;
    Vector2(int row, int col) noexcept;
    Vector2 operator-() const noexcept;
    Vector2& operator+=(const Vector2& other) noexcept;
    Vector2& operator-=(const Vector2& other) noexcept;
    Vector2& operator*=(const int& other) noexcept;
    Vector2& operator/=(const int& other);

    friend Vector2 operator+(Vector2 first, const Vector2& second) noexcept;
    friend Vector2 operator-(Vector2 first, const Vector2& second) noexcept;
    friend Vector2 operator*(Vector2 vector, int factor) noexcept;
    friend Vector2 operator/(Vector2 vector, int factor);
    friend bool operator==(const Vector2& first, const Vector2& second) noexcept;

    double GetVectorLength() const noexcept;
};