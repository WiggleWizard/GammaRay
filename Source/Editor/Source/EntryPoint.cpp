#include "Engine/ModuleManager.h"
#include "Module/EditorModule.h"

#include <memory>

ModuleManager::CreateEngineModuleFn fn = []()
{
    return static_cast<EngineModule*>(new EditorModule());
};
int moduleId = ModuleManager::Get().RegisterEngineModuleFactoryFunction("Editor", fn);
