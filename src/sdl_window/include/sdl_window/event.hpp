#pragma once

#include "interfaces/event.hpp"
#include "SDL.h"

class SDLEvent : public Event
{
public:
    const void *GetEventRawHandle() const final
    {
        return reinterpret_cast<const void *>(&e_);
    };
    SDL_Event e_;
};