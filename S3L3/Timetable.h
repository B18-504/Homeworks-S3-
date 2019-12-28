#pragma once

class Timetable
{
public:                                 //to be private
    int interval = 0;
    int duration = 0;
    int offset = 0;

public:
    Timetable() = default;
    Timetable(int, int, int);
    ~Timetable() = default;

    int GetTime(int);
};

#include "Timetable.cpp"