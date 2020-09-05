#include "game.h"

Game::Game()
    : _player(Player(0, 240)), _level("../levels/level1.txt")
{
    _gridSizeforOneUnit = WIN_H / 10;
    _run = true;
    _renderer = Renderer::GetInstance();
    Init();
    _state = RUNNING;

    DEBUG(_gridSizeforOneUnit);
}

Game::~Game() {}

void Game::Update()
{

    while (_run)
    {
        DEBUG(_player._positionX << "," << _player._positionY);
        HandleInput();
        switch (_state)
        {
        case RUNNING:
            Render();
            break;
        case PLAYERWIN:
            break;
        case PLAYERLOSE:
            break;
        case END:
            break;
        case QUIT:
            _run = false;
            DEBUG("run is false");
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
    for (Texture sprite : _sprites)
    {
        _renderer->RenderTexture(&sprite);
    }

    for (Line line : _lines)
    {
        _renderer->DrawLine(line);
    }

    _renderer->End();
}

void Game::Init()
{
    _wall = Texture("../img/wall.png", 256, 256, 80, 80, 0, 0);
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
                DEBUG("Key A Pressed!");
                if (IsMovementPossible(LEFT))
                    _player.Move(LEFT);
                break;
            case SDLK_d:
                DEBUG("Key D Pressed!");
                if (IsMovementPossible(RIGHT))
                    _player.Move(RIGHT);
                break;
            case SDLK_w:
                DEBUG("Key W Pressed!");
                if (IsMovementPossible(UP))
                    _player.Move(UP);
                break;
            case SDLK_s:
                DEBUG("Key S Pressed!");
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
            //not implemented yet
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

    if (_level._blocks[index] != Wall && ((tempX >= 0 && tempX < 800) && (tempY >= 0 && tempY < 800)))
        return true;
    else
        return false;
}