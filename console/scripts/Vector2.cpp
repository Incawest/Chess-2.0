#include "Vector2.h"

Vector2::Vector2() noexcept = default;

Vector2::Vector2(int row, int col) noexcept : row{row}, col{col}
{
}

Vector2 Vector2::operator-() const noexcept
{
    return Vector2{-row, -col};
}

Vector2& Vector2::operator+=(const Vector2& other) noexcept
{
    row += other.row;
    col += other.col;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) noexcept
{
    row -= other.row;
    col -= other.col;
    return *this;
}

Vector2& Vector2::operator*=(const int& other) noexcept
{
    row *= other;
    col *= other;
    return *this;
}

Vector2& Vector2::operator/=(const int& other)
{
    row /= other;
    col /= other;
    return *this;
}

Vector2 operator+(Vector2 first, const Vector2& second) noexcept
{
    return first += second;
}

Vector2 operator-(Vector2 first, const Vector2& second) noexcept
{
    return Vector2{first.row - second.row, first.col - second.col};
}

Vector2 operator*(Vector2 vector, int factor) noexcept
{
    return vector *= factor;
}

Vector2 operator/(Vector2 vector, int factor)
{
    return vector /= factor;
}

bool operator==(const Vector2& first, const Vector2& other) noexcept
{
    return first.row == other.row && first.col == other.col;
}

double Vector2::GetVectorLength() const noexcept
{
    return sqrt(row * row + col * col);
}