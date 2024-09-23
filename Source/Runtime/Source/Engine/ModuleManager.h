#pragma once

#include "CoreMinimal.h"

#include "Engine/EngineModule.h"

#include <functional>
#include <memory>

class EngineModule;

class ModuleManager
{
public:
    using CreateEngineModuleFn = std::function<std::unique_ptr<EngineModule>()>;
    
public:
    static ModuleManager& Get()
    {
        static ModuleManager s;
        return s;
    }

    int RegisterEngineModuleFactoryFunction(const StringName& moduleName, CreateEngineModuleFn& factoryFn);

    void InitializeEngineModules();

public:
    ModuleManager(const ModuleManager&) = delete;
    ModuleManager& operator =(const ModuleManager&) = delete;

private:
    std::unordered_map<StringName, CreateEngineModuleFn> engineModuleFactories;
    std::vector<EngineModule*> engineModules;
    
private:
    ModuleManager() {}
    ~ModuleManager() {}
};
