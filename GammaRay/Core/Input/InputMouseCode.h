#pragma once


#define GR_MOUSE_BUTTON_1         0
#define GR_MOUSE_BUTTON_2         1
#define GR_MOUSE_BUTTON_3         2
#define GR_MOUSE_BUTTON_4         3
#define GR_MOUSE_BUTTON_5         4
#define GR_MOUSE_BUTTON_6         5
#define GR_MOUSE_BUTTON_7         6
#define GR_MOUSE_BUTTON_8         7
#define GR_MOUSE_BUTTON_LAST      GLFW_MOUSE_BUTTON_8
#define GR_MOUSE_BUTTON_LEFT      GLFW_MOUSE_BUTTON_1
#define GR_MOUSE_BUTTON_RIGHT     GLFW_MOUSE_BUTTON_2
#define GR_MOUSE_BUTTON_MIDDLE    GLFW_MOUSE_BUTTON_3


namespace InputMouseButtonCode
{
    int NativeToGammaRay(int mouseButton);
}
