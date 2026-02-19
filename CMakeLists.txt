cmake_minimum_required(VERSION 3.16)
project(WeatherApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(WeatherApp src/main.cpp)

target_link_libraries(WeatherApp PRIVATE cpr::cpr nlohmann_json::nlohmann_json)