#include "grpch.h"

#include "Core/Input/InputKeyCode.h"
#include "Core/Input/InputMouseCode.h"


int InputKeyCode::NativeToGammaRay(int keycode)
{
    return keycode;
}

int InputMouseButtonCode::NativeToGammaRay(int mouseButton)
{
    return mouseButton;
}
