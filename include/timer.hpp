/// @file timer.hpp
/// @brief 定时器
#pragma once

#include <functional>

/// @class Timer
/// @brief 定时器类。
///
/// 定时器支持以下功能：
/// - 设置等待时间
/// - 定时触发回调函数
/// - 支持暂停和恢复
/// - 单次触发模式和循环模式
class Timer
{
    using TimeOut = std::function<void()>; ///< 定义超时回调类型

public:
    /// @brief 默认构造函数
    Timer() = default;
    /// @brief 默认析构函数
    ~Timer() = default;

    /// @brief 重置定时器
    /// 将累计的计时时间重置为零，并取消触发状态
    void restart()
    {
        _pass_time = 0;
        _shotted = false;
    }

    /// @brief 设置定时器等待时间
    /// @param val 定时器的等待时间（秒）
    void setWaitTime(float val)
    {
        _wait_time = val;
    }
    /// @brief 设置超时触发时的回调函数
    /// @param on_timeout 回调函数，定时器超时时触发
    void setOnTimeout(TimeOut on_timeout)
    {
        _on_timeout = on_timeout;
    }
    /// @brief 暂停定时器
    ///
    /// 暂停后定时器不再更新计时时间，直到调用`resume`恢复
    void pause()
    {
        _paused = true;
    }
    /// @brief 恢复定时器
    ///
    /// 恢复暂停的定时器，使其重新开始更新计时时间
    void resume()
    {
        _paused = false;
    }
    /// @brief 更新定时器
    /// 每帧调用此函数以更新定时器的计时时间。如果达到等待时间且满足触发条件
    /// 则调用设置的回调函数
    /// @param delta 上一帧到当前帧的时间间隔（秒）
    void onUpdate(float delta)
    {
        if (_paused)
            return;

        _pass_time += delta;
        if (_pass_time >= _wait_time)
        {
            bool can_shot = (!_one_shot || (_one_shot && !_shotted));
            _shotted = true;
            if (can_shot && _on_timeout)
                _on_timeout();
            _pass_time -= _wait_time;
        }
    }

private:
    float _pass_time = 0;   ///< 已经过的时间（秒）
    float _wait_time = 0;   ///< 等待的时间（秒）
    bool _paused = false;   ///< 定时器是否处于暂停状态
    bool _shotted = false;  ///< 是否已经触发过（用于单次触发模式）
    bool _one_shot = false; ///< 是否为单次触发模式
    TimeOut _on_timeout;    ///< 是否为单次触发模式
};