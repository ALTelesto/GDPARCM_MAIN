#pragma once
#include "AGameObject.h"
class PoolableObject :
    public AGameObject
{
public:
    PoolableObject(String name);

public:
    virtual void onActivate() = 0;
    virtual void onRelease() = 0;
    virtual PoolableObject* clone() = 0;
};

