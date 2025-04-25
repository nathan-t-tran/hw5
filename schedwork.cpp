#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

#include "schedwork.h"

using namespace std;

static const Worker_T INVALID_ID = (unsigned int)-1;

// Helper function prototype
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftCounts,
    size_t day,
    size_t slot
);

// Main schedule() function
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if (avail.empty() || avail[0].empty()) {
        return false;
    }

    const size_t n = avail.size();
    const size_t k = avail[0].size();

    // Initialize the schedule with INVALID_ID
    sched.clear();
    sched = DailySchedule(n, std::vector<Worker_T>(dailyNeed, INVALID_ID));

    // Initialize shift counts for each worker
    std::vector<size_t> shiftCounts(k, 0);

    // Start recursive backtracking
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, 0, 0);
}

// Recursive helper function
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftCounts,
    size_t day,
    size_t slot
)
{
    // Base case: all days filled
    if (day == avail.size()) {
        return true;
    }

    // If all slots for the current day are filled, move to next day
    if (slot == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, day + 1, 0);
    }

    for (Worker_T worker = 0; worker < avail[0].size(); ++worker) {
        // Check availability, shift limit, and avoid duplicates on same day
        if (avail[day][worker] &&
            shiftCounts[worker] < maxShifts &&
            find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()) {
            
            // Assign and recurse
            sched[day][slot] = worker;
            shiftCounts[worker]++;

            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, day, slot + 1)) {
                return true;
            }

            // Backtrack
            sched[day][slot] = INVALID_ID;
            shiftCounts[worker]--;
        }
    }

    return false; // No valid assignment for this slot
}
