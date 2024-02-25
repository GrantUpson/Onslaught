#include "state/gameState.h"


GameState::~GameState() {
    while(!currentGameState.empty()) {
        currentGameState.pop();
    }
}


State* GameState::GetCurrentGameState() {
    return currentGameState.top().get();
}


void GameState::SetCurrentGameState(Scope<State> newState) {
    if(!currentGameState.empty()) {
        currentGameState.top()->OnExit();
    }

    currentGameState.push(std::move(newState));
    currentGameState.top()->OnEnter();
}


void GameState::ReplaceCurrentGameState(Scope<State> newState) {
    RemoveCurrentGameState();
    currentGameState.push(std::move(newState));
}


void GameState::RemoveCurrentGameState() {
    currentGameState.top()->OnExit();
    currentGameState.pop();
}