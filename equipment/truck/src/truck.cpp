
#include <truck.hpp>

uint16_t Truck::startTask(uint32_t time, TruckProfile p)
{
    profile = p;
    startTime_s = time;
    totalStations++;
    status = TRUCK_TRANSITION;
    return 0;
}

TruckStatus Truck::poll(uint16_t id, uint32_t time)
{
    uint32_t elapsed = 0;

    if (status != TRUCK_IDLE)
        elapsed = time - startTime_s;
    // State Machine to trigger the next event based on time, waiting state requires controller intervention
    switch (status)
    {
        case TRUCK_TRANSITION:
            if (elapsed >= profile.transition)
            {
                logger->write("[T+%dm] Truck %d (%p) Waiting... (elapsed %d min)\n", time/60, id, this, elapsed/60);
                startTime_s = time;
                status = TRUCK_WAITING;
            }
            break;
        case TRUCK_MINING:
            if (elapsed >= profile.mining)
            {
                logger->write("[T+%dm] Truck %d (%p) Done Mining... (elapsed %d min)\n", time/60, id, this, elapsed/60);
                totalMineTime += elapsed;
                startTime_s = time;
                status = TRUCK_UNLOADING;
            }
            break;
        case TRUCK_UNLOADING:
            if (elapsed >= profile.unloading)
            {
                logger->write("[T+%dm] Truck %d (%p) Done Unloading... (elapsed %d min)\n", time/60, id, this, elapsed/60);
                startTime_s = time;
                status = TRUCK_IDLE;
            }
            break;
        default:
            break;
    }

    return status;
}

TruckStatus Truck::getStatus(void)
{
    return status;
}

uint8_t Truck::startMining(uint32_t time)
{
    if (TRUCK_WAITING == status)
    {
        startTime_s = time;
        status = TRUCK_MINING;
        return 0;
    }
    return 1;
}

TruckProfile Truck::getProfile(void)
{
    return profile;
}

uint16_t Truck::getTotalMiningTime(void)
{
    return totalMineTime;
}

uint16_t Truck::getTotalStations(void)
{
    return totalStations;
}
