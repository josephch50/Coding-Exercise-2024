add_library(data_logger
    src/logger.cpp
)

target_include_directories(data_logger
    PUBLIC
        include
)
