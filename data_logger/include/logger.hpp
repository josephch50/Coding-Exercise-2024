#ifndef DATA_LOGGER_HPP_
#define DATA_LOGGER_HPP_

#include <stdint.h>

class DataLogger {
    public:
        DataLogger(uint32_t *pTime) :
            time(pTime)
        {}
        void write(const char* format, ...);

    private:
        uint32_t *time;
};

#endif // DATA_LOGGER_HPP_