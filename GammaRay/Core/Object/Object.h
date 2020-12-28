#pragma once


#define GRCLASS(m_class, m_inheritsFrom) \
private: \
public: \
    static const char* GetClassNameStatic() { return #m_class; } \
    virtual const char* GetClassName() const { return m_class::GetClassNameStatic(); } \
private:

class Object
{
public:
    template<typename T>
    static T* CastTo(Object* fromObject)
    {
        return dynamic_cast<T*>(fromObject);
    }

    template<typename T>
    static const T* CastTo(const Object* fromObject)
    {
        return dynamic_cast<const T*>(fromObject);
    }

public:
    virtual ~Object() {};
};
