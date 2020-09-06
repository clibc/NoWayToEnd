#pragma once
#include "level_loader.h"

enum EntityType
{
    Empty,
    Wall,
    Gate
};

class Level
{

public:
    Level(const char *filepath)
    {
        LoadLevel(filepath, _blocks);

        for (int i = 0; i < 100; i++)
        {
            if (_blocks[i] == Gate)
            {
                int row = i / COLUMNCOUNT;
                int column = i % ROWCOUNT;

                _gatePosX = column * CELLSIZE;
                _gatePosY = row * CELLSIZE;
            }
        }
    }
    std::vector<int> _blocks;

    int _gatePosX;
    int _gatePosY;
};