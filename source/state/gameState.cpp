#include "state/gameState.h"


GameState::~GameState() {
    while(!currentGameState.empty()) {
        currentGameState.pop();
    }
}


State* GameState::GetCurrentGameState() {
    return currentGameState.top().get();
}


void GameState::SetCurrentGameState(Owner<State> newState) {
    if(!currentGameState.empty()) {
        currentGameState.top()->OnExit();
    }

    currentGameState.push(std::move(newState));
    currentGameState.top()->OnEnter();
}


void GameState::ReplaceCurrentGameState(Owner<State> newState) {
    RemoveCurrentGameState();
    currentGameState.push(std::move(newState));
}


void GameState::RemoveCurrentGameState() {
    currentGameState.top()->OnExit();
    currentGameState.pop();
}