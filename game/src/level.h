#pragma once
#include "level_loader.h"

class Level
{

public:
    Level(const char *filepath)
    {
        LoadLevel(filepath, _blocks);
    }
    std::vector<int> _blocks;
};