#ifndef _TIMER__H
#define _TIMER__H

#include <SDL.h>

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    /** Get the timer's time */
    Uint32 getTicks();

    /** Check status */
    bool isStarted();

    bool isPaused();

private:
    /** The clock time when the timer started */
    Uint32 startTicks;

    /** The ticks stored when the timer was pause */
    Uint32 pausedTicks;

    /** The timer status */
    bool started;
    bool paused;
};

#endif // _TIMER__H

