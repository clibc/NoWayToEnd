#pragma once
#include <iostream>
#include "gameDefines.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"
#include "utils.h"
#include "level.h"
#include "vector"

enum GameState
{
    RUNNING,
    PLAYERWIN,
    PLAYERLOSE,
    END,
    QUIT
};

enum EntityType
{
    Empty,
    Wall,
    Gate
};

class Game
{
public:
    Game();
    ~Game();
    void Update();
    void Render();
    void HandleInput();
    void Init();
    void PassLevelDataToRenderer(Level level);
    bool IsMovementPossible(Direction dir);

private:
    Player _player;
    Texture _wall;
    GameState _state;
    int _gridSizeforOneUnit;
    Renderer *_renderer;
    bool _run;
    Level _level;

    std::vector<Line> _lines;
    std::vector<Texture> _sprites;
};
