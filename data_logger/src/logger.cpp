
#include <logger.hpp>
#include <stdio.h>
#include <stdarg.h>

#define LOG_STDOUT
void DataLogger::write(const char* format, ...)
{
    FILE * pFile = fopen("simulation.log","a+");;
    va_list argList;
    // Read in va list and fprintf to file
    va_start(argList, format);
    vfprintf(pFile, format, argList);
#ifdef LOG_STDOUT
    vprintf(format, argList);
#endif
    va_end(argList);

    fclose(pFile);
}
