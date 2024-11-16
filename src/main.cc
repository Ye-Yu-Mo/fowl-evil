#include <glaze/glaze.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
struct my_struct
{
   int i = 287;
   double d = 3.14;
   std::string hello = "Hello World";
   std::array<uint64_t, 3> arr = {1, 2, 3};
};

template <>
struct glz::meta<my_struct>
{
   static constexpr std::string_view name = "my_struct";
   using T = my_struct;
   static constexpr auto value = object(
      "i", [](auto&& v) -> auto& { return v.i; }, //
      &T::d, //
      "hello", &T::hello, //
      &T::arr //
   );
};

static constexpr auto info = glz::reflect<my_struct>{};

#include <iostream>

int main()
{
   std::cout << "Field types:\n";
   glz::for_each<info.size>([](auto I) {
      // std::cout << glz::name_v<decltype(glz::get<I>(info.values))> << '\n';
   });

   std::cout << "Field keys:\n";
   glz::for_each<info.size>([](auto I) { std::cout << info.keys[I] << '\n'; });

   my_struct obj{};
   std::cout << '\n' << glz::write_json(obj).value() << '\n';
   constexpr std::string_view input = R"({"i":287,"d":3.14,"hello":"Hello World","arr":[1,2,3]})";
   auto ec = glz::read_json(obj, input);
   if (ec) {
      std::cout << "error: " << glz::format_error(ec, input);
   }

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 使用 SDL2_gfx 绘制图形
    filledCircleColor(renderer, 320, 240, 100, 0xFFFF0000);  // 绘制红色圆形

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);  // 显示 5 秒钟

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
