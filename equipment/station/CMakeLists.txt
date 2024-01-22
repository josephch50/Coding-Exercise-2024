add_library(station
    src/station.cpp
)

target_include_directories(station
    PUBLIC
        include
)

target_link_libraries(station
    PRIVATE
        data_logger
        truck
)
