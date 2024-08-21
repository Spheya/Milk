set(NBT_USE_ZLIB  OFF CACHE BOOL "" FORCE)
set(NBT_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory("asio")
add_subdirectory("concurrentqueue")
add_subdirectory("glm")
add_subdirectory("json")
add_subdirectory("nbt")