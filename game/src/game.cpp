#include "game.h"

Game::Game()
    : _player(Player(0, 240)), _level("../levels/level1.lvl")
{
    _gridSizeforOneUnit = WIN_H / 10;
    _run = true;
    _renderer = Renderer::GetInstance();
    Init();
    _state = RUNNING;
}

Game::~Game() {}

void Game::Update()
{
    while (_run)
    {
        HandleInput();
        switch (_state)
        {
        case RUNNING:
            Render();
            if (_player._positionX == _level._gatePosX && _player._positionY == _level._gatePosY)
                _state = PLAYERWIN;
            break;
        case PLAYERWIN:
            _renderer->Begin();
            _renderer->RenderBackground({100, 100, 0});
            _renderer->End();
            break;
        case PLAYERLOSE:
            break;
        case END:
            break;
        case QUIT:
            _run = false;
            break;
        default:
            break;
        }
    }
}

void Game::Render()
{
    _renderer->Begin();
    _renderer->RenderTexture(_player.GetRenderData());
    PassLevelDataToRenderer(_level);

    //if (SDL_RenderCopy(Renderer::GetRenderer(), _text.GetTexture(), NULL, NULL))
    //  DEBUG(SDL_GetError() << "1");

    _renderer->RenderTextTexture(&_text);

    for (Line line : _lines)
    {
        _renderer->DrawLine(line);
    }

    _renderer->End();
}

void Game::Init()
{
    _wall = Texture("../img/wall.png", 256, 256, 80, 80, 0, 0);
    _gate = Texture("../img/coin.png", 256, 256, 80, 80, _level._gatePosX, _level._gatePosY);
    _text = Text("Game text", {255, 255, 255, 255}, 50, 200, 0);

    for (int i = 1; i < _gridSizeforOneUnit; i++)
    {
        int position = i * CELLSIZE;
        Line line1(position, 0, position, 800);
        Line line2(0, position, 800, position);

        _lines.push_back(line1);
        _lines.push_back(line2);
    }
}

void Game::HandleInput()
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            _state = QUIT;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                if (IsMovementPossible(LEFT))
                    _player.Move(LEFT);
                break;
            case SDLK_d:
                if (IsMovementPossible(RIGHT))
                    _player.Move(RIGHT);
                break;
            case SDLK_w:
                if (IsMovementPossible(UP))
                    _player.Move(UP);
                break;
            case SDLK_s:
                if (IsMovementPossible(DOWN))
                    _player.Move(DOWN);
                break;

            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Game::PassLevelDataToRenderer(Level level)
{
    //TODO : Find an algorithm to find proper position to render the wall.

    int row;
    int column;

    for (int i = 0; i < 100; i++)
    {
        switch (_level._blocks[i])
        {
        case Empty:
            //clean code :)
            break;
        case Wall:
            row = i / COLUMNCOUNT;
            column = i % ROWCOUNT;
            _wall.ChangePositionOnScreen(column * CELLSIZE, row * CELLSIZE);
            _renderer->RenderTexture(&_wall);
            break;
        case Gate:
            _renderer->RenderTexture(&_gate);
            break;
        default:
            break;
        }
    }
}

bool Game::IsMovementPossible(Direction dir)
{
    int tempX = _player._positionX;
    int tempY = _player._positionY;

    switch (dir)
    {
    case UP:
        tempY -= CELLSIZE;
        break;
    case DOWN:
        tempY += CELLSIZE;
        break;
    case RIGHT:
        tempX += CELLSIZE;
        break;
    case LEFT:
        tempX -= CELLSIZE;
        break;
    default:
        break;
    }
    int col = tempX / CELLSIZE;
    int row = tempY / CELLSIZE;

    int index = (row * COLUMNCOUNT + col);

    if (_level._blocks[index] != Wall && ((tempX >= 0 && tempX < WIN_W) && (tempY >= 0 && tempY < WIN_H)))
        return true;
    else
        return false;
}