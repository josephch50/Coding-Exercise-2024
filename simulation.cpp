// File: simulation.cpp
// Author: Joseph Chen
// Description: Creates a 72-hour simulation of continuous mining using n-mining stations

#include <station.hpp>
#include <truck.hpp>
#include <stdio.h>
#include <ctime>


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
    printf("************ Lunar Mining Simulation ************\n");
    // Initialize Trucks and Stations
    uint32_t timestamp_s = 0;
    Truck trucks[NUM_TRUCKS];
    Station stations[NUM_STATIONS];
    TruckStatus truckStatus;
    StationStatus stationStatus;
    int i, j, minQueue = 0;

    // truck gets assigned a station -> join queue,
    // travel to queue, stay in queue until 30 minutes elapsed
    //   if truck.first() == waiting, station tells truck to start mining
    // once truck done mining over a specific amount of time, --> unload.

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
                printf("[T+%dm] Truck %d Queued at Station %d. Mine Time=%d min\n", timestamp_s/60, i, minQueue, randNum/60);
            }
        }

        // Iterate through all Stations
        for (i = 0; i < NUM_STATIONS; i++) {
            stationStatus = stations[i].poll(i, timestamp_s);
        }
    }

    // Simulation Statistic Printout
    printf("\nStatistics:\n\n*** Stations ***\n");
    for (i = 0; i < NUM_STATIONS; i++) {
        printf("Station %d: Total Trucks: %d Total Mine Time: %f hr\n", i, stations[i].getTotalTrucks(), static_cast<double>(stations[i].getTotalMiningTime())/60/60);
    }
    printf("\n**** Trucks ****\n");
    for (i = 0; i < NUM_TRUCKS; i++) {
        printf("Truck %d: Total Mines: %d Total Mine Time: %f hr\n", i, trucks[i].getTotalStations(), static_cast<double>(trucks[i].getTotalMiningTime())/60/60);
    }
    printf("********** Lunar Mining Simulation End **********\n");
    return 0;
}
