#pragma once

#include "Engine/EngineModule.h"
#include "CoreMinimal.h"

#include <functional>
#include <memory>

class ModuleManager
{
public:
    using CreateEngineModuleFn = std::function<EngineModule*()>;
    
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
    std::unordered_map<StringName, std::unique_ptr<EngineModule>> engineModules;
    
private:
    ModuleManager() {}
    ~ModuleManager() {}
};
