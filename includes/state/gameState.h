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
    static void SetCurrentGameState(Scope<State> newState);
    static void ReplaceCurrentGameState(Scope<State> newState);
    static void RemoveCurrentGameState();

private:
    inline static std::stack<Scope<State>> currentGameState {};
};


#endif
