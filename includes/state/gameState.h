#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <stack>
#include "state.h"
#include "types.h"

class GameState {
public:
    ~GameState();
    GameState() = default;

    static State* GetCurrentGameState();
    static void SetCurrentGameState(Owner<State> newState);
    static void ReplaceCurrentGameState(Owner<State> newState);
    static void RemoveCurrentGameState();

private:
    inline static std::stack<Owner<State>> currentGameState {};
};


#endif
