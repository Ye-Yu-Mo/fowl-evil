/// @file atlas.hpp
/// @brief 图集类
/// 绘制图片素材时
/// 从 图片 -> 内存结构 SDL_Surface
/// 借助硬件加速进行绘图
/// SDL_Surface -> 显存结构 -> 借助 Renderer 进行渲染显式到窗口

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <string>

#include "./logger.hpp"

/// @class Atlas
/// @brief 图集 持有并管理图片纹理对象
class Atlas
{
public:
    /// @brief 构造函数
    Atlas() = default;

    /// @brief 释放图集纹理对象
    ~Atlas()
    {
        for (SDL_Texture *texture : _tex_list)
            SDL_DestroyTexture(texture); // 工厂方法析构
    }

    /// @brief 清空图集内容
    void clear()
    {
        _tex_list.clear();
    }

    /// @brief 获取图集数量
    /// @return 图集数量
    int getSize() const
    {
        return static_cast<int>(_tex_list.size());
    }

    /// @brief 获取指定下标的纹理对象
    /// @param idx 下标索引
    /// @return 纹理对象指针
    SDL_Texture* getTexture(int idx)
    {
        if (idx < 0 || idx > _tex_list.size())
        {
           warn(logger, "get_texture 越界！ index : %d , size : %d", idx, _tex_list.size());
           return nullptr;
        }
        return _tex_list[idx];
    }

    /// @brief 添加额外纹理
    /// @param texture 纹理对象
    void addTexture(SDL_Texture* texture)
    {
        _tex_list.push_back(texture);
    }

    /// @brief 从磁盘按照动画帧文件序号加载图片
    /// 图片路径通过模板字符串和序号拼接生成，然后加载为纹理并存储在图集中。
    /// @param renderer SDL_Renderer对象，用于创建纹理
    /// @param path_template 图片路径的模板字符串（例如"frame_%d.png"）。
    /// @param num 要加载的图片数量
    void load(SDL_Renderer *renderer, const char *path_template, int num)
    {
        for (int i = 0; i < num; i++)
        {
            char path_file[256];
            sprintf(path_file, path_template, i + 1);                    // 生成完整图片路径
            SDL_Texture *texture = IMG_LoadTexture(renderer, path_file); // 加载为纹理 内存结构
            _tex_list.push_back(texture);
        }
    }

private:
    std::vector<SDL_Texture *> _tex_list; ///< 纹理列表
};