#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "window.h"


class Game {
public:
    Game() = default;

    bool Initialize();
    void Run();
    void Shutdown();

private:
    bool isRunning {true};
    Owner<Window> window;
};


#endif
