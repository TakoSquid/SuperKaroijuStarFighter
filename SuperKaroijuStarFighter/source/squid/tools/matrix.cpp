#include "matrix.hpp"

namespace squid
{
    Matrix createTranslationMatrix(float x, float y)
    {
        return Matrix{{1, 0, x}, {0, 1, y}, {0, 0, 1}};
    }

    Matrix createTranslationMatrix(m3d::Vector2f vec)
    {
        return createTranslationMatrix(vec.u, vec.v);
    }

    Matrix createScaleMatrix(float x, float y)
    {
        return Matrix{{x, 0, 0}, {0, y, 0}, {0, 0, 1}};
    }

    Matrix createScaleMatrix(float scale)
    {
        return createScaleMatrix(scale, scale);
    }

    Matrix createScaleMatrix(m3d::Vector2f vec)
    {
        return createScaleMatrix(vec.u, vec.v);
    }

    Matrix createRotationMatrix(float angle)
    {
        return Matrix{{(float)cos(angle), -(float)sin(angle), 0}, {(float)sin(angle), (float)cos(angle), 0}, {0, 0, 1}};
    }

    Matrix createIdentity(int size)
    {
        squid::Matrix result(size, std::vector<float>(size));

        for (int i = 0; i < size; i++)
        {
            result[i][i] = 1;
        }

        return result;
    }

    Matrix multiply(const Matrix &left, const Matrix &right)
    {
        if (left[0].size() != right.size())
        {
            std::cerr << "Column number from left does not match row number from right";
        }

        squid::Matrix result(left.size(), std::vector<float>(right[0].size()));

        for (size_t i = 0; i < left.size(); i++)
        {
            for (size_t j = 0; j < right[0].size(); j++)
            {
                for (size_t k = 0; k < left[0].size(); k++)
                {
                    result[i][j] += left[i][k] * right[k][j];
                }
            }
        }

        return result;
    }

    m3d::Vector2f multiply(const squid::Matrix &mat, const m3d::Vector2f &vec)
    {
        squid::Matrix tmp{{vec.u}, {vec.v}, {1}};
        tmp = squid::multiply(mat, tmp);
        return m3d::Vector2f{tmp[0][0], tmp[1][0]};
    }
} // namespace squid

squid::Matrix operator*(const squid::Matrix &left, const squid::Matrix &right)
{
    return squid::multiply(left, right);
}

m3d::Vector2f operator*(const squid::Matrix &mat, const m3d::Vector2f &vec)
{
    return squid::multiply(mat, vec);
}

std::ostream &operator<<(std::ostream &out, const squid::Matrix &mat)
{
    for (const auto &subvec : mat)
    {
        for (const auto &value : subvec)
            out << ' ' << value;

        out << std::endl;
    }

    return out;
}