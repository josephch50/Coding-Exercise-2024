add_library(truck
    src/truck.cpp
)

target_include_directories(truck
    PUBLIC
        include
)

target_link_libraries(truck
    PRIVATE
        data_logger
)
