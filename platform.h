//File for platform specific functions
// Add others as needed
//
// (c) 2014 Adam Shelly (github.com/ashelly)
#include <time.h>
typedef struct timespec sysTime_t;
#define MS_PER_SEC 1000.0f

//** Linux specific high-precision timing**/

//returns elapsed time between `now` and `then` as sysType_t
static inline sysTime_t platformTimeElapsed(sysTime_t now, sysTime_t then)
{
  sysTime_t e;
  e.tv_sec = now.tv_sec-then.tv_sec;
  if (now.tv_nsec < then.tv_nsec){
    e.tv_sec-=1;
    e.tv_nsec = now.tv_nsec+(1e9-then.tv_nsec);
  }
  else{
    e.tv_nsec = now.tv_nsec-then.tv_nsec;
  }
  return e;
}

//converts `timeIn` to Milliseconds
static inline double platformSysTimeToMs(sysTime_t timeIn) {
  return (double)timeIn.tv_sec* MS_PER_SEC + (double)timeIn.tv_nsec / 1e6;
}

//fills `out` with current time
static inline void platformGetTime(sysTime_t* out){
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, out);
}
