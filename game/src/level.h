#pragma once
#include "level_loader.h"

enum EntityType
{
    Empty,
    Wall,
    Gate,
    PlayerLoc
};

class Level
{

public:
    Level(const char *filepath)
    {
        LoadLevel(filepath, _blocks);

        int row;
        int column;

        for (int i = 0; i < 100; i++)
        {
            if (_blocks[i] == Gate)
            {
                row = i / COLUMNCOUNT;
                column = i % ROWCOUNT;

                _gatePosX = column * CELLSIZE;
                _gatePosY = row * CELLSIZE;
            }
            else if (_blocks[i] == PlayerLoc)
            {
                row = i / COLUMNCOUNT;
                column = i % ROWCOUNT;

                _playerPosX = column * CELLSIZE;
                _playerPosY = row * CELLSIZE;
            }
        }
    }
    std::vector<int> _blocks;

    int _gatePosX;
    int _gatePosY;

    int _playerPosX;
    int _playerPosY;
};