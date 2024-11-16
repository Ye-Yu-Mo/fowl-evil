# SDL2 SDL2-gfx SDL2-image SDL2-mixer SDL2-ttf glaze-JSON

# 设置最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(fowl-evil VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2_gfx REQUIRED)



# 添加 SDL2 包
find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_GFX_INCLUDE_DIR})

include_directories(${SDL2_INCLUDE_DIRS})

# 设置使用静态编译
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)  # 可执行文件

# 添加源文件
set(SOURCES
    src/main.cc
)

# 添加头文件目录
include_directories(include)

# 查找静态库
# 假设静态库位于`lib`目录下，名为libmystaticlib.a
# link_directories(${CMAKE_SOURCE_DIR}/lib)

# 创建可执行文件
add_executable(fowl-evil ${SOURCES})

target_link_libraries(fowl-evil
    ${SDL2_LIBRARIES}
    SDL2_gfx
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)

target_link_libraries(fowl-evil ${SDL2_GFX_LIBRARY})

# 连接静态库
# target_link_libraries(fowl-evil PRIVATE mystaticlib)

# 如果需要安装，指定安装规则
# install(TARGETS MyProject DESTINATION bin)

# 如果你有第三方库（例如SDL2）并且是静态库，可以链接它
# find_library(SDL2_LIBRARY NAMES SDL2 PATHS /path/to/SDL2/lib)
# target_link_libraries(MyProject PRIVATE ${SDL2_LIBRARY})
