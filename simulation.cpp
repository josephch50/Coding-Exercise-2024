// File: simulation.cpp
// Author: Joseph Chen
// Description: Creates a 72-hour simulation of continuous mining using n-mining stations

#include <logger.hpp>
#include <station.hpp>
#include <truck.hpp>
#include <stdio.h>
#include <ctime>
#include <cstdlib>


// Configurable Simulation Parameters
#define NUM_STATIONS 3
#define NUM_TRUCKS 10
#define NUM_HOURS 72
// In Seconds
#define TIME_TRANSITION 1800
#define TIME_UNLOAD 300
#define TIME_RANGE_MAX 5*60*60
#define TIME_RANGE_MIN 1*60*60


int main() {
    // Initialize Trucks and Stations
    uint32_t timestamp_s = 0;
    DataLogger logger(&timestamp_s);
    Truck trucks[NUM_TRUCKS] = {&logger};
    Station stations[NUM_STATIONS] = {&logger};
    TruckStatus truckStatus;
    StationStatus stationStatus;
    int i, j, minQueue = 0;

    // truck gets assigned a station -> join queue,
    // travel to queue, stay in queue until 30 minutes elapsed
    //   if truck.first() == waiting, station tells truck to start mining
    // once truck done mining over a specific amount of time, --> unload.

    logger.write("************ Lunar Mining Simulation ************\n");
    // Runs each second
    for (timestamp_s = 0; timestamp_s < NUM_HOURS * 3600; timestamp_s++) {
        // Iterate through all Trucks
        for (i = 0; i < NUM_TRUCKS; i++) {
            truckStatus = trucks[i].poll(i, timestamp_s);
            if (truckStatus == TRUCK_IDLE)
            {
                // Assign to a station with the least amount of queue
                minQueue = 0;
                for (j = 0; j < NUM_STATIONS; j++) {
                    if (stations[j].getQueueSize() < stations[minQueue].getQueueSize())
                        minQueue = j;
                }
                int randNum = rand()%(TIME_RANGE_MAX-TIME_RANGE_MIN + 1) + TIME_RANGE_MIN;
                trucks[i].startTask(timestamp_s, {TIME_TRANSITION, (uint32_t) randNum, TIME_UNLOAD});
                stations[minQueue].addToQueue(&trucks[i]);
                logger.write("[T+%dm] Truck %d Queued at Station %d. Mine Time=%d min\n", timestamp_s/60, i, minQueue, randNum/60);
            }
        }

        // Iterate through all Stations
        for (i = 0; i < NUM_STATIONS; i++) {
            stationStatus = stations[i].poll(i, timestamp_s);
        }
    }

    // Simulation Statistic Printout
    logger.write("\nStatistics:\n\n*** Stations ***\n");
    for (i = 0; i < NUM_STATIONS; i++) {
    }
        logger.write("Station %d: Total Trucks: %d Total Mine Time: %f hr\n", i, stations[i].getTotalTrucks(), static_cast<double>(stations[i].getTotalMiningTime())/60/60);
    logger.write("\n**** Trucks ****\n");
    for (i = 0; i < NUM_TRUCKS; i++) {
        logger.write("Truck %d: Total Mines: %d Total Mine Time: %f hr\n", i, trucks[i].getTotalStations(), static_cast<double>(trucks[i].getTotalMiningTime())/60/60);
    }
    logger.write("********** Lunar Mining Simulation End **********\n");
    return 0;
}
