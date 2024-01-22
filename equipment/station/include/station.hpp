// File: station.hpp
// Author: Joseph Chen
// Description: Station object
#ifndef STATION_HPP_
#define STATION_HPP_

#include <logger.hpp>
#include <truck.hpp>

#include <stdint.h>
#include <queue>

enum StationStatus {
    STATION_IDLE,
    STATION_BUSY,
};

class Station {
    public:
        Station() :
            status(STATION_IDLE),
            totalTrucks(0),
            totalMineTime(0),
            logger(0)
        {}

        Station(DataLogger *log) :
            status(STATION_IDLE),
            totalTrucks(0),
            totalMineTime(0),
            logger(log)
        {}
        uint16_t addToQueue(Truck* truck);
        uint16_t getQueueSize(void);
        uint16_t getTotalTrucks(void);
        uint16_t getTotalMiningTime(void);
        Truck* getCurrentTruck(void);
        StationStatus setState(StationStatus state);
        StationStatus poll(uint16_t id, uint32_t time);
    private:
        uint32_t startTime_s;
        StationStatus status;
        uint16_t totalTrucks;
        uint16_t totalMineTime;
        std::queue<Truck*> queue;
        DataLogger *logger;

};
uint16_t getTotalTrucks();

uint16_t getTotalMiningTime();

#endif //STATION_HPP_