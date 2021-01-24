#pragma once
#include "common.h"

struct player
{
    int x = 8;
    int y = 1;
    enum next
    {
        empty,
        wall,
        coin
    };
};

inline bool player_can_move(int cell)
{
    if (cell == player::empty || cell == player::coin || cell == 3)
        return true;
    return false;
}
