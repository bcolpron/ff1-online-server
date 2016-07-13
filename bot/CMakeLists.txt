cmake_minimum_required (VERSION 3.1.0)

add_executable(ff1-online-bot src/main.cpp)

target_include_directories(ff1-online-bot PRIVATE
    ${Boost_INCLUDE_DIRS}
    ../externals/cereal/include
    ../include/
    include/
)

target_link_libraries(ff1-online-bot ${Boost_LIBRARIES} pthread)

