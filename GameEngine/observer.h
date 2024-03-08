#pragma once
#include <stdint.h>

//enum State
//{
//    Unknown,
//    Restarting,
//    RowCleared,
//    LevelUp,
//};

class Observer
{
public:
    virtual void OnNotify(uint8_t level) = 0;
};

