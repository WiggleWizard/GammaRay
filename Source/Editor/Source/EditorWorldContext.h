#pragma once

#include "Engine/WorldContext.h"

class EditorWorld;

class EditorWorldContext : public WorldContext
{
private:
    ObjectPtr<EditorWorld> editorWorld = nullptr;
    ObjectPtr<EditorWorld> gameWorld = nullptr;
};
