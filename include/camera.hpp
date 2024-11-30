/// @file camera.hpp
/// @brief 摄像机类
/// 如果摄像机本身就在抖动的状态中
/// 只需要随机摄像机本身的位置
/// 就能产生抖动的效果

#pragma once
#include "timer.hpp"
#include "vector2.hpp"

#include <SDL2/SDL.h>

/// @class Camera
/// @brief 处理摄像机位置和抖动效果的类
class Camera
{
public:
    /// @brief 构造函数
    /// @param renderer 渲染器对象
    Camera(SDL_Renderer *renderer)
    {
        this->renderer = renderer;

        _timer_shake.setOneShot(true);
        _timer_shake.setOnTimeout([&]()
                                  {
            _is_shaking = false;
            reset(); });
    }

    /// @brief 获取摄像机当前位置
    /// @return 摄像机当前位置
    const Vector2 &getPosition() const
    {
        return _position;
    }

    /// @brief 重置摄像机位置
    void reset()
    {
        _position.x = 0;
        _position.y = 0;
    }

    /// @brief 更新摄像机位置
    /// @param delta 通过此参数传入时间增量，用于更新时间和动画
    /// 摄像机的活动范围是原始位置的[-50, 50]
    void onUpdate(float delta)
    {
        _timer_shake.onUpdate(delta);
        if (_is_shaking)
        {
            _position.x = (-50 + rand() % 100) / 50.0f * _shaking_strength;
            _position.y = (-50 + rand() % 100) / 50.0f * _shaking_strength;
        }
    }

    /// @brief 启动摄像机抖动效果
    /// @param strength 抖动强度，控制抖动的幅度
    /// @param duration 抖动持续时间
    void shake(float strength, float duration)
    {
        _is_shaking = true;
        _shaking_strength = strength;
        _timer_shake.setWaitTime(duration);
        _timer_shake.restart();
    }

    /// @brief 渲染纹理
    /// @param texture 纹理对象
    /// @param rect_src 源纹理
    /// @param rect_dst 目标纹理
    /// @param angle 旋转角度
    /// @param center 旋转中心
    void renderTexture(SDL_Texture *texture, const SDL_Rect *rect_src,
                       const SDL_FRect *rect_dst, double angle, const SDL_FPoint *center) const
    {
        SDL_FRect rect_dst_win = *rect_dst;
        rect_dst_win.x -= _position.x;
        rect_dst_win.y -= _position.y;

        // 自行决定绘制的角度和旋转中心
        SDL_RenderCopyExF(renderer, texture, rect_src,
                          &rect_dst_win, angle, center, SDL_RendererFlip::SDL_FLIP_NONE);
    }

private:
    Vector2 _position;                ///< 摄像机当前位置
    Timer _timer_shake;               ///< 抖动定时器
    bool _is_shaking = false;         ///< 标记是否处于抖动状态
    float _shaking_strength = 0;      ///< 抖动强度
    SDL_Renderer *renderer = nullptr; ///< 渲染器对象指针
};