
#include <stdio.h>
#include <stdint.h>
#include <station.hpp>


uint16_t Station::getTotalTrucks(void)
{
    return totalTrucks;
}

uint16_t Station::getTotalMiningTime(void)
{
    return totalMineTime;
}

uint16_t Station::addToQueue(Truck* truck) 
{
    queue.push(truck);
    return queue.size();
}

uint16_t Station::getQueueSize(void) 
{
    return queue.size();
}

Truck* Station::getCurrentTruck(void)
{
    return queue.front();
}

StationStatus Station::setState(StationStatus state)
{
    status = state;
    return status;
}

StationStatus Station::poll(uint16_t id, uint32_t time) 
{
    if (status == STATION_IDLE)
    {
        if (!queue.empty() && (queue.front()->getStatus() == TRUCK_WAITING))
        {
            // Start Mining
            queue.front()->startMining(time);
            printf("[T+%dm] Station %d: Truck %p: Start Mining for next %d minutes\n", time/60, id, queue.front(), queue.front()->getProfile().mining/60);
        }

        if (!queue.empty() && (queue.front()->getStatus() == TRUCK_MINING))
        {
            status = STATION_BUSY;
            totalTrucks++;
            startTime_s = time;
        }
    }
    else if (status == STATION_BUSY)
    {
        if (queue.front()->getStatus() != TRUCK_MINING)
        {
            status = STATION_IDLE;
            totalMineTime += (time - startTime_s);
            startTime_s = 0;
            queue.pop();
        }
    }
    return status;
}