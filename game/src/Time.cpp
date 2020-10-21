#include "time.h"

Time* Time::_instance = nullptr;
float Time::_deltaTime;

Time::Time()
{
}

Time* Time::GetInstance()
{
    if (_instance == nullptr)
        _instance = new Time();

    return _instance;
}

void Time::Update()
{
    float time = (float)SDL_GetTicks();
    _deltaTime = time - _firstTime;
    _firstTime = time;
}