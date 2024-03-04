#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"


class Player {
public:
    explicit Player(const Vector2& position) : position(position) {}

    Vector2 position;
};



#endif
