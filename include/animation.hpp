/// @file animation.hpp
/// @brief 帧动画
/// 使用Timer定时器
/// 控制每隔一段时间 切换显示的纹理到下一个逻辑帧
/// 逻辑帧可以是 下一张图片对象 或者 同一张纹理对象的不同裁剪区域
#pragma once
#include "timer.hpp"
#include "atlas.hpp"
#include "camera.hpp"
#include "vector2.hpp"

#include <SDL2/SDL.h>

#include <vector>
#include <functional>

/// @class Animation
/// @brief 帧动画类
class Animation
{
public:
    using onFinished = std::function<void()>; ///< 完成帧动画时的回调类型

    /// @brief 构造函数
    Animation()
    {
        _timer.setOneShot(false);
        _timer.setOnTimeout([&]()
                            {
            ++_idx_frame;
            if (_idx_frame >= _frame_list.size())
            {
                _idx_frame = _is_loop ? 0 : _frame_list.size() - 1;
                if (!_is_loop && _on_finished)
                    _on_finished();
            } });
    }

    ~Animation() = default;

    /// @brief 重置动画的当前帧索引和定时器状态
    void reset()
    {
        _timer.restart();
        _idx_frame = 0;
    }
    /// @brief 设置动画位置
    void setPosition(const Vector2 &position) { _position = position; }
    /// @brief 设置动画旋转角度
    void setRotation(double angle) { _angle = angle; }
    /// @brief 设置旋转中心
    void setCenter(const SDL_FPoint &center) { _center = center; }
    /// @brief 设置是否循环播放
    void setLoop(bool is_loop) { _is_loop = is_loop; }
    /// @brief 设置每帧的间隔时间
    void setInterval(float interval) { _timer.setWaitTime(interval); }
    /// @brief 设置动画完成后的回调函数
    void setOnFinished(onFinished on_finished) { _on_finished = on_finished; }

    /// @brief 添加一组帧到动画中
    /// 将一组由相同纹理但不同裁剪区域的帧添加到动画中。
    /// @param texture 动画使用的纹理
    /// @param num_h 帧的数量，按水平方向排列
    void addFrame(SDL_Texture *texture, int num_h)
    {
        int width, height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

        int width_frame = width / num_h;
        for (int i = 0; i < num_h; i++)
        {
            SDL_Rect rect_src;
            rect_src.x = i * width_frame, rect_src.y = 0;
            rect_src.w = width_frame, rect_src.h = height;

            _frame_list.emplace_back(texture, rect_src);
        }
    }

    /// @brief 添加一个图集中的所有帧到动画中
    /// 将 `Atlas` 中的所有纹理帧添加到动画中。
    /// @param atlas 动画的纹理图集
    void addFrame(Atlas *atlas)
    {
        for (int i = 0; i < atlas->getSize(); i++)
        {
            SDL_Texture *texture = atlas->getTexture(i);
            int width, height;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

            SDL_Rect rect_src;
            rect_src.x = 0, rect_src.y = 0;
            rect_src.w = width, rect_src.h = height;

            _frame_list.emplace_back(texture, rect_src);
        }
    }

    /// @brief 更新动画状态
    void onUpdate(float delta) { _timer.onUpdate(delta); }

    /// @brief 渲染动画
    /// 在给定的摄像机视角下渲染当前帧。
    /// @param camera 摄像机对象，用于确定渲染时的位置和视角
    void onRender(const Camera &camera) const
    {
        const Frame &frame = _frame_list[_idx_frame];
        const Vector2 &pos_camera = camera.getPosition();

        SDL_FRect rect_dst;
        rect_dst.x = _position.x - frame._rect_src.w / 2;
        rect_dst.y = _position.y - frame._rect_src.h / 2;
        rect_dst.w = (float)frame._rect_src.w, rect_dst.h = (float)frame._rect_src.h;

        camera.renderTexture(frame._texture, &frame._rect_src, &rect_dst, _angle, &_center);
    }

private:
    /// @struct Frame
    /// @brief 帧结构体
    /// 存储单个帧的信息，包括纹理和裁剪区域
    struct Frame
    {
        SDL_Rect _rect_src;              ///< 裁剪区域
        SDL_Texture *_texture = nullptr; ///< 纹理对象

        Frame() = default;
        ~Frame() = default;

        /// @brief 构造函数
        /// @param texture 纹理对象
        /// @param rect_src 源纹理
        Frame(SDL_Texture *texture, const SDL_Rect &rect_src)
            : _texture(texture), _rect_src(rect_src) {}
    };

private:
    Vector2 _position;              ///< 动画位置
    double _angle = 0;              ///< 动画旋转角度
    SDL_FPoint _center = {0};       ///< 旋转中心
    Timer _timer;                   ///< 定时器对象
    bool _is_loop = true;           ///< 是否循环播放
    size_t _idx_frame = 0;          ///< 当前帧索引
    std::vector<Frame> _frame_list; ///< 帧列表
    onFinished _on_finished;        ///< 播放完成时的回调函数
};