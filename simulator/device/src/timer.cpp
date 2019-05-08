#include    "timer.h"

Timer::Timer(double timeout, bool first_process, QObject *parent)
    : QObject(parent)
    , tau(0.0)
    , timeout(timeout)
    , first_process(first_process)
    , is_started(false)
{

}

Timer::~Timer()
{

}

void Timer::step(double t, double dt)
{
    if (is_started)
    {
        if ( first_process || (tau >= timeout) )
        {
            emit process();
            tau = 0;
            first_process = false;
        }

        tau += dt;
    }
}

void Timer::start()
{
    is_started = true;
    reset();
}

void Timer::stop()
{
    is_started = false;
    reset();
}

void Timer::reset()
{
    first_process = true;
    tau = 0.0;
}

bool Timer::isStarted() const
{
    return is_started;
}
