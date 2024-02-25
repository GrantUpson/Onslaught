#ifndef MAINMENU_H
#define MAINMENU_H

#include "state.h"


class MainMenu : public State {
public:
    MainMenu() = default;
    ~MainMenu() override;

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;
};



#endif