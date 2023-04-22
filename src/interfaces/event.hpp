#pragma once

class Event
{
public:
    virtual const void *GetEventRawHandle() const = 0;
};
