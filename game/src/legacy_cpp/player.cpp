#include "player.h"

Player::Player(int posX, int posY)
    : _positionX(posX)
    , _positionY(posY)
{
    _sprite = Animation("../img/pirate.png", 192, 32, 32, posX, posY);
}

void Player::Move(Direction direction)
{
    switch (direction) {
    case UP:
        _positionY -= CELLSIZE;
        break;
    case DOWN:
        _positionY += CELLSIZE;
        break;
    case RIGHT:
        _positionX += CELLSIZE;
        break;
    case LEFT:
        _positionX -= CELLSIZE;
        break;
    default:
        break;
    }
    _sprite.ChangePositionOnScreen(_positionX, _positionY);
}
