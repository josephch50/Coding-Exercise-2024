#ifndef TRUCK_HPP_
#define TRUCK_HPP_

#include <stdint.h>
#include <logger.hpp>

struct TruckProfile {
    uint32_t transition;
    uint32_t mining;
    uint32_t unloading;
};

enum TruckStatus {
    TRUCK_IDLE,
    TRUCK_TRANSITION,
    TRUCK_WAITING,
    TRUCK_MINING,
    TRUCK_UNLOADING,
};

class Truck {
    public:
        Truck() :
            startTime_s(0),
            status(TRUCK_IDLE),
            totalStations(0),
            totalMineTime(0),
            logger(0)
        {}

        Truck(DataLogger *log) :
            startTime_s(0),
            status(TRUCK_IDLE),
            totalStations(0),
            totalMineTime(0),
            logger(log)
        {}
        uint16_t startTask(uint32_t time, TruckProfile profile);
        TruckStatus poll(uint16_t id, uint32_t time);
        TruckStatus getStatus(void);
        uint8_t startMining(uint32_t time);
        TruckProfile getProfile(void);
        uint16_t getTotalMiningTime(void);
        uint16_t getTotalStations(void);
    private:
        TruckProfile profile;
        TruckStatus status;
        uint32_t startTime_s;
        uint16_t totalStations;
        uint16_t totalMineTime;
        DataLogger *logger;
};

#endif // TRUCK_HPP_