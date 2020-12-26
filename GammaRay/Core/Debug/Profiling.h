#pragma once

#include "Tracy.hpp"


struct Profile
{

};

class Profiler
{
public:
};

#define GR_PROF_FRAME_MARK FrameMark
#define GR_PROF_ZONE(profileId, name) ZoneScopedN(name)
