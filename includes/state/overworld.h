#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "state.h"


class Overworld : public State {
public:
    Overworld() = default;
    ~Overworld() override;

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;
};



#endif