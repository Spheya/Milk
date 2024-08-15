add_executable(milk_example "example.cpp")
set_property(TARGET milk_example PROPERTY CXX_STANDARD 20)
target_link_libraries(milk_example PUBLIC milk)