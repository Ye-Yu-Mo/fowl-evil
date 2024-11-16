find_path(SDL2_GFX_INCLUDE_DIR SDL2/SDL2_gfxPrimitives.h)
find_library(SDL2_GFX_LIBRARY SDL2_gfx)

if (SDL2_GFX_INCLUDE_DIR AND SDL2_GFX_LIBRARY)
    set(SDL2_GFX_FOUND TRUE)
else()
    set(SDL2_GFX_FOUND FALSE)
endif()

if (SDL2_GFX_FOUND)
    message(STATUS "Found SDL2_gfx: ${SDL2_GFX_LIBRARY}")
else()
    message(FATAL_ERROR "Could not find SDL2_gfx")
endif()

mark_as_advanced(SDL2_GFX_INCLUDE_DIR SDL2_GFX_LIBRARY)
