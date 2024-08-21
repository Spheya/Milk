cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("milk")
add_subdirectory ("external")

set(SOURCE_FILES
	"src/milk/core/Server.cpp"
	"src/milk/core/ServerStatus.cpp"
	"src/milk/protocol/Packet.cpp"
	"src/milk/protocol/PacketHandler.cpp"
	"src/milk/net/Connection.cpp"
	"src/milk/net/Server.cpp"
	"src/milk/registry/DimensionType.cpp"
	"src/milk/types/UUID.cpp"
	"src/milk/types/Identifier.cpp"
	"src/milk/registry/WolfVariant.cpp"
	"src/milk/registry/PaintingVariant.cpp"
)

add_library (milk ${SOURCE_FILES})
set_property(TARGET milk PROPERTY CXX_STANDARD 20)

target_include_directories(milk PUBLIC "src")
target_link_libraries(milk PUBLIC asio concurrentqueue glm json nbt)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  add_subdirectory ("example")
endif()