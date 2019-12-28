#include "Exceptions.h"

Timetable::Timetable(int interval, int duration, int offset)
{
    this->interval = interval;
    this->duration = duration;
    this->offset = offset;
}

int Timetable::GetTime(int point_arrival_time)
{
    if((interval > 0) * (duration > 0))
    {
        return (((point_arrival_time - 1 - offset)/interval) + ((point_arrival_time - offset) > 0))*interval + duration + offset;
    }
    else
    {
        throw Exception(1, "Bad timetable data");
    }
}