#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "state.h"


class SplashScreen : public State {
public:
    SplashScreen() = default;
    ~SplashScreen() override;

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;
};


#endif