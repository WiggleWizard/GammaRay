#pragma once

#include "ApplicationBase.h"

#define GAMMARAY_CREATE_APPLICATION_DEFINE(ApplicationClass) \
    ApplicationBase* CreateApplication() { return new ApplicationClass(); }

// Initializes application base.
// Basic "bootstrapping" line to get booted into Skeleton as soon as the application can do so.
#define START_GAMMARAY_APPLICATION(ApplicationClass) \
    GAMMARAY_CREATE_APPLICATION_DEFINE(ApplicationClass) \
        int main(int argc, char** argv) \
        { \
            ApplicationBase::CreateInstance = &CreateApplication; \
            return ApplicationBase::Main(argc, argv); \
        }