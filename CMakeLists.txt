cmake_minimum_required (VERSION 3.1.0)

project (ff1-online-server)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

SET( CMAKE_EXE_LINKER_FLAGS  " -static-libstdc++")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.45.0 REQUIRED COMPONENTS system filesystem regex)

add_subdirectory ("bot/")

add_executable(ff1-online-server src/main.cpp)

target_include_directories(ff1-online-server PRIVATE
    ${Boost_INCLUDE_DIRS}
    externals/cereal/include
    include/
)

target_link_libraries(ff1-online-server ${Boost_LIBRARIES})

