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
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shifts);


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
    if(avail.empty())
    {
        return false;
    }

    //want to map the worker to their shifts
    map<Worker_T, size_t> shifts; 
    //traverse through workers in availability 
    for(size_t worker = 0; i < avail[0].size(); worker++)
    {
        shifts[worker] = 0;
    }

    return scheduleHelper(avail, dailyNeed, maxShifts, shifts, sched);


}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, map<Worker_T, size_t>& shifts)
{
    int row = 0; //day rows
    int col = 0; //worker columns. only dailyneed per day

    //base case - if all the days are filled
    if(day == sched.size())
    {
        return true;
    }

    //make sure if we have reached the daily need, or all workers are filled, go to next day
    if(col == dailyNeed) //d
    {
        day++;
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts);
    }

    //assign workers into initialized schedule
    for(size_t worker = 0; worker < avail[0].size(); worker++)
    {
        //is the worker available and is maxShifts not reached yet?
        if(avail[row][worker] && shifts[worker] < maxShifts) //if so, add worker into schedule
        {
            //worker is free and max shifts is not reached yet
            sched[row].push_back(worker);
            shifts[worker]++; //shift count increases for worker

            //next column
            col++;
            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts))
            {
                return true;
            }

            //backtrack:
            //remove worker from schedule
            shched[row][col] = INVALID_ID; 
            //decrease their shift count
            shifts[worker]--; 
        }
    }

    return false;
}

