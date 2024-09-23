#include "Engine/ModuleManager.h"
#include "Module/EditorModule.h"

#include <memory>

ModuleManager::CreateEngineModuleFn fn = []()
{
    return std::make_unique<EditorModule>();
};
int moduleId = ModuleManager::Get().RegisterEngineModuleFactoryFunction("Editor", fn);
