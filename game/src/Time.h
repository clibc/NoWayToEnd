#pragma once
#include "SDL.h"

class Time
{
public:
    static Time *GetInstance();
    static inline float DeltaTime() { return _deltaTime / 1000.0f; }
    void Update();

private:
    Time();
    static Time *_instance;
    static float _deltaTime;
    float _firstTime;
};