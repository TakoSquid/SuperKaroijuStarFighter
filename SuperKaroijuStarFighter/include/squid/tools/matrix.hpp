#pragma once

#include <m3dia.hpp>
#include <vector>

namespace squid
{
    using Matrix = std::vector<std::vector<float>>;

    Matrix createTranslationMatrix(float x, float y);
    Matrix createTranslationMatrix(m3d::Vector2f vec);
    Matrix createRotationMatrix(float angle);
    Matrix createScaleMatrix(float x, float y);
    Matrix createScaleMatrix(m3d::Vector2f vec);
    Matrix createScaleMatrix(float scale);
    Matrix createIdentity(int size);

    Matrix multiply(const Matrix &left, const Matrix &right);
    m3d::Vector2f multiply(const squid::Matrix &mat, const m3d::Vector2f &vec);
} // namespace squid

squid::Matrix operator*(const squid::Matrix &left, const squid::Matrix &right);
m3d::Vector2f operator*(const squid::Matrix &mat, const m3d::Vector2f &vec);
std::ostream &operator<<(std::ostream &out, const squid::Matrix &vec);
