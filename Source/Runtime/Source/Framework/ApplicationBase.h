#pragma once

#undef CreateWindow

class ApplicationBase
{
protected:
    ApplicationBase();

public:
    virtual ~ApplicationBase() = default;
    
    // Overrides for devs
    virtual String GetApplicationName() = 0;

protected:
    virtual void OnInitialized() {};

public:
    virtual void OnMainGuiComponentInitialized() {};

public:
    // Dynamically swapped out at the start of the process
    using CreateInstanceFunction = ApplicationBase* (*)();
    static CreateInstanceFunction CreateInstance;

    static ApplicationBase* GetInstance() { return instance; }
    template<class T>
    static T* GetInstance() { return dynamic_cast<T*>(instance); }

    // Internals only
    static int Main(int arc, char** argv);
    static int Main();

public:
    void CreateWindow();

private:
    void InitializeApplication();

private:
    static ApplicationBase* instance;
    bool quit = false;
};
