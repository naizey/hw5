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
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& shifts, /*size_t next_worker, size_t workerCount, */size_t day, size_t worker);


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

    const size_t numDays = avail.size(); //number of days
    const size_t numWorkers = avail[0].size(); //number of workers

    //if the daily need is greater than the number of workers available, can't make valid sched
    if(numWorkers < dailyNeed)
    {
        return false;
    }

    // //want to map the worker to their shifts
    // map<Worker_T, size_t> shifts; 
    // //traverse through workers in availability 
    // for(size_t worker = 0; worker < numWorkers; worker++)
    // {
    //     shifts[worker] = 0;
    // }

    sched.resize(numDays); //set to num days

    for(size_t i = 0; i < sched.size(); i++)
    {
        sched[i].resize(dailyNeed, INVALID_ID);
        // vector<Worker_T> temp;
        // sched.push_back(temp); //push back for each day
        // for(size_t j = 0; j < dailyNeed; j++)
        // {
        //     sched[i].push_back(INVALID_ID); //initialize the schedule with invalid id
        // }

    }

    vector<size_t> shifts(numWorkers, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, /*0, 0,*/ 0, 0);


}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& shifts, /*size_t next_worker, size_t workerCount, */size_t day, size_t worker)
{
    //int workerCount = 0; //increment the number of workers scheduled 

    //base case - if all the days are filled (up til last day and all workers filled)
    if(day == avail.size())
    {
        return true;
    }

    if(worker == dailyNeed)
    {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0); //go to next day
    }

    //assign workers into initialized schedule
    for(size_t w = 0; w < avail[day].size(); w++)
    {
        // if(find(sched[day].begin(), sched[day].end(), w) != sched[day].end()) //if the worker is already scheduled
        // {
        //     continue; //skip to next worker
        // }
        //is the worker available and is maxShifts not reached yet?
        if(avail[day][w] && shifts[w] < maxShifts) //if so, add worker into schedule
        {
            //worker is free and max shifts is not reached yet
            bool assigned = false;
            for(size_t i = 0; i < worker && !assigned; i++)
            {
                if(sched[day][i] == w)
                {
                    assigned = true; //worker is aready assigned don't assign again
                }
            }

            if(!assigned)
            {
                sched[day][worker] = w; //add worker to schedule
                shifts[w]++; //increment the shift count for the worker
            

                if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day, worker + 1))
                {
                    return true;
                }

                //backtrack:
                sched[day][worker] = INVALID_ID; //remove the worker from the schedule
                //remove worker from schedule
                shifts[w]--;
            }
            // sched[day][worker] = w;
            // shifts[w]++; //shift count increases for worker
            // //workerCount++;
            //checks if the workers working is less than the daily need, NEED MORE WORKERS
            // if(workerCount < dailyNeed)
            // {
                // if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day, worker + 1))
                // {
                //     return true;
                // }
            // }
            //if we have the amount we need, go to next day
            // else if(workerCount == dailyNeed)
            // {
            //     //increment the day
            //     if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0, day + 1, 0)) //if the daily need is met, go to next day
            //     {
            //         return true;
            //     }
            // }
            
        }

        
        //decrease their shift count
        //workerCount--;
    }

    return false;
}

