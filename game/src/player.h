#pragma once
#include "animation.h"
#include "gameDefines.h"
#include "texture.h"

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Player {
public:
    int _positionX;
    int _positionY;

    Player() = default;
    Player(int posX, int posY);
    void Move(Direction direction);
    inline const Texture* GetRenderData() const { return &_tSprite; }
    inline Animation* GetAnim() { return &_sprite; }
    ~Player() = default;

private:
    Texture _tSprite;
    Animation _sprite;
    int health;
};
