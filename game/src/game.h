#pragma once
#include <iostream>
#include "gameDefines.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"
#include "utils.h"
#include "level.h"
#include "text.h"
#include "vector"
#include "animation.h"
#include "time.h"

enum GameState
{
    RUNNING,
    PLAYERWIN,
    PLAYERLOSE,
    END,
    QUIT
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
    void UpdateGameText();
    bool IsMovementPossible(Direction dir);

private:
    Player _player;
    Texture _wall;
    GameState _state;
    int _gridSizeforOneUnit;
    Renderer *_renderer;
    bool _run;
    Level _level;
    Text _text;

    Animation _coin;

    std::vector<Line> _lines;
    std::string _positionText;

    Time *_time;
};
