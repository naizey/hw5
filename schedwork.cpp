#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shifts, size_t row, size_t col);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //if availability is empty
    if(avail.empty() || avail[0].empty())
    {
        return false;
    }

    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    DailySchedule temp(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));

    //want to map the worker to their shifts
    map<Worker_T, size_t> shifts; 
    //traverse through workers in availability 
    for(size_t worker = 0; worker < numWorkers; worker++)
    {
        shifts[worker] = 0;
    }

    if(scheduleHelper(avail, dailyNeed, maxShifts, temp, shifts, 0, 0))
    {
        sched = temp; //if the schedule is valid
        return true;
    }

    return false;


}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shifts, size_t day, size_t col)
{
    // int row = 0; //day rows
    // int col = 0; //worker columns. only dailyneed per day

    //base case - if all the days are filled
    if(day == sched.size())
    {
        return true;
    }

    //make sure if we have reached the daily need, or all workers are filled, go to next day
    if(col == dailyNeed) //d
    {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day+1, 0);
    }

    //assign workers into initialized schedule
    for(size_t worker = 0; worker < avail[0].size(); worker++)
    {
        //is the worker available and is maxShifts not reached yet?
        if(avail[day][worker] && shifts[worker] < maxShifts && std::find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()) //if so, add worker into schedule
        {
            //worker is free and max shifts is not reached yet
            sched[day][col] = worker;
            shifts[worker]++; //shift count increases for worker

            //next column
            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day, col+1))
            {
                return true;
            }

            //backtrack:
            //remove worker from schedule
            sched[day][col] = INVALID_ID; 
            //decrease their shift count
            shifts[worker]--; 
        }
    }

    return false;
}

