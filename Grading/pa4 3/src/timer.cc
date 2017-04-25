#include "../include/timer.h"

// Calculates time since a given timestamp
// Globals:
//   none
// Arguments:
//   timeval struct representing start time
// Returns:
//   double representing time since t1 in seconds
double get_time(struct timeval t1) {
    struct timeval t2;
    double end_time;
    double total_time;

    gettimeofday(&t2, NULL);

    end_time = t2.tv_usec + t2.tv_sec * 1000000;

    total_time = end_time - (t1.tv_usec + t1.tv_sec * 1000000);
    total_time = total_time / 1000000.0;

    return total_time;
}
