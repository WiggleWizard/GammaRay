#pragma once

class World;
class RenderTarget;

// Persistent object that tracks any existing worlds within the game
class WorldContext : public Object
{
public:
    virtual void Process();
    
    void LoadWorld(ObjectPtr<World> world);

private:
    ObjectPtr<RenderTarget> viewport = nullptr;
    ObjectPtr<World> currentWorld = nullptr;
};
