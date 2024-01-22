cmake_minimum_required(VERSION 3.16.3)

project(lunar_mining VERSION 1.0.0 DESCRIPTION "Lunar Regolith")

set (CMAKE_CXX_STANDARD 11)
set(binary simulation)
add_executable(${binary})

target_link_libraries(${binary}
    PRIVATE
        data_logger
        station
        truck
)

target_sources(${binary}
    PRIVATE
        simulation.cpp
)

add_subdirectory(equipment)
