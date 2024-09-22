#pragma once

#include "Core/Types/Types.h"
#include "Framework/ApplicationBase.h"

class Editor : public ApplicationBase
{
public:
    String GetApplicationName() override;

    void OnInitialized() override;
};