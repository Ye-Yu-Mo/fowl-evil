/// @file vector2.hpp
/// @brief 二维向量类
/// 用来表述坐标位置 移动速度等矢量值
#pragma once

#include <cmath>

/// @class Vector2
/// @brief 二维向量类
class Vector2
{
public:
    /// @brief 默认构造
    Vector2() = default;
    /// @brief 默认析构
    ~Vector2() = default;

    /// @brief 构造函数
    /// @param idx_x x 分量
    /// @param idx_y y 分量
    Vector2(float idx_x, float idx_y) : x(idx_x), y(idx_y) {}

    /// @brief 向量加法
    /// @param vec 另一向量
    /// @return 新向量
    Vector2 operator+(const Vector2 &vec) const
    {
        return Vector2(x + vec.x, y + vec.y);
    }
    /// @brief 向量剑法
    /// @param vec 另一向量
    /// @return 新向量
    Vector2 operator-(const Vector2 &vec) const
    {
        return Vector2(x - vec.x, y - vec.y);
    }
    /// @brief 向量乘标量
    /// @param val 标量
    /// @return 新向量
    Vector2 operator*(float val) const
    {
        return Vector2(x * val, y * val);
    }
    /// @brief 向量除标量
    /// @param val 标量
    /// @return 新向量
    Vector2 operator/(float val) const
    {
        return Vector2(x / val, y / val);
    }

    /// @brief 向量内积
    /// @param vec 要计算点积的向量
    /// @return 内积的结果
    float operator*(const Vector2 &vec) const
    {
        return x * vec.x + y * vec.y;
    }
    /// @brief 向量加法赋值运算符重载
    /// @param vec 要相加的向量
    void operator+=(const Vector2 &vec)
    {
        x += vec.x, y += vec.y;
    }
    /// @brief 向量减法赋值运算符重载。
    /// @param vec 要相减的向量。
    void operator-=(const Vector2 &vec)
    {
        x -= vec.x, y -= vec.y;
    }
    /// @brief 向量与标量的乘法赋值运算符重载。
    /// @param val 要相乘的标量。
    void operator*=(float val)
    {
        x *= val, y *= val;
    }
    /// @brief 向量与标量的除法赋值运算符重载。
    /// @param val 要相除的标量。
    void operator/=(float val)
    {
        x /= val, y /= val;
    }
    /// @brief 计算向量的长度。
    /// @return 返回向量的长度（模）。
    float length()
    {
        return sqrt(x * x + y * y);
    }
    /// @brief 归一化向量。
    /// @return 返回单位向量。如果向量长度为0，则返回 (0, 0)。
    Vector2 normalize()
    {
        float len = length();
        if (len == 0)
            return Vector2(0, 0);
        return Vector2(x / len, y / len);
    }

public:
    float x = 0; ///< 向量的 x 分量
    float y = 0; ///< 向量的 y 分量
};