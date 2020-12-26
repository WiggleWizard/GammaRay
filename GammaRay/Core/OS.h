#pragma once

#include "Core.h"


class MainLoop;

class GAMMARAY_API OS
{
    static OS* m_singleton;

public:
    OS();
    ~OS();

    static OS* GetSingleton();
};

